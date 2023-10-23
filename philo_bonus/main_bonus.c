/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:05:17 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/22 15:08:12 by rugrigor         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_menu	menu;
	t_philo philo;

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	menu_init(argv, &philo, &menu);
	if (ft_error(argv) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	philo_init(&menu, &philo, -1);
	if (philo_create(&menu, &philo, -1) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
}