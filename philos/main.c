/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:05:17 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/16 19:44:43 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int fork_create(t_menu *menu)
{
	int	i;
	
	i = -1;
	menu->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (menu->philo_count));
	menu->write = malloc(sizeof(pthread_mutex_t));
	menu->eat_t = malloc(sizeof(pthread_mutex_t));
	menu->meal = malloc(sizeof(pthread_mutex_t));
	menu->die = -1;
	menu->eat = -1;
	while (++i < menu->philo_count)
		pthread_mutex_init(&menu->fork[i], NULL);
	pthread_mutex_init(menu->write, NULL);
	pthread_mutex_init(menu->eat_t, NULL);
	pthread_mutex_init(menu->meal, NULL);
	return (0);
}

void	philo_init(t_menu *menu, int i)
{
	while (++i < menu->philo_count)
	{
		menu->philo[i].num = i + 1;
		menu->philo[i].eat_times = 0;
		menu->philo[i].die = menu->die;
		menu->philo[i].eat = menu->eat;
		menu->philo[i].write = menu->write;
		menu->philo[i].p_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(menu->philo[i].p_mutex, NULL);
		menu->philo[i].left_fork = &menu->fork[i];
		if (i == menu->philo_count - 1)
			menu->philo[i].right_fork = &menu->fork[0];
		else
			menu->philo[i].right_fork = &menu->fork[i + 1];
		menu->philo[i].eat_times = 0;
		menu->philo[i].time_to_eat = menu->time_to_eat;
		menu->philo[i].time_to_sleep = menu->time_to_sleep;
		menu->philo[i].time_to_die = menu->time_to_die;
		menu->philo[i].last_meal = t_time();
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

int main(int argc, char **argv)
{
	t_menu	menu;

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	menu_init(argv, &menu);
	if (ft_error(argv) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	if (fork_create(&menu) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	philo_init(&menu, -1);
	if (philo_create(&menu) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
}