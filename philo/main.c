/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:05:17 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/25 18:11:26 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check2(t_philo *philo)
{
	pthread_mutex_lock(philo->last);
	if (*philo->die == 1)
	{
		pthread_mutex_unlock(philo->last);
		return (1);
	}
	pthread_mutex_unlock(philo->last);
	return (0);
}

int	main(int argc, char **argv)
{
	t_menu	menu;
	int		n;

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	n = ft_error(argv);
	if (n == 1)
		return (write(2, "Ruzik_ERROR\n", 13));
	else if (n != 2)
	{
		menu_init(argv, &menu);
		if (fork_create(&menu) != 0)
			return (write(2, "Ruzik_ERROR\n", 13));
		philo_init(&menu, -1);
		if (philo_create(&menu) != 0)
			return (write(2, "Ruzik_ERROR\n", 13));
	}
	else if (n == 2)
		printf("[0 ms] everyone ate\n");
	return (0);
}
