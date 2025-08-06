/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/06 17:16:12 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	mutex_fork_r = PTHREAD_MUTEX_INITIALIZER;

void	take_fork_right(t_args *lc_args, struct timeval tv, int idx_philo)
{
	pthread_mutex_lock(&lc_args->mutex_fork_r);
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
		"has taken a fork");
}

void	take_fork_left(t_args *lc_args, struct timeval tv, int idx_philo)
{
	pthread_mutex_lock(&lc_args->mutex_fork_l);
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
		"has taken a fork");
}

void	is_eating(t_args *lc_args, struct timeval tv, int idx_philo)
{
	usleep(lc_args->time_to_eat);
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
		"is eating");
	pthread_mutex_unlock(&lc_args->mutex_fork_l);
	pthread_mutex_unlock(&lc_args->mutex_fork_r);
}

void	is_sleeping(t_args *lc_args, struct timeval tv, int idx_philo)
{
	usleep(lc_args->time_to_sleep);
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
		"is sleeping");
}

void	is_thinking(t_args *lc_args, struct timeval tv, int idx_philo)
{
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
		"is thinking");
}

void	is_dead(t_args *lc_args, struct timeval tv, int idx_philo)
{
	printf_action((get_timestamp() - lc_args->tv_start), idx_philo, "died");
}

int	ft_monitoring(t_args *lc_args, struct timeval tv, int count)
{
	if (count == lc_args->time_to_die)
	{
		is_dead(lc_args, tv, lc_args->tab_philo[lc_args->i]);
		return (0);
	}
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
	while (ft_monitoring(lc_args, tv, count) == 1)
	{
		if (ready_to_eat())
		{
			is_eating(lc_args, tv, lc_args->tab_philo[lc_args->i]);
			is_sleeping(lc_args, tv, lc_args->tab_philo[lc_args->i]);
			is_thinking(lc_args, tv, lc_args->tab_philo[lc_args->i]);
		}
		count++;
		usleep(1);
	}
	return (NULL);
}
