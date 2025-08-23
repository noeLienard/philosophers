/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/22 17:52:16 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void precise_usleep(long duration_ms)
{
    long start = get_timestamp();
    while (get_timestamp() - start < duration_ms)
        usleep(50);
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

int	take_fork(t_philo *philo, int fork)
{
	if (pthread_mutex_lock(&philo->args->mtx_fork[fork]) != 0)
		return (1);
	if (printf_action(philo, (get_timestamp() - philo->args->start_time), philo->idx,
		"has taken a fork") == 1)
		return (1);
	return (0);
}

int	is_eating(t_philo *philo)
{
	if (printf_action(philo, (get_timestamp() - philo->args->start_time), philo->idx,
		"is eating") == 1)
		return (1);
	precise_usleep(philo->args->time_to_eat);
	if (pthread_mutex_lock(&philo->mtx_meal) != 0)
		return (1);
	philo->last_meal = get_timestamp();
	philo->nbr_meal++;
	if (pthread_mutex_unlock(&philo->mtx_meal) != 0)
		return (1);
	return (0);
}

