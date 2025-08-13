/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:12:43 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/13 14:05:49 by nlienard         ###   ########.fr       */
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
	if (str[i] != '\0')
		return (0);
	return (res);
}


int	printf_action(int timestamp, int number_philo, char *str)
{
	if (printf("%dms %d %s\n", timestamp, number_philo, str) == -1)
		return (1);
	return (0);
}

int get_timestamp()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int unlock_mutex(t_philo *philo, int i, int j)
{
	if (pthread_mutex_unlock(&philo->args->mtx_fork[i]) != 0)
		return (1);
	if (j == 1)
	{
		if (pthread_mutex_unlock(&philo->args->mtx_fork[(i + 1)
			% philo->args->nbr_p]) != 0)
			return (1);
	}
	return (1);
}