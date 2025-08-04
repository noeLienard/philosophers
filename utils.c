/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:12:43 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:11 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int		res;

	i = 0;
	res = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void	fill_tab(t_args *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < args->nbr_p)
	{
		args->tab_philo1[j] = i;
		j++;
		i += 2;
	}
	i = 1;
	j = 0;
	while (i < args->nbr_p)
	{
		args->tab_philo2[j] = i;
		j++;
		i += 2;
	}
}

int	printf_action(int timestamp, int number_philo, char *str)
{
	if (printf("%d %d %s\n", timestamp, number_philo, str) == -1)
		return (-1);
	return (0);
}