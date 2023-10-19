/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:52:54 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/18 00:26:22 by rugrigor         ###   ########.fr       */
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
			if (argv[i][y] < 48 || argv[i][y] > 57)
				return(1);
		}
	}
	return (0);
}