/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:12:43 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/22 17:40:16 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;

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

int	printf_action(t_philo *philo, int timestamp, int number_philo, char *str)
{
	if (check_died(philo) == 1)
		return (1);
	if (printf("%dms %d %s\n", timestamp, number_philo, str) == -1)
		return (1);
	return (0);
}

int	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	free_and_destroy_all_mutex(t_args *args, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < args->nbr_p)
	{
		pthread_mutex_destroy(&args->mtx_fork[i]);
		pthread_mutex_destroy(&philo[i].mtx_meal);
		i++;
	}
	pthread_mutex_destroy(&args->mtx_state);
	free(philo);
	free(args->mtx_fork);
	return (1);
}
