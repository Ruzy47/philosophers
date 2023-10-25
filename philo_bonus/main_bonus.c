/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:05:17 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/25 17:37:24 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check2(t_philo *philo)
{
	if (philo->meal_count == 0)
		return (1);
	if (get_time(philo, 0) - philo->last_meal > philo->time_to_die)
	{
		sem_wait(philo->last);
		philo->die = 1;
		sem_post(philo->last);
		printf("[%lld ms] %d died\n", get_time(philo, 0), philo->num);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		n;
	t_menu	menu;

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	n = ft_error(argv);
	if (n == 1)
		return (write(2, "Ruzik_ERROR\n", 13));
	else if (n != 2)
	{
		menu_init(argv, &menu);
		if (philo_create(&menu, -1) != 0)
			return (write(2, "Ruzik_ERROR\n", 13));
	}
	else if (n == 2)
		printf("[0 ms] everyone ate\n");
	return (0);
}
