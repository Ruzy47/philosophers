/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/06/21 17:59:31 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(t_philo *philo)
{
	int	i;
	int	y;
	
	i = 0;
	y = -1;
	while (philo->pargv[++i])
	{
		if (philo->pargv[1][0] == 48)
			return (1);
		y = -1;
		while (philo->pargv[i][++y])
		{
			if (philo->pargv[i][y] <= 47 && philo->pargv[i][y] >= 57)
				return(1);
		}
	}
	return (0);
}