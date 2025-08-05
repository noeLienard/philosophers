/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:12:43 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/05 14:11:09 by nlienard         ###   ########.fr       */
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
		args->tab_philo1[j] = malloc(sizeof(int) * 3);
		args->tab_philo1[j][0] = i;
		args->tab_philo1[j][1] = true; // Left fork
		args->tab_philo1[j][2] = true; // Right fork
		j++;
		i += 2;
	}
	i = 1;
	j = 0;
	// while (i < args->nbr_p)
	// {
	// 	args->tab_philo2[j] = malloc(sizeof(int) * 333);
	// 	args->tab_philo2[j][0] = i;
	// 	args->tab_philo1[j][1] = false; // Left fork
	// 	args->tab_philo1[j][2] = false; // Right fork
	// 	j++;
	// 	i += 2;
	// }
}

int	printf_action(int timestamp, int number_philo, char *str)
{
	if (printf("%dms %d %s\n", timestamp, number_philo, str) == -1)
		return (-1);
	return (0);
}

void free_tab(int *tab)
{
	int i;
	
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}