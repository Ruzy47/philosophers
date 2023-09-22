/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/22 14:05:29 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int fork_create(t_menu *menu, t_philo *philo)
{
    int 		i;
	
	i = -1;
    philo->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * menu->philo_count);
    while (++i <= menu->philo_count)
        if (pthread_mutex_init(philo->fork, NULL) != 0)
            return (1);
        //printf("aaa\n");
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

void	menu_init(char **argv, t_menu *menu, t_philo *philo)
{
    philo->eat_times = 0;
    menu->philo_count = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        philo->meal_count = ft_atoi(argv[5]);
}

int main(int argc, char **argv)
{
	t_philo	philo;
	t_menu	menu;

	if (argc > 6 || argc < 5)
		return (write(2, "Ruzik_ERROR\n", 13));
	menu_init(argv, &menu, &philo);
    //printf("aaa\n");
	if (ft_error(argv) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
       // printf("aaa\n");
    philo_init(&menu);
    //printf("aaa\n");
	if (fork_create(&menu, &philo) != 0 || philo_create(&menu, &philo) != 0)
		return (write(2, "Ruzik_ERROR\n", 13));
    //    printf("aaa\n");
    
}