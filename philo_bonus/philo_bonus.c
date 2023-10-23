/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/23 20:15:20 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check2(t_philo *philo)
{
	if (get_time(philo, 0) - philo->last_meal > philo->time_to_die)
	{
		sem_wait(philo->last);
		philo->die = 1;
		sem_post(philo->last);
		printf("[%lld ms] %d died\n", get_time(philo, 0), philo->num);
		return (1);
	}
	return (0);
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
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)info;
	while (1)
	{
		if (get_time(philo, 0) - philo->last_meal > philo->time_to_die)
		{
			sem_wait(philo->last);
			philo->die = 1;
			sem_post(philo->last);
			sem_wait(philo->write);
			printf("[%lld ms] %d died\n", get_time(philo, 0), philo->num);
			sem_post(philo->write);
			exit (1);
		}
		i = 0;
		sem_wait(philo->meal);
		if (philo->meal_count != -1 && philo->eat_times >= philo->meal_count)
		{
			sem_post(philo->meal);
			break ;
		}
		sem_post(philo->meal);
	}
	return (NULL);
}

void	*routine(t_menu *menu, int i)
{
	pthread_create(&menu->philo[i].th, NULL, check, &menu->philo[i]);
	// if (menu->philo[i].num % 2)
	// 	usleep(1000);
	while (!check2(&menu->philo[i]))
	{
		routine2(&menu->philo[i]);
		sem_wait(menu->philo[i].meal);
		if (menu->philo[i].meal_count != -1 && menu->philo[i].eat_times
			>= menu->philo[i].meal_count)
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
		usleep(500);
	}
	i = -1;
	while (++i < menu->philo_count)
	{
		waitpid(-1, n, 0);
		if (n[0] > 0)
		{
			i = -1;
			while (++i < menu->philo_count)
				kill(menu->philo[i].pid, SIGKILL);
		}
	}
	return (0);
}
