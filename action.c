/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/08 15:50:22 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork_right(t_args *lc_args, t_philo *philo, int i)
{
	pthread_mutex_lock(&lc_args->mtx_fork[i]);
	pthread_mutex_lock(&lc_args->mtx_print);
	printf_action((get_timestamp() - lc_args->start_time), philo->idx,
		"has taken a fork");
	pthread_mutex_unlock(&lc_args->mtx_print);
	return (0);
}

int	take_fork_left(t_args *lc_args, t_philo *philo, int i)
{
	pthread_mutex_lock(&lc_args->mtx_fork[(i + 1) % lc_args->nbr_p]);
	pthread_mutex_lock(&lc_args->mtx_print);
	printf_action((get_timestamp() - lc_args->start_time), philo->idx,
		"has taken a fork");
	pthread_mutex_unlock(&lc_args->mtx_print);
	return (0);
}

int	is_eating(t_args *lc_args, t_philo *philo, int i)
{
	pthread_mutex_lock(&lc_args->mtx_print);
	usleep(lc_args->time_to_eat);
	printf_action((get_timestamp() - lc_args->start_time), philo->idx,
		"is eating");
	pthread_mutex_unlock(&lc_args->mtx_print);
	philo->nbr_meal++;
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&lc_args->mtx_fork[i]);
	pthread_mutex_unlock(&lc_args->mtx_fork[(i + 1) % lc_args->nbr_p]);
	return (1);
}

int	is_sleeping(t_args *lc_args, t_philo *philo)
{
	pthread_mutex_lock(&lc_args->mtx_print);
	usleep(lc_args->time_to_sleep);
	printf_action((get_timestamp() - lc_args->start_time), philo->idx,
		"is sleeping");
	pthread_mutex_unlock(&lc_args->mtx_print);
	return (1);
}

int	is_thinking(t_args *lc_args, t_philo *philo)
{
	pthread_mutex_lock(&lc_args->mtx_print);
	printf_action((get_timestamp() - lc_args->start_time), philo->idx,
		"is thinking");
	pthread_mutex_unlock(&lc_args->mtx_print);
	return (1);
}

void	*ft_monitoring(void *args)
{
	bool	is_dead;
	int		i;
	t_args	*lc_args;
	t_philo	philo;

	is_dead = false;
	lc_args = (t_args *)args;
	while (is_dead == false)
	{
		i = 0;
		while (i < lc_args->nbr_p)
		{
			philo = lc_args->tab_philo[i];
			if (lc_args->start_time - philo.last_meal > lc_args->time_to_die)
			{
				pthread_mutex_lock(&lc_args->mtx_print);
				printf_action((get_timestamp() - lc_args->start_time), i + 1,
					"died");
				is_dead = true;
				pthread_mutex_unlock(&lc_args->mtx_print);
				exit(1);
			}
			i++;
		}
	}
	exit(1);
	return (NULL);
}

void	*action_routine(void *args)
{
	int i;
	t_args	*lc_args;
	lc_args = (t_args *)args;
	i = lc_args->i;
	if (i % 2 != 0)
		usleep(1000);
	while (1)
	{
		take_fork_right(lc_args, &lc_args->tab_philo[i], i);
		take_fork_left(lc_args, &lc_args->tab_philo[i], i);	
		is_eating(lc_args, &lc_args->tab_philo[i], i);
		is_sleeping(lc_args, &lc_args->tab_philo[i]);
		is_thinking(lc_args, &lc_args->tab_philo[i]);
	}
	return (NULL);
}
