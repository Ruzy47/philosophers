/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:25:16 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/23 20:19:43 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_init(char **argv, t_menu *menu, int i)
{
	while (++i < menu->philo_count)
	{
		menu->philo[i].num = i + 1;
		menu->philo[i].die = -1;
		menu->philo[i].eat = -1;
		menu->philo[i].eat_times = 0;
		menu->philo[i].philo_count = ft_atoi(argv[1]);
		menu->philo[i].fork = sem_open("/sem_fork", O_CREAT, S_IRWXU, menu->philo_count);
		menu->philo[i].last = sem_open("/sem_last", O_CREAT, S_IRWXU, 1);
		menu->philo[i].write = sem_open("/sem_write", O_CREAT, S_IRWXU, 1);
		menu->philo[i].meal = sem_open("/sem_meal", O_CREAT, S_IRWXU, 1); 
		menu->philo[i].time_to_die = ft_atoi(argv[2]);
		menu->philo[i].time_to_eat = ft_atoi(argv[3]);
		menu->philo[i].time_to_sleep = ft_atoi(argv[4]);
		menu->philo[i].last_meal = t_time();
		if (argv[5])
			menu->philo[i].meal_count = ft_atoi(argv[5]);
		else
			menu->philo[i].meal_count = -1;
		if (i == 0)
			menu->philo[i].time = t_time();
		else
			menu->philo[i].time = menu->philo[i - 1].time;
	}
}

void	menu_init(char **argv, t_menu *menu)
{
	sem_unlink("/sem_write");
	sem_unlink("/sem_meal");
	sem_unlink("/sem_last");
	sem_unlink("/sem_fork");
	menu->philo_count = ft_atoi(argv[1]);
	menu->philo = (t_philo *)malloc(sizeof(t_philo) * (menu->philo_count));
	philo_init(argv, menu, -1);
}
