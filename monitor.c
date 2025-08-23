/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:27:59 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/22 17:43:15 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_someone_died(t_philo *lc_philo, int i)
{
	if (pthread_mutex_lock(&lc_philo[i].mtx_meal) != 0)
		return (0);
	if (get_timestamp() - lc_philo[i].last_meal > lc_philo->args->time_to_die
		|| lc_philo->args->nbr_p == 1)
	{
		if (pthread_mutex_unlock(&lc_philo[i].mtx_meal) != 0)
			return (0);
		if (lc_philo->args->nbr_p == 1)
			usleep(lc_philo->args->time_to_die * 1000);
		if (pthread_mutex_lock(&lc_philo[i].args->mtx_state) != 0)
			return (0);
		lc_philo->args->philo_died = 1;
		if (pthread_mutex_unlock(&lc_philo[i].args->mtx_state) != 0)
			return (0);
		if (pthread_mutex_lock(&lc_philo->args->mtx_print) != 0)
			return (0);
		if (printf("%dms %d %s\n", get_timestamp()
				- lc_philo[i].args->start_time, i + 1, "died") == -1)
			return (pthread_mutex_unlock(&lc_philo->args->mtx_print), 1);
		if (pthread_mutex_unlock(&lc_philo->args->mtx_print) != 0)
			return (0);
		return (0);
	}
	if (pthread_mutex_unlock(&lc_philo[i].mtx_meal) != 0)
		return (0);
	return (1);
}

int	check_each_philo(t_philo *lc_philo, int i, int j)
{
	while (i < lc_philo->args->nbr_p)
	{
		if (check_someone_died(lc_philo, i) == 0)
			return (0);
		if (pthread_mutex_lock(&lc_philo[i].mtx_meal) != 0)
			return (0);
		if (lc_philo->args->must_eat != 0
			&& lc_philo[i].nbr_meal >= lc_philo->args->must_eat)
			j++;
		if (pthread_mutex_unlock(&lc_philo[i].mtx_meal) != 0)
			return (0);
		i++;
	}
	if (j == lc_philo->args->nbr_p && lc_philo->args->nbr_args == 6)
	{
		if (pthread_mutex_lock(&lc_philo->args->mtx_state) != 0)
			return (0);
		lc_philo->args->eat_enough = 1;
		if (pthread_mutex_unlock(&lc_philo->args->mtx_state) != 0)
			return (0);
		return (0);
	}
	return (1);
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
		if (check_each_philo(lc_philo, i, j) == 0)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
