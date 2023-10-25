/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/25 17:13:41 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine2(t_philo	*philo)
{
	pthread_mutex_lock(philo->left_fork);
	p_printf("take left fork", philo);
	if (!philo->right_fork)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	p_printf("take right fork", philo);
	p_printf("is eating", philo);
	s_sleep(philo, 1, 0);
	pthread_mutex_lock(philo->last);
	philo->last_meal = get_time(philo, 0);
	pthread_mutex_unlock(philo->last);
	pthread_mutex_lock(philo->meal);
	philo->eat_times++;
	pthread_mutex_unlock(philo->meal);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*routine(void	*info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	if ((philo->num - 1) % 2)
		usleep(7000);
	while (!check2(philo))
	{
		if (routine2(philo))
			break ;
		pthread_mutex_lock(philo->meal);
		if (philo->meal_count && philo->eat_times >= philo->meal_count)
		{
			pthread_mutex_unlock(philo->meal);
			break ;
		}
		pthread_mutex_unlock(philo->meal);
		p_printf("is sleeping", philo);
		s_sleep(philo, 0, 0);
		p_printf("is thinking", philo);
	}
	return (NULL);
}

int	check_2(t_menu *menu, int i)
{
	pthread_mutex_lock(menu->meal);
	while (menu->meal_count != -1 && i < menu->philo_count
		&& menu->philo[i].eat_times >= menu->meal_count)
		i++;
	if (i == menu->philo_count)
	{
		pthread_mutex_lock(menu->write);
		menu->eat = 1;
		printf("[%lld ms] everyone ate\n", get_time(&menu->philo[0], 0));
		pthread_mutex_unlock(menu->write);
		pthread_mutex_unlock(menu->meal);
		return (1);
	}
	pthread_mutex_unlock(menu->meal);
	return (0);
}

int	check(t_menu *menu, int i)
{
	while (++i < menu->philo_count)
	{
		pthread_mutex_lock(menu->last);
		if (get_time(&menu->philo[i], 0) - menu->philo[i].last_meal
			>= menu->time_to_die)
		{
			pthread_mutex_lock(menu->write);
			menu->die = 1;
			printf("[%lld ms] %d died\n", get_time(&menu->philo[0], 0),
				menu->philo[i].num);
			pthread_mutex_unlock(menu->write);
			pthread_mutex_unlock(menu->last);
			return (1);
		}
		pthread_mutex_unlock(menu->last);
	}
	if (check_2(menu, 0) == 1)
		return (1);
	return (0);
}

int	philo_create(t_menu *menu)
{
	int	i;

	i = -1;
	while (++i < menu->philo_count)
	{
		menu->philo[i].num = i + 1;
		if (pthread_create(&menu->philo[i].th, NULL,
				&routine, &menu->philo[i]) == -1)
			return (1);
	}
	while (1)
		if (check(menu, -1) == 1)
			break ;
	i = -1;
	while (++i < menu->philo_count)
		if (pthread_join(menu->philo[i].th, NULL) != 0)
			return (1);
	i = -1;
	while (++i < menu->philo_count)
		pthread_mutex_destroy(&(menu->fork[i]));
	pthread_mutex_destroy(menu->write);
	pthread_mutex_destroy(menu->meal);
	pthread_mutex_destroy(menu->last);
	return (0);
}
