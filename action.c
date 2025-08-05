/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/05 14:31:22 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

void	take_fork(t_args *lc_args, struct timeval tv, int tab_philo)
{
	gettimeofday(&tv, NULL);
	printf_action((tv.tv_usec - lc_args->tv_start.tv_usec), tab_philo,
		"has taken a fork");
    
}

void	is_eating(t_args *lc_args, struct timeval tv, int tab_philo)
{
	pthread_mutex_lock(&mutex);
	gettimeofday(&tv, NULL);
	printf_action(tv.tv_usec, tab_philo, "is eating");
	usleep(lc_args->time_to_eat);
	pthread_mutex_unlock(&mutex);
}

void	is_sleeping(t_args *lc_args, struct timeval tv, int tab_philo)
{
	gettimeofday(&tv, NULL);
	printf_action((tv.tv_usec - lc_args->tv_start.tv_usec), tab_philo,
		"is sleeping");
	usleep(lc_args->time_to_sleep);
}

void	is_sleeping(t_args *lc_args, struct timeval tv, int tab_philo)
{
	gettimeofday(&tv, NULL);
	printf_action((tv.tv_usec - lc_args->tv_start.tv_usec), tab_philo,
		"is sleeping");
	usleep(lc_args->time_to_sleep);
}

void	is_thinking(t_args *lc_args, struct timeval tv, int tab_philo)
{
	gettimeofday(&tv, NULL);
	printf_action((tv.tv_usec - lc_args->tv_start.tv_usec), tab_philo,
		"is thinking");
}

void	is_dead(t_args *lc_args, struct timeval tv, int tab_philo)
{
	gettimeofday(&tv, NULL);
	printf_action((tv.tv_usec - lc_args->tv_start.tv_usec), tab_philo,
		"died");
}

int	ft_monitoring(t_args *args, struct timeval tv)
{
    if (args->tab_philo1[args->i][1] == true)
            take_fork(args,tv, args->tab_philo1[args->i]);
    if (args->tab_philo1[args->i + 1][2] == true)
            take_fork(args,tv, args->tab_philo1[args->i]);
}

void	*action_routine(void *args)
{
	struct timeval tv;
    int i;
	t_args *lc_args;

	lc_args = (t_args *)args;
    i = 0;
	if (lc_args->i == 0)
		gettimeofday(&lc_args->tv_start, NULL);
	while (1)
	{
		while (ft_monitoring(lc_args,tv) == 1)
        {
            usleep(1);
            i++;
            if (i >= lc_args->time_to_die)
            {
                is_dead(lc_args, tv,lc_args->tab_philo1[lc_args->i]);
                exit(1);
            }
        }
        is_eating(lc_args,tv, lc_args->tab_philo1);
        is_sleeping(lc_args,tv, lc_args->tab_philo1);
        is_thinking(lc_args,tv, lc_args->tab_philo1);
	}
	return (NULL);
}
