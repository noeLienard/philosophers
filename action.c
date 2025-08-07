/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelienard <noelienard@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/07 17:51:51 by noelienard       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork_right(t_args *lc_args, int idx_philo)
{
	if (pthread_mutex_lock(&lc_args->mtx_fork[lc_args->i]) == EBUSY)
		return (1);
	printf_action((get_timestamp()), idx_philo,
		"has taken a fork");
	return (0);
}

int	take_fork_left(t_args *lc_args, int idx_philo)
{
	if (pthread_mutex_lock(&lc_args->mtx_fork[lc_args->i + 1]) == EBUSY)
		return (1);
	printf_action((get_timestamp()), idx_philo,
		"has taken a fork");
	return (0);
}

int	is_eating(t_args *lc_args, int idx_philo)
{
	usleep(lc_args->time_to_eat);
	printf_action((get_timestamp()), idx_philo,
		"is eating");
	pthread_mutex_unlock(&lc_args->mtx_fork[lc_args->i]);
	pthread_mutex_unlock(&lc_args->mtx_fork[lc_args->i + 1]);
	return (1);
}

// int	is_sleeping(t_args *lc_args, int idx_philo)
// {
// 	usleep(lc_args->time_to_sleep);
// 	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
// 		"is sleeping");
// 	return (1);
// }

// int	is_thinking(t_args *lc_args, int idx_philo)
// {
// 	// pthread_mutex_lock(lc_args->mtx_print);
// 	printf_action((get_timestamp() - lc_args->tv_start), idx_philo,
// 		"is thinking");
// 	// pthread_mutex_unlock(lc_args->mtx_print);
// 	return (1);
// }

void	*ft_monitoring(void *args)
{
	bool	is_dead;
	int		i;
	t_args	*lc_args;
	t_philo	philo;

	is_dead = false;
	lc_args = (t_args *)args;
	lc_args->start_time = get_timestamp();
	while (is_dead == false)
	{
		i = 0;
		while (i < lc_args->nbr_p)
		{
			philo = lc_args->tab_philo[i];
			if (lc_args->start_time - philo.last_meal > lc_args->time_to_die)
			{
				printf_action((get_timestamp() - lc_args->start_time), i + 1, "died");
				is_dead = true;
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

void	*action_routine(void *args)
{
	t_args	*lc_args;

	lc_args = (t_args *)args;
	is_eating(lc_args, lc_args->tab_philo[lc_args->i].idx);
	is_sleeping(lc_args, lc_args->tab_philo[lc_args->i].idx);
	is_thinking(lc_args, lc_args->tab_philo[lc_args->i].idx);
	return (NULL);
}
