/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:47:05 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/22 14:37:35 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*init_fork(int nbr_p)
{
	pthread_mutex_t	*mtx_fork;
	int				i;

	mtx_fork = malloc(sizeof(pthread_mutex_t) * nbr_p);
	if (!mtx_fork)
		return (NULL);
	i = 0;
	while (i < nbr_p)
	{
		if (pthread_mutex_init(&mtx_fork[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (mtx_fork);
}

t_philo	*init_philo(t_args *args)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * args->nbr_p);
	if (!philo)
		return (0);
	i = 0;
	while (i < args->nbr_p)
	{
		philo[i].idx = i + 1;
		philo[i].nbr_meal = 0;
		philo[i].last_meal = args->start_time;
		philo[i].i = i;
		philo[i].args = args;
		if (pthread_mutex_init(&philo[i].mtx_meal, NULL) != 0)
			free(philo);
		i++;
	}
	return (philo);
}

int	init_args(t_args *args, char **argv, int nb_args)
{
	args->nbr_p = ft_atoi(argv[0]);
	if (args->nbr_p < 1 || args->nbr_p > 300)
		return (1);
	args->time_to_die = ft_atoi(argv[1]);
	if (args->time_to_die < 1)
		return (1);
	args->time_to_eat = ft_atoi(argv[2]);
	if (args->time_to_eat < 1)
		return (1);
	args->time_to_sleep = ft_atoi(argv[3]);
	if (args->time_to_sleep < 1)
		return (1);
	if (nb_args == 6)
	{
		args->must_eat = ft_atoi(argv[4]);
		if (args->must_eat < 1)
			return (1);
	}
	else
		args->must_eat = 0;
	return (0);
}

int	init_all(t_args *args, char **argv, int nb_args)
{
	if (init_args(args, argv, nb_args) == 1)
		return (1);
	args->mtx_fork = init_fork(args->nbr_p);
	if (!args->mtx_fork)
		return (1);
	if (pthread_mutex_init(&args->mtx_state, NULL) != 0)
		return (free(args->mtx_fork), 1);
	return (0);
}
