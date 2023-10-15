/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/15 20:30:53 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	s_sleep(t_philo *philo, int i, long long n)
{
	n = t_time();
	if (i == 2)
		if (n - philo->last_meal >= philo->time_to_die)
			philo->die = 1;
	if (i == 0 || i == 1)
	{
		while (philo->die < 0)
		{
			if (i == 1)
				if (get_time(philo, 1) - n >= philo->time_to_eat)
					break;
			if (i == 0)
				if (get_time(philo, 1) - n >= philo->time_to_sleep)
					break;
			usleep(50);
		}
		if (i == 1)
			philo->last_meal = get_time(philo, 1) - n;
		if (philo->meal_count > 0 && philo->eat_times == philo->meal_count)
			philo->die = 1;
	}
}

void	*routine(void	*info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	if ((philo->num - 1) % 2)
		usleep(7000);
	while (1)
	{
		s_sleep(philo, 2, 0);
		pthread_mutex_lock(philo->left_fork);
		p_printf("take left fork", philo);
		pthread_mutex_lock(philo->right_fork);
		p_printf("take right fork", philo);
		philo->eat_times++;
		if (philo->eat != -1)
			break;
		p_printf("is eating", philo);
		s_sleep(philo, 1, 0);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		p_printf("is sleeping", philo);
		s_sleep(philo, 0, 0);
		p_printf("is thinking", philo);
	}
	return (NULL);
}

void	check(t_menu *menu)
{
	int	i;
	
	//pthread_mutex_lock(menu->eat_t);
	while (!menu->eat)
	{
		i = 0;
		//pthread_mutex_lock(menu->eat_t);
		while (menu->philo[i].eat_times)
			if (menu->meal_count != -1 && i < menu->philo_count
				&& menu->philo[i].eat_times >= menu->meal_count)
				i++;
			{
				if (i == menu->meal_count)
					menu->eat = 1;
			}
		//pthread_mutex_unlock(menu->eat_t);
		//usleep(100);
	}
	//pthread_mutex_unlock(menu->eat_t);
	
}

int	philo_create(t_menu *menu)
{
	int	i;
	
	i = -1;
	while (++i < menu->philo_count)
	{
		if (pthread_create(&menu->philo[i].th, NULL, &routine, &menu->philo[i]) == -1)
			return (1);
		//usleep(100);
	}
	pthread_mutex_lock(menu->eat_t);
	check(menu);
	pthread_mutex_unlock(menu->eat_t);
	i = -1;
	while (++i < menu->philo_count)
	{
		if (pthread_join(menu->philo[i].th, NULL) != 0)
			return (1);
	}
	i = -1;
	while (++i < menu->philo_count)
		pthread_mutex_destroy(&(menu->fork[i]));
	pthread_mutex_destroy(menu->write);
	return (0);
}