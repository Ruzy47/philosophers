/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/23 15:29:11 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_t(t_menu *menu, int i)
{
	while (menu->philo[i].meal_count != -1 && i < menu->philo[i].philo_count
		&& menu->philo[i].eat_times >= menu->philo[i].meal_count && menu->philo[i].die != 1)
		i++;
	if (i == menu->philo[i].philo_count)
	{
		sem_wait(menu->philo[i].meal);
		menu->philo[i].eat = 1;
		sem_post(menu->philo[i].meal);
		printf("[%lld ms] everyone ate\n", get_time(&menu->philo[i], 0));
	}
}

void	routine2(t_philo *philo)
{
	sem_wait(philo->fork);
	p_printf("take left fork", philo);
	sem_wait(philo->fork);
	p_printf("take right fork", philo);
	s_sleep(philo, 1, 0);
	sem_wait(philo->last);
	p_printf("is eating", philo);
	philo->last_meal = get_time(philo, 0);
	sem_post(philo->last);
	sem_wait(philo->meal);
	philo->eat_times++;
	sem_post(philo->meal);
	sem_post(philo->fork);
	sem_post(philo->fork);
}

void	*check(void *info)
{
	t_menu	*menu;
	int		i;

	i = -1;
	menu = (t_menu *)info;
	while (++i < menu->philo_count)
	{
		printf("%lld\n", menu->philo[i].time);
		printf("%lld\n", get_time(&menu->philo[i], 0));
		if (get_time(&menu->philo[i], 0) - menu->philo[i].last_meal > menu->philo[i].time_to_die)
		{
			sem_wait(menu->philo[i].last);
			menu->philo[i].die = 1;
			sem_post(menu->philo[i].last);
			printf("[%lld ms] %d died\n", get_time(&menu->philo[i], 0), menu->philo[i].num);
		}
		sem_post(menu->philo[i].last);
	}
	check_t(menu, 0);
	return (NULL);
}

void	*routine(t_menu *menu, int i)
{
	if (menu->philo[i].num % 2)
		usleep(2000);
	pthread_create(&menu->philo[i].th, NULL, check, menu);
	while (!check2(&menu->philo[i]))
	{
		routine2(&menu->philo[i]);
		sem_wait(menu->philo[i].meal);
		if (menu->philo[i].eat == 1)
		{
			sem_post(menu->philo[i].meal);
			break ;
		}
		sem_post(menu->philo[i].meal);
		p_printf("is sleeping", &menu->philo[i]);
		s_sleep(&menu->philo[i], 0, 0);
		p_printf("is thinking", &menu->philo[i]);
	}
	pthread_join(menu->philo[i].th, NULL);
	if (menu->philo[i].die)
		exit(1);
	exit(0);
	return (NULL);
}

int	philo_create(t_menu *menu, int i)
{
	int	n[1];

	while (++i < menu->philo_count)
	{
		menu->philo[i].pid = fork();
		if (menu->philo[i].pid < 0)
			return (1);
		if (menu->philo[i].pid == 0)
			routine(menu, i);
	}
	i = -1;
	while (++i < menu->philo_count)
	{
		wait(n);
		if (n[0] > 0)
		{
			i = -1;
			while (++i < menu->philo_count)
				kill(menu->philo[i].pid, SIGKILL);
		}
	}
	return (0);
}
