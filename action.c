/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/06 12:08:21 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

void	take_fork(t_args *lc_args, struct timeval tv, int idx_philo)
{
	gettimeofday(&tv, NULL);
	printf_action((tv.tv_usec - lc_args->tv_start.tv_usec), idx_philo,
		"has taken a fork");
}

void	is_eating(t_args *lc_args, struct timeval tv, int idx_philo)
{
	pthread_mutex_lock(&mutex);
	gettimeofday(&tv, NULL);
	printf_action((tv.tv_usec - lc_args->tv_start.tv_usec), idx_philo,
		"is eating");
	usleep(lc_args->time_to_eat);
	pthread_mutex_unlock(&mutex);
	lc_args->tab_philo[lc_args->i][1] = true;
	lc_args->tab_philo[lc_args->i + 1][1] = true;
}

void	is_sleeping(t_args *lc_args, struct timeval tv, int idx_philo)
{
	gettimeofday(&tv, NULL);
	printf_action((tv.tv_usec - lc_args->tv_start.tv_usec), idx_philo,
		"is sleeping");
	usleep(lc_args->time_to_sleep);
}

void	is_thinking(t_args *lc_args, struct timeval tv, int idx_philo)
{
	gettimeofday(&tv, NULL);
	printf_action((tv.tv_usec - lc_args->tv_start.tv_usec), idx_philo,
		"is thinking");
}

void	is_dead(t_args *lc_args, struct timeval tv, int idx_philo)
{
	gettimeofday(&tv, NULL);
	printf_action((tv.tv_usec - lc_args->tv_start.tv_usec), idx_philo, "died");
}

int	ft_monitoring(t_args *lc_args, struct timeval tv, int count)
{
	if (count == 0 && lc_args->i % 2 == 0)
	{
		take_fork(lc_args, tv, lc_args->tab_philo[lc_args->i][0]);
		lc_args->tab_philo[lc_args->i][1] = false;
		take_fork(lc_args, tv, lc_args->tab_philo[lc_args->i][0]);
		lc_args->tab_philo[lc_args->i + 1][1] = false;
		return (0);
	}
	ft_printf("ok\n\n");
	if (lc_args->tab_philo[lc_args->i][1] == true && lc_args->tab_philo[lc_args->i + 1][1] == true)
		return (0);
	return (1);
}

void	*action_routine(void *args)
{
	struct timeval	tv;
	int				i;
	int count;
	t_args			*lc_args;

	lc_args = (t_args *)args;
	i = 0;
	count = 0;
	if (lc_args->i == 0)
		gettimeofday(&lc_args->tv_start, NULL);
	while (1)
	{
		while (ft_monitoring(lc_args, tv, count) == 1)
		{
			if (i == lc_args->time_to_die)
			{
				is_dead(lc_args, tv, lc_args->tab_philo[lc_args->i][0]);
				exit(1);
			}
			usleep(1);
			i++;
		}
		is_eating(lc_args, tv, lc_args->tab_philo[lc_args->i][0]);
		is_sleeping(lc_args, tv, lc_args->tab_philo[lc_args->i][0]);
		is_thinking(lc_args, tv, lc_args->tab_philo[lc_args->i][0]);
		count++;
	}
	return (NULL);
}
