/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:09:00 by rugrigor          #+#    #+#             */
/*   Updated: 2023/05/17 17:57:25 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo	*philo)
{
	
}

void	thread(t_philo	*philo)
{
	int 		i;
	
	i = -1;
	pthread_mutex_init(&philo->mutex, NULL);
	while (++i < philo->pargv[1])
	{
		if (pthread_create(&philo->th[i], NULL, &routine, NULL) != 0)
			return (write(2, "Ruzik_ERROR", 12));
	}
	i = -1;
	while (++i < philo->pargv[1])
	{
		if (pthread_join(philo->th[i], NULL) != 0)
			return (write(2, "Ruzik_ERROR", 12));
	}
	pthread_mutex_destroy(&philo->mutex);
}

int main(int argc, char **argv)
{
	t_philo	*philo;
	
	if (argc == 1 || argc > 5)
		return (write(2, "Ruzik_ERROR", 12));
	philo->pargv = argv;
	if (ft_error(philo) != 0)
		return (write(2, "Ruzik_ERROR", 12));
	thread(philo);
}