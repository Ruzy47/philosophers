/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:09:00 by rugrigor          #+#    #+#             */
/*   Updated: 2023/06/21 17:51:31 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo	*philo)
{
	// while (1)
	// {
	// 	if (philo->th)
	// }
	printf("%d\n", *philo->th);
}

void	thread(t_philo	*philo)
{
	int 		i;
	
	i = 1;
	while (i++ <= philo->pargv[1])
	{
		if (pthread_create(&philo->th[i], NULL, &routine, &philo) != 0 ||
			pthread_mutex_init(&philo->fork[i], NULL) != 0)
			return (write(2, "Ruzik_ERROR", 12));
	}
	i = 1;
	while (i++ <= philo->pargv[1])
	{
		//pthread_mutex_destroy(&philo->fork[i]);
		if (pthread_join(philo->th[i], NULL) != 0)
			return (write(2, "Ruzik_ERROR", 12));
	}
}

int main(int argc, char **argv)
{
	t_philo	*philo;
	
	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR", 12));
	philo->pargv = argv;
	if (ft_error(philo) != 0)
		return (write(2, "Ruzik_ERROR", 12));
	thread(philo);
	
}