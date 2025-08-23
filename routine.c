/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelienard <noelienard@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:30:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/23 17:25:10 by noelienard       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_philosopher(t_philo *lc_philo)
{
	while (lc_philo->args->nbr_p == 1)
	{
		if (pthread_mutex_lock(&lc_philo->args->mtx_state) != 0)
			return (1);
		if (lc_philo->args->philo_died == 1)
		{
			pthread_mutex_unlock(&lc_philo->args->mtx_state);
			return (1);
		}
		if (pthread_mutex_unlock(&lc_philo->args->mtx_state) != 0)
			return (1);
		usleep(1000);
	}
	return (0);
}

int	choose_fork_and_eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->args->mtx_fork[philo->fork[0]]) != 0)
		return (1);
	if (printf_action(philo, (get_timestamp() - philo->args->start_time), philo->idx,
		"has taken a fork") == 1)
		return ();
	if (pthread_mutex_lock(&philo->args->mtx_fork[philo->fork[1]]) != 0)
		return (1);
	if (printf_action(philo, (get_timestamp() - philo->args->start_time), philo->idx,
		"has taken a fork") == 1)
		return (1);
	if (is_eating(philo) == 1)
		return (unlock_mutex_fork(philo, philo->fork[0], philo->fork[1]));
	return (unlock_mutex_fork(philo, philo->fork[0], philo->fork[1]), 0);
}

void	*action_routine(void *data)
{
	int		i;
	t_philo	*lc_philo;

	lc_philo = (t_philo *)data;
	i = lc_philo->i;
	if (one_philosopher(lc_philo) == 1)
		return (NULL);
	if (i % 2 == 1)
		usleep(1000);
	while (check_died(lc_philo) == 0)
	{
		if (choose_fork_and_eat(lc_philo) == 1)
			return (NULL); ;
		if (printf_action(lc_philo, (get_timestamp()
					- lc_philo->args->start_time), lc_philo->idx,
				"is sleeping") == 1)
			return (NULL);
		precise_usleep(lc_philo->args->time_to_sleep);
		if (printf_action(lc_philo, (get_timestamp()
					- lc_philo->args->start_time), lc_philo->idx,
				"is thinking") == 1)
			return (NULL);
	}
	return (NULL);
}
