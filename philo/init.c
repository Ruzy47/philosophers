/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:25:16 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/24 17:40:38 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_create(t_menu *menu)
{
	int	i;

	i = -1;
	menu->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (menu->philo_count));
	menu->last = malloc(sizeof(pthread_mutex_t));
	menu->write = malloc(sizeof(pthread_mutex_t));
	menu->meal = malloc(sizeof(pthread_mutex_t));
	menu->die = -1;
	menu->eat = -1;
	while (++i < menu->philo_count)
		pthread_mutex_init(&menu->fork[i], NULL);
	pthread_mutex_init(menu->write, NULL);
	pthread_mutex_init(menu->meal, NULL);
	pthread_mutex_init(menu->last, NULL);
	return (0);
}

void	philo_init(t_menu *menu, int i)
{
	while (++i < menu->philo_count)
	{
		menu->philo[i].die = &(menu->die);
		menu->philo[i].eat = &(menu->eat);
		menu->philo[i].last = menu->last;
		menu->philo[i].write = menu->write;
		menu->philo[i].meal = menu->meal;
		menu->philo[i].left_fork = &menu->fork[i];
		menu->philo[i].right_fork = &menu->fork[i + 1];
		if (i == menu->philo_count - 1)
			menu->philo[i].right_fork = &menu->fork[0];
		if (menu->philo_count == 1)
			menu->philo[i].right_fork = NULL;
		menu->philo[i].eat_times = 0;
		menu->philo[i].time_to_eat = menu->time_to_eat;
		menu->philo[i].time_to_sleep = menu->time_to_sleep;
		menu->philo[i].time_to_die = menu->time_to_die;
		menu->philo[i].last_meal = 0;
		if (menu->meal_count > 0)
			menu->philo[i].meal_count = menu->meal_count;
		if (i == 0)
			menu->philo[i].time = t_time();
		else
			menu->philo[i].time = menu->philo[i - 1].time;
	}
}

void	menu_init(char **argv, t_menu *menu)
{
	menu->philo_count = ft_atoi(argv[1]);
	menu->philo = (t_philo *)malloc(sizeof(t_philo) * (menu->philo_count));
	menu->time_to_die = ft_atoi(argv[2]);
	menu->time_to_eat = ft_atoi(argv[3]);
	menu->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		menu->meal_count = ft_atoi(argv[5]);
	else
		menu->meal_count = -1;
}
