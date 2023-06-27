/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/06/27 15:43:44 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char **argv)
{
	int	i;
	int	y;
	
	i = 0;
	y = -1;
	while (argv[++i])
	{
		if (i == 1 && ft_atoi(argv[i]) < 2)
			return (1);
		else if (i != 1 && ft_atoi(argv[i]) < 0)
			return (1);
		y = -1;
		while (argv[i][++y])
		{
			if (argv[i][y] < '0' && argv[i][y] > '9')
				return(1);
		}
	}
	return (0);
}