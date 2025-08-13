/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:52 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/13 14:16:27 by nlienard         ###   ########.fr       */
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

void	*ft_monitoring(void *data)
{
	t_philo	*lc_philo;
	int		i;
	int		j;

	lc_philo = (t_philo *)data;
	while (1)
	{
		i = 0;
		j = 0;
		while (i < lc_philo->args->nbr_p)
		{
			if (get_timestamp()
				- lc_philo[i].last_meal > lc_philo->args->time_to_die
				|| lc_philo->args->nbr_p == 1)
			{
				if (pthread_mutex_lock(&lc_philo[i].args->mtx_print) != 0)
					return (NULL);
				printf_action((get_timestamp() - lc_philo[i].args->start_time),
					i + 1, "died");
				lc_philo->args->philo_died = 1;
				if (pthread_mutex_unlock(&lc_philo[i].args->mtx_print) != 0)
					return (NULL);
				return (NULL);
			}
			if (lc_philo[i].nbr_meal >= lc_philo->args->must_eat)
				j++;
			i++;
		}
		if (j == lc_philo->args->nbr_p && lc_philo->args->nbr_args == 6)
		{
			lc_philo->args->eat_enough = 1;
			break ;
		}
	}
	return (NULL);
}

void	*action_routine(void *data)
{
	int		i;
	t_philo	*lc_philo;

	lc_philo = (t_philo *)data;
	i = lc_philo->i;
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
