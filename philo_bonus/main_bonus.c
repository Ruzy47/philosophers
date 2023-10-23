/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:05:17 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/23 12:33:37 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check2(t_philo *philo)
{
	sem_wait(philo->last);
	if (philo->die == 1)
	{
		sem_post(philo->last);
		return (1);
	}
	sem_post(philo->last);
	return (0);
}

int	main(int argc, char **argv)
{
	t_menu	menu;

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	if (ft_error(argv) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	menu_init(argv, &menu, -1);
	// philo_init(&philo);
	// i = -1;
	// printf("%d\n", philo.philo_count);
	// while (++i < philo.philo_count)
	// {
	// 	menu.philo[i] = philo;
	// 	menu.philo[i].num = i + 1;
	// }
	if (philo_create(&menu, -1) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
}
