/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:25:16 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/22 15:05:57 by rugrigor         ###   ########.fr       */
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

void	philo_init(t_menu *menu, t_philo *philo, int i)
{
	sem_unlink("/sem_write");
	sem_unlink("/sem_meal");
	sem_unlink("/sem_last");
	sem_unlink("/sem_fork");
	philo->die = -1;
	philo->eat = -1;
	// philo->die = &(menu->die);
	// philo->eat = &(menu->eat);
	philo->eat_times = 0;
	philo->meal = sem_open("/sem_fork", O_CREAT, S_IRWXU, philo->philo_count);
	philo->last = sem_open("/sem_last", O_CREAT, S_IRWXU, 1);
	philo->write = sem_open("/sem_write", O_CREAT, S_IRWXU, 1);
	philo->meal = sem_open("/sem_meal", O_CREAT, S_IRWXU, 1);
	philo->last_meal = t_time();
	philo->time = t_time();
	i = -1;
	while (++i < philo->philo_count)
		menu->philo[i].num = i + 1;
}

void	menu_init(char **argv, t_philo *philo, t_menu *menu)
{
	philo->philo_count = ft_atoi(argv[1]);
	menu->philo = (t_philo *)malloc(sizeof(t_philo) * (philo->philo_count));
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->eat_times = 0;
	if (argv[5])
		philo->meal_count = ft_atoi(argv[5]);
	else
		philo->meal_count = -1;
}
