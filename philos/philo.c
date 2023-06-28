/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/06/28 18:09:54 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void	*info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	while (1)
	{
		pthread_mutex_lock(&(philo->fork[philo->right_fork]));
		pthread_mutex_lock(&(philo->fork[philo->left_fork]));
	}
	return (NULL);
}

int	philo_create(t_menu *menu, t_philo *philo)
{
	int 		i;
	
	i = 0;	
	if (get_time(philo) == 1)
			return (1);
	while (++i <= menu->philo_count)
	{
		if (pthread_create(&philo[i].th, NULL, routine, (void *)&(menu->philo[i])) != 0)
			return (1);
	}
	return (0);
}