/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/24 14:51:47 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	printf("check1 : %lld\n", t_time());
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
		sem_wait(philo->meal);
		if (philo->meal_count != -1 && philo->eat_times >= philo->meal_count)
		{
			sem_post(philo->meal);
			break ;
		}
		sem_post(philo->meal);
	}
	printf("check2 : %lld\n", t_time());
	return (NULL);
}

void	*routine(t_philo *philo)
{
	printf("rout : %lld\n", t_time());
	pthread_create(&philo->th, NULL, check, philo);
	printf("%lld\n", t_time());
	if (philo->num % 2)
		usleep(1000);
	while (!check2(philo))
	{
		routine2(philo);
		sem_wait(philo->meal);
		if (philo->meal_count != -1 && philo->eat_times >= philo->meal_count)
		{
			sem_post(philo->meal);
			break ;
		}
		sem_post(philo->meal);
		p_printf("is sleeping", philo);
		s_sleep(philo, 0, 0);
		p_printf("is thinking", philo);
	}
	pthread_join(philo->th, NULL);
	if (philo->die)
		exit(1);
	exit(0);
	return (NULL);
}

void	close2(t_menu *menu,  int i)
{
	int	n;

	while (++i < menu->philo_count)
	{
		waitpid(menu->philo[i].pid, &n, 0);
		if (n > 0)
		{
			i = -1;
			while (++i < menu->philo_count)
				kill(menu->philo[i].pid, SIGKILL);
			break ;
		}
	}
	sem_close(menu->philo[0].fork);
	sem_close(menu->philo[0].meal);
	sem_close(menu->philo[0].last);
	sem_close(menu->philo[0].write);
	sem_unlink("/sem_write");
	sem_unlink("/sem_meal");
	sem_unlink("/sem_last");
	sem_unlink("/sem_fork");
}

int	philo_create(t_menu *menu, int i)
{
	// int		n;
	t_philo	*philo;

	philo = menu->philo;
	printf("a %lld\n", t_time());
	while (++i < menu->philo_count)
	{
		printf("b %lld\n", t_time());
		philo[i].pid = fork();
			printf("c %lld\n", t_time());
		if (philo[i].pid == 0)
			routine(&philo[i]);
		if (philo[i].pid < 0)
			return (1);
		// waitpid(menu->philo[i].pid, &n, 0);
		// if (n > 0)
		// 	kill(menu->philo[i].pid, SIGKILL);
		// break ;	
	}
	close2(menu, -1);
	return (0);
}
