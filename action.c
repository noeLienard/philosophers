/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/04 13:35:07 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

void	is_eating(t_args *lc_args, struct timeval tv, int i)
{
    pthread_mutex_lock(&mutex);
    gettimeofday(&tv, NULL);
    printf_action(tv.tv_usec, lc_args->tab_philo1[i], "has taken a fork");
    gettimeofday(&tv, NULL);
    printf_action(tv.tv_usec, lc_args->tab_philo1[i], "is eating");
    usleep(lc_args->time_to_eat);
    pthread_mutex_unlock(&mutex);
}

void	is_sleeping(t_args *lc_args, struct timeval tv, int i)
{
	gettimeofday(&tv, NULL);
	printf_action(tv.tv_usec, lc_args->tab_philo1[i], "is sleeping");
	usleep(lc_args->time_to_sleep);
}

void	is_thinking(t_args *lc_args, struct timeval tv, int i)
{
	gettimeofday(&tv, NULL);
	printf_action(tv.tv_usec, lc_args->tab_philo1[i], "is thinking");
	usleep(lc_args->time_to_die);
}

void	*action_routine(void *args)
{
	struct timeval	tv;
	t_args			*lc_args;

	lc_args = (t_args *)args;
    while (ft_monitoring() == 1)
    {
        is_eating(lc_args, tv, lc_args->i);
        is_sleeping(lc_args, tv, lc_args->i);
        is_thinking(lc_args, tv, lc_args->i);
    }
    printf_action(tv.tv_usec, lc_args->tab_philo1[lc_args->i], "is died");
	return (NULL);
}