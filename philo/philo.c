/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/23 16:58:13 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine2(t_philo	*philo)
{
	pthread_mutex_lock(philo->left_fork);
	p_printf("take left fork", philo);
	pthread_mutex_lock(philo->right_fork);
	p_printf("take right fork", philo);
	s_sleep(philo, 1, 0);
	pthread_mutex_lock(philo->last);
	p_printf("is eating", philo);
	philo->last_meal = get_time(philo, 0);
	pthread_mutex_unlock(philo->last);
	pthread_mutex_lock(philo->meal);
	philo->eat_times++;
	pthread_mutex_unlock(philo->meal);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void	*info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	if ((philo->num - 1) % 2)
		usleep(2000);
	while (!check2(philo))
	{
		routine2(philo);
		pthread_mutex_lock(philo->meal);
		if (*philo->eat == 1)
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
	while (menu->meal_count != -1 && i < menu->philo_count
		&& menu->philo[i].eat_times >= menu->meal_count)
		i++;
	if (i == menu->philo_count)
	{
		pthread_mutex_lock(menu->meal);
		menu->eat = 1;
		pthread_mutex_unlock(menu->meal);
		printf("[%lld ms] everyone ate\n", get_time(&menu->philo[0], 0));
		return (1);
	}
	return (0);
}

int	check(t_menu *menu, int i)
{
	while (++i < menu->philo_count)
	{
		if (get_time(&menu->philo[i], 0) - menu->philo[i].last_meal
			> menu->time_to_die)
		{
			pthread_mutex_lock(menu->last);
			menu->die = 1;
			pthread_mutex_unlock(menu->last);
			printf("[%lld ms] %d died\n", get_time(&menu->philo[0], 0),
				menu->philo[i].num);
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
		if (pthread_create(&menu->philo[i].th, NULL,
				&routine, &menu->philo[i]) == -1)
			return (1);
	while (1)
		if (check(menu, -1) == 1)
			break ;
	i = -1;
	while (++i < menu->philo_count)
	{
		if (pthread_join(menu->philo[i].th, NULL) != 0)
			return (1);
		pthread_detach(menu->philo[i].th);
	}
	i = -1;
	while (++i < menu->philo_count)
		pthread_mutex_destroy(&(menu->fork[i]));
	pthread_mutex_destroy(menu->write);
	pthread_mutex_destroy(menu->meal);
	pthread_mutex_destroy(menu->last);
	return (0);
}
