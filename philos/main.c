/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/06/28 16:25:54 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int fork_create(t_menu *menu, t_philo *philo)
{
    int 		i;
	
	i = 0;
    philo->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * menu->philo_count);
	if (pthread_mutex_init(philo->fork, NULL) != 0)
		return (1);
    return (0);
}

void    philo_init(t_menu *menu)
{
    int     i;

    i = 0;
    menu->philo = (t_philo *)malloc(sizeof(t_philo) * menu->philo_count);
    while (++i <= menu->philo_count)
    {
        menu->philo[i].num = i;
        menu->philo[i].right_fork = i;
        if (i == menu->philo_count)
            menu->philo[i].left_fork = 1;
        else
            menu->philo[i].left_fork = i + 1;
        menu->philo[i].eat_times = 0;
    }
}

void	menu_init(char **argv, t_menu *menu)
{
    menu->philo_count = ft_atoi(argv[1]);
    menu->time_to_die = ft_atoi(argv[2]);
    menu->time_to_eat = ft_atoi(argv[3]);
    menu->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        menu->meal_count = ft_atoi(argv[5]);
}

int main(int argc, char **argv)
{
	t_philo	philo;
	t_menu	menu;

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	menu_init(argv, &menu);
	if (ft_error(argv) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
    philo_init(&menu);
	if (fork_create(&menu, &philo) != 0 || philo_create(&menu, &philo) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
}