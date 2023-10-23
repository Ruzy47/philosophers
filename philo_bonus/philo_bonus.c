/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/22 15:39:03 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_t(t_philo *philo, int i)
{
	while (philo->meal_count != -1 && i < philo->philo_count
		&& philo[i].eat_times >= philo->meal_count && philo->die != 1)
			i++;
	if (i == philo->philo_count)
	{
		sem_wait(philo->meal);
		philo->eat = 1;
		sem_post(philo->meal);
		printf("[%lld ms] everyone ate\n", get_time(&philo[0], 0));
	}
}

void	routine2(t_philo	*philo)
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
	while (++i < philo->philo_count)
	{
		if (get_time(&philo[i], 0) - philo[i].last_meal > philo->time_to_die)
		{
			sem_wait(philo->last);
			philo->die = 1;
			sem_post(philo->last);
			printf("[%lld ms] %d died\n", get_time(&philo[0], 0), philo[i].num);
		}
		sem_post(philo->last);
	}
	check_t(philo, 0);
	return (NULL);
}

void	*routine(t_philo	*philo)
{
	if (philo->num % 2)
		usleep(2000);
	pthread_create(&philo->th, NULL, check, philo);
	while (!check2(philo))
	{
		routine2(philo);
		sem_wait(philo->meal);
		if (philo->eat == 1)
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

int	philo_create(t_menu *menu, t_philo *philo, int i)
{
	int	n[1];
	
	// printf("%d\n", philo->philo_count);
	while (++i < philo->philo_count)
	{
		philo[i] = menu->philo[i];
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (1);
		if (philo[i].pid == 0)
		{
			printf("%d\n", i);
			printf("aaa\n");
			routine(&philo[i]);
		}
		usleep(50);
	}
	i = -1;
	while (++i < philo->philo_count)
	{
		waitpid(-1, n, 0);
		if (n[0] > 0)
		{
			i = -1;
			while (++i < philo->philo_count)
				kill(menu->philo[i].pid, SIGKILL);
		}
	}
	return (0);
}
