/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:30:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/14 10:22:59 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_until_end(t_philo *lc_philo, int i)
{
	if (i + 1 == lc_philo->args->nbr_p)
		lc_philo->args->ready_odd = 1;
	if (i % 2 != 0)
	{
		while (lc_philo->args->ready_odd == 0)
			usleep(1000);
		usleep(1000);
	}
	while (lc_philo->args->nbr_p == 1 && lc_philo->args->philo_died == 0)
		usleep(1000);
}

void	*action_routine(void *data)
{
	int		i;
	t_philo	*lc_philo;

	lc_philo = (t_philo *)data;
	i = lc_philo->i;
	wait_until_end(lc_philo, i);
	while (lc_philo->args->philo_died == 0 && lc_philo->args->eat_enough == 0)
	{
		if (take_fork_right(lc_philo->args->start_time, lc_philo, i) == 1)
			break ;
		if (take_fork_left(lc_philo->args->start_time, lc_philo, i) == 1)
			break ;
		if (is_eating(lc_philo->args->start_time, lc_philo, i) == 1)
			break ;
		if (is_sleeping(lc_philo->args->start_time, lc_philo) == 1)
			break ;
		if (is_thinking(lc_philo->args->start_time, lc_philo) == 1)
			break ;
	}
	return (NULL);
}
