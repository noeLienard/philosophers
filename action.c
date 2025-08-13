/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/13 14:40:05 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork_right(int start_time, t_philo *philo, int i)
{
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (1);
	if (pthread_mutex_lock(&philo->args->mtx_fork[i]) != 0)
		return (1);
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 0));
	if (pthread_mutex_lock(&philo->args->mtx_print) != 0)
		return (unlock_mutex(philo, i, 0));
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 0));
	printf_action((get_timestamp() - philo->args->start_time), philo->idx,
		"has taken a fork");
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 0));
	if (pthread_mutex_unlock(&philo->args->mtx_print) != 0)
		return (unlock_mutex(philo, i, 0));
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 0));
	return (0);
}

int	take_fork_left(int start_time, t_philo *philo, int i)
{
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 0));
	if (pthread_mutex_lock(&philo->args->mtx_fork[(i + 1)
				% philo->args->nbr_p]) != 0)
		return (unlock_mutex(philo, i, 0));
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 1));
	if (pthread_mutex_lock(&philo->args->mtx_print) != 0)
		return (unlock_mutex(philo, i, 1));
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 1));
	printf_action((get_timestamp() - philo->args->start_time), philo->idx,
		"has taken a fork");
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 1));
	if (pthread_mutex_unlock(&philo->args->mtx_print) != 0)
		return (unlock_mutex(philo, i, 1));
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 1));
	return (0);
}

int	is_eating(int start_time, t_philo *philo, int i)
{
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 1));
	if (pthread_mutex_lock(&philo->args->mtx_print) != 0)
		return (unlock_mutex(philo, i, 1));
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 1));
	philo->last_meal = get_timestamp();
	printf_action((get_timestamp() - philo->args->start_time), philo->idx,
		"is eating");
	if (pthread_mutex_unlock(&philo->args->mtx_print) != 0)
		return (unlock_mutex(philo, i, 1));
	usleep(philo->args->time_to_eat * 1000);
	philo->nbr_meal++;
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (unlock_mutex(philo, i, 1));
	if (pthread_mutex_unlock(&philo->args->mtx_fork[i]) != 0)
		return (pthread_mutex_unlock(&philo->args->mtx_fork[(i + 1)
					% philo->args->nbr_p]), 0);
	if (pthread_mutex_unlock(&philo->args->mtx_fork[(i + 1)
				% philo->args->nbr_p]) != 0)
		return (1);
	return (0);
}

int	is_sleeping(int start_time, t_philo *philo)
{
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (1);
	if (pthread_mutex_lock(&philo->args->mtx_print) != 0)
		return (1);
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (1);
	printf_action((get_timestamp() - start_time), philo->idx, "is sleeping");
	if (pthread_mutex_unlock(&philo->args->mtx_print) != 0)
		return (1);
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (1);
	usleep(philo->args->time_to_sleep * 1000);
	return (0);
}

int	is_thinking(int start_time, t_philo *philo)
{
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (1);
	if (pthread_mutex_lock(&philo->args->mtx_print) != 0)
		return (1);
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (1);
	printf_action((get_timestamp() - start_time), philo->idx, "is thinking");
	if (pthread_mutex_unlock(&philo->args->mtx_print) != 0)
		return (1);
	if (philo->args->philo_died == 1 || philo->args->eat_enough == 1)
		return (1);
	return (0);
}
