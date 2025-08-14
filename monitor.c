/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:27:59 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/14 13:00:48 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_someone_died(t_philo *lc_philo, int i)
{
	if (get_timestamp() - lc_philo[i].last_meal > lc_philo->args->time_to_die
		|| lc_philo->args->nbr_p == 1)
	{
		if (pthread_mutex_lock(&lc_philo[i].args->mtx_print) != 0)
			return (0);
		printf_action((get_timestamp() - lc_philo[i].args->start_time), i + 1,
			"died");
		lc_philo->args->philo_died = 1;
		if (pthread_mutex_unlock(&lc_philo[i].args->mtx_print) != 0)
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
		while (i < lc_philo->args->nbr_p)
		{
			if (check_someone_died(lc_philo, i) == 0)
				return (NULL);
			if (lc_philo->args->must_eat != 0
				&& lc_philo[i].nbr_meal >= lc_philo->args->must_eat)
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
