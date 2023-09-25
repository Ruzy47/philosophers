/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/25 17:34:10 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void	*info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("[%lld ms] %d take left fork\n", get_time(philo), philo->num);
		pthread_mutex_lock(philo->right_fork);
		printf("[%lld ms] %d take right fork\n", get_time(philo), philo->num);
		philo->eat_times++;
		printf("[%lld ms] %d is eating\n", get_time(philo), philo->num);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("[%lld ms] %d is sleeping\n", get_time(philo), philo->num);
		usleep(philo->time_to_sleep * 1000);
		printf("[%lld ms] %d is thinking\n", get_time(philo), philo->num);
		return (NULL);
	}
}

int	philo_create(t_menu *menu)
{
	int	i;
	
	i = -1;
	while (++i < menu->philo_count)
		if (pthread_create(&menu->philo[i].th, NULL, &routine, &menu->philo[i]) == -1)
			return (1);
	i = -1;
	while (++i < menu->philo_count)
		if (pthread_join(menu->philo[i].th, NULL) != 0)
			return (1);
	return (0);
}