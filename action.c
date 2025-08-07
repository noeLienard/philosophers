/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/07 12:13:19 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork_right(t_args *lc_args, int idx_philo)
{
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
		"has taken a fork");
	if (pthread_mutex_lock(&lc_args->mtx_fork[lc_args->i]) == EBUSY)
		return (1);
	return (0);
}

int	take_fork_left(t_args *lc_args, int idx_philo)
{
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
		"has taken a fork");
	if (pthread_mutex_lock(&lc_args->mtx_fork[lc_args->i + 1]) == EBUSY)
		return (1);
	return (0);
}

void	is_eating(t_args *lc_args, int idx_philo)
{
	usleep(lc_args->time_to_eat);
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
		"is eating");
	pthread_mutex_unlock(&lc_args->mtx_fork[lc_args->i]);
	pthread_mutex_unlock(&lc_args->mtx_fork[lc_args->i + 1]);
}

void	is_sleeping(t_args *lc_args, int idx_philo)
{
	usleep(lc_args->time_to_sleep);
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
		"is sleeping");
}

void	is_thinking(t_args *lc_args, int idx_philo)
{
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
		"is thinking");
}

int	ft_monitoring(t_args *lc_args)
{
	static bool	is_die = false;

	if (lc_args->philo_dead == true)
	{
		printf_action((get_timestamp() - lc_args->tv_start),
			lc_args->tab_philo[lc_args->i], "died");
		is_die = true;
	}
	if (is_die == true)
		return (0);
	return (1);
}
int	ready_to_eat(t_args *lc_args, int count)
{
	int	i;
	bool fork_r;
	bool fork_l;
	
	i = 0;
	fork_r = false;
	fork_l = false;
	while (count < lc_args->time_to_die)
	{
		if (take_fork_right(lc_args, lc_args->tab_philo[lc_args->i]) == 0)
			fork_r = true;
		if (take_fork_left(lc_args, lc_args->tab_philo[lc_args->i + 1]) == 0)
			fork_l = true;
		if (fork_r == true && fork_r == true)
			return (0);
		count++;
		usleep(1000);
	}
	lc_args->philo_dead = true;
	return (1);
}

void	*action_routine(void *args)
{
	struct timeval	tv;
	int				i;
	int				count;
	t_args			*lc_args;

	lc_args = (t_args *)args;
	i = 0;
	count = 0;
	if (lc_args->i == 0)
		lc_args->tv_start = get_timestamp();
	while (ft_monitoring(lc_args) == 1)
	{
		if (ready_to_eat(lc_args, count) == 1)
		{
			is_eating(lc_args, lc_args->tab_philo[lc_args->i]);
			is_sleeping(lc_args, lc_args->tab_philo[lc_args->i]);
			is_thinking(lc_args, lc_args->tab_philo[lc_args->i]);
		}
	}
	return (NULL);
}
