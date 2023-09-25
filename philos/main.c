/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:05:17 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/25 19:03:18 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int fork_create(t_menu *menu)
{
	int	i;
	
	i = -1;
	menu->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (menu->philo_count + 1));
	while (++i < menu->philo_count)
		pthread_mutex_init(&menu->fork[i], NULL);
	return (0);
}

void	philo_init(t_menu *menu, t_philo *philo)
{
	int i;

	i = -1;
	philo->eat_times = 0;

	while (++i < menu->philo_count)
	{
		menu->philo[i].num = i + 1;
		menu->philo[i].left_fork = &menu->fork[i];
		if (i == menu->philo_count - 1)
			menu->philo[i].right_fork = &menu->fork[0];
		else
			menu->philo[i].right_fork = &menu->fork[i + 1];
		menu->philo[i].eat_times = 0;
		menu->philo[i].time_to_eat = menu->time_to_eat;
		menu->philo[i].time_to_sleep = menu->time_to_sleep;
		if (menu->meal_count)
			menu->philo[i].meal_count = menu->meal_count;
		if (i == 0)
			menu->philo[i].time = 0;
		else
			menu->philo[i].time = menu->philo[i - 1].time;
	}
}

void	menu_init(char **argv, t_menu *menu)
{
	menu->philo_count = ft_atoi(argv[1]);
	menu->philo = (t_philo *)malloc(sizeof(t_philo) * (menu->philo_count + 1));
	menu->time_to_die = ft_atoi(argv[2]);
	menu->time_to_eat = ft_atoi(argv[3]);
	menu->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		menu->meal_count = ft_atoi(argv[5]);
}

int main(int argc, char **argv)
{
	t_menu	menu;
	t_philo	philo;

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	philo.time = 0;
	philo.eat_times = 0;
	menu_init(argv, &menu);
	if (ft_error(argv) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	if (fork_create(&menu) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
	philo_init(&menu, &philo);
	if (philo_create(&menu) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
}