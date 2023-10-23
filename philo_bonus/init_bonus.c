/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:25:16 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/23 14:56:19 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// int	fork_create(t_menu *menu)
// {
// 	int	i;

// 	i = -1;
// 	sem_unlink("/sem_write");
// 	sem_unlink("/sem_meal");
// 	sem_unlink("/sem_last");
// 	sem_unlink("/sem_fork");
// 	menu->die = -1;
// 	menu->eat = -1;
// 	return (0);
// }

// void	philo_init(t_philo *philo)
// {
// 	sem_unlink("/sem_write");
// 	sem_unlink("/sem_meal");
// 	sem_unlink("/sem_last");
// 	sem_unlink("/sem_fork");
	// philo->die = -1;
	// philo->eat = -1;
	// philo->die = &(menu->die);
	// philo->eat = &(menu->eat);
	// philo->eat_times = 0;
	// philo->fork = sem_open("/sem_fork", O_CREAT, S_IRWXU, philo->philo_count);
	// philo->last = sem_open("/sem_last", O_CREAT, S_IRWXU, 1);
	// philo->write = sem_open("/sem_write", O_CREAT, S_IRWXU, 1);
	// philo->meal = sem_open("/sem_meal", O_CREAT, S_IRWXU, 1);
	// philo->last_meal = t_time();
	// philo->time = t_time();
	// i = -1;
	// while (++i < philo->philo_count)
	// {
	// 	menu->philo[i] = *philo;
	// 	menu->philo[i].num = i + 1;
	// }
// }

// void	menu_init(char **argv, t_philo *philo, t_menu *menu)
// {
// 	philo->philo_count = ft_atoi(argv[1]);
// 	menu->philo = (t_philo *)malloc(sizeof(t_philo) * (philo->philo_count));
// 	menu->philo->time_to_die = ft_atoi(argv[2]);
// 	philo->time_to_eat = ft_atoi(argv[3]);
// 	philo->time_to_sleep = ft_atoi(argv[4]);
// 	philo->eat_times = 0;
// 	if (argv[5])
// 		philo->meal_count = ft_atoi(argv[5]);
// 	else
// 		philo->meal_count = -1;
// 	// philo_init(menu, philo, -1);
// 	// while (++i < philo->philo_count)
// 	// {
// 	// 	menu->philo[i] = *philo;
// 	// 	menu->philo[i].num = i + 1;
// 	// }
// }

// void	philo_init(char **argv, t_menu *menu, int i)
// {
// 	while (++i < menu->philo_count)
// 	{
// 		// menu->philo[i].num = i + 1;
// 		// menu->philo[i].die = &(menu->die);
// 		// menu->philo[i].eat = &(menu->eat);
// 		menu->philo[i].last = menu->last;
// 		menu->philo[i].write = menu->write;
// 		menu->philo[i].meal = menu->meal;
// 		menu->philo[i].left_fork = &menu->fork[i];
// 		if (i == menu->philo_count - 1)
// 			menu->philo[i].right_fork = &menu->fork[0];
// 		else
// 			menu->philo[i].right_fork = &menu->fork[i + 1];
// 		menu->philo[i].eat_times = 0;
// 		menu->philo[i].time_to_eat = menu->time_to_eat;
// 		menu->philo[i].time_to_sleep = menu->time_to_sleep;
// 		menu->philo[i].time_to_die = menu->time_to_die;
// 		menu->philo[i].last_meal = t_time();
// 		if (menu->meal_count > 0)
// 			menu->philo[i].meal_count = menu->meal_count;
// 		if (i == 0)
// 			menu->philo[i].time = t_time();
// 		else
// 			menu->philo[i].time = menu->philo[i - 1].time;
// 	}
// }

void	menu_init(char **argv, t_menu *menu, int i)
{
	sem_unlink("/sem_write");
	sem_unlink("/sem_meal");
	sem_unlink("/sem_last");
	sem_unlink("/sem_fork");
	menu->philo_count = ft_atoi(argv[1]);
	menu->philo = (t_philo *)malloc(sizeof(t_philo) * (menu->philo_count));
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
