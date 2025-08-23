/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/23 21:40:32 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_usleep(long time)
{
	long start;
	long now;
	start = get_timestamp();
	while (1)
	{
		now = get_timestamp();
		if ((now - start) >= time)
			break ;
		usleep(500);
	}
}

int	check_died(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->args->mtx_state) != 0)
		return (1);
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (pthread_mutex_unlock(&philo->args->mtx_state), 1);
	if (pthread_mutex_unlock(&philo->args->mtx_state) != 0)
		return (pthread_mutex_unlock(&philo->args->mtx_state), 1);
	return (0);
}
