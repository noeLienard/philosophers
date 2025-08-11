/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/11 14:45:11 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork_right(int start_time, t_philo *philo, int i)
{
	if (pthread_mutex_lock(&philo->args->mtx_fork[i]) != 0)
		exit(1);
	if (pthread_mutex_lock(&philo->args->mtx_print) != 0)
		exit(1);
	printf_action((get_timestamp() - philo->args->start_time), philo->idx,
		"has taken a fork");
	if (pthread_mutex_unlock(&philo->args->mtx_print) != 0)
		exit(1);
	return (0);
}

int	take_fork_left(int start_time, t_philo *philo, int i)
{
	if (pthread_mutex_lock(&philo->args->mtx_fork[(i + 1) % philo->args->nbr_p]) != 0)
		exit(1);
	if (pthread_mutex_lock(&philo->args->mtx_print) != 0)
		exit(1);
	printf_action((get_timestamp() - philo->args->start_time), philo->idx,
		"has taken a fork");
	if (pthread_mutex_unlock(&philo->args->mtx_print) != 0)
		exit(1);
	return (0);
}

int	is_eating(int start_time, t_philo *philo, int i)
{
	if (pthread_mutex_lock(&philo->args->mtx_print) != 0)
		exit(1);
	usleep(philo->args->time_to_eat);
	printf_action((get_timestamp() - philo->args->start_time), philo->idx,
		"is eating");
	if (pthread_mutex_unlock(&philo->args->mtx_print) != 0)
		exit(1);
	philo->nbr_meal++;
	philo->last_meal = get_timestamp();
	if (pthread_mutex_unlock(&philo->args->mtx_fork[i]) != 0)
		exit(1);
	if (pthread_mutex_unlock(&philo->args->mtx_fork[(i + 1) % philo->args->nbr_p]) != 0)
		exit(1);
	return (1);
}

int	is_sleeping(int start_time, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->args->mtx_print) != 0)
		exit(1);
	usleep(philo->args->time_to_sleep);
	printf_action((get_timestamp() - start_time), philo->idx,
		"is sleeping");
	if (pthread_mutex_unlock(&philo->args->mtx_print) != 0)
		exit(1);
	return (1);
}

int	is_thinking(int start_time, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->args->mtx_print) != 0)
		exit(1);
	printf_action((get_timestamp() - start_time), philo->idx,
		"is thinking");
	if (pthread_mutex_unlock(&philo->args->mtx_print) != 0)
		exit(1);
	return (1);
}

void	*ft_monitoring(void *data)
{
	t_philo *lc_philo;
	bool	is_dead;
	int		i;
	
	is_dead = false;
	lc_philo = (t_philo *)data;
	while (is_dead == false)
	{
		i = 0;
		while (i < lc_philo[i].args->nbr_p)
		{
			if (lc_philo[i].args->start_time- lc_philo[i].last_meal > lc_philo[i].args->time_to_die)
			{
				if (pthread_mutex_lock(&lc_philo[i].args->mtx_print) != 0)
					exit(1);
				printf_action((get_timestamp() - lc_philo[i].args->start_time), i + 1,
					"died");
				is_dead = true;
				if (pthread_mutex_unlock(&lc_philo[i].args->mtx_print) != 0)
					exit(1);
				exit(1);
			}
			i++;
		}
	}
	exit(1);
	return (NULL);
}

void	*action_routine(void *data)
{
	int		i;
	t_philo	*lc_philo;

	lc_philo = (t_philo *)data;
	i = lc_philo->i;
	// if (i + 1 == lc_philo->args->nbr_p)
	// 	lc_philo->args->ready_odd = true;
	// else if (i % 2 != 0)
	// {
	// 	while (lc_philo->args->ready_odd == false)
	// 		usleep(1000);	
	// }
	 if (i % 2 != 0)
	 	usleep(1000);
	while (1)
	{
		take_fork_right(lc_philo->args->start_time, lc_philo, i);
		take_fork_left(lc_philo->args->start_time, lc_philo, i);
		is_eating(lc_philo->args->start_time, lc_philo, i);
		is_sleeping(lc_philo->args->start_time, lc_philo);
		is_thinking(lc_philo->args->start_time, lc_philo);
	}
	return (NULL);
}
