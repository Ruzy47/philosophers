/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/22 14:46:35 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void	*info)
{
	t_philo	*philo;

	//printf("aaa");
	philo = (t_philo *)info;
	printf("aaabbb\n");
	pthread_mutex_lock(&(philo->fork[philo->left_fork]));
	printf("%lld%d""has taken left fork\n", get_time(philo), philo->num);
	pthread_mutex_lock(&(philo->fork[philo->right_fork]));
	printf("%lld%d""has taken right fork\n", get_time(philo), philo->num);
	philo->eat_times++;
	//printf("%lld", get_time(philo));
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&(philo->fork[philo->left_fork]));
	pthread_mutex_unlock(&(philo->fork[philo->right_fork]));
	usleep(philo->time_to_sleep);
	return (NULL);
}

int	philo_create(t_menu *menu, t_philo *philo)
{
	int 		i;
	
	i = -1;
	if (get_time(philo) == 1)
			return (1);
			//printf("aaa\n");
	while (++i <= menu->philo_count)
	{
		if (pthread_create(&philo[i].th, NULL, routine, (void *)&(menu->philo[i])) != 0)
			return (1);
	printf("aaa\n");
	}
	i = -1;
	while (++i <= menu->philo_count)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			printf("Ruzik_ERROR\n");
	printf("aaab\n");
	}
	return (0);
}