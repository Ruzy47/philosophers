/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:05:17 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/25 11:08:41 by rugrigor         ###   ########.fr       */
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

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	if (ft_error(argv) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	menu_init(argv, &menu);
	if (fork_create(&menu) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	philo_init(&menu, -1);
	if (philo_create(&menu) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
}
