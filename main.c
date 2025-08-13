/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:07:24 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/13 12:09:46 by nlienard         ###   ########.fr       */
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
		pthread_mutex_init(&mtx_fork[i], NULL);
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
		i++;
	}
	return (philo);
}

int	init_args(t_args *args, char **argv, int nb_args)
{
	args->nbr_p = ft_atoi(argv[0]);
	if (args->nbr_p < 1 && args->nbr_p > 300)
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
	args->mtx_fork = init_fork(args->nbr_p);
	if (!args->mtx_fork)
		return (0);
	pthread_mutex_init(&args->mtx_print, NULL);
	args->start_time = 0;
	args->ready_odd = 0;
	args->philo_died = 0;
	args->eat_enough = 0;
	args->nbr_args = nb_args;
	return (0);
}
int free_and_destroy_all_mutex(t_args *args, t_philo *philo)
{
	int i;

	i = 0;
	while (i < args->nbr_p)
	{
		if (pthread_mutex_destroy(&args->mtx_fork[i]) != 0)
			return (0);
		i++;
	}
	pthread_mutex_destroy(&args->mtx_print);
	free(philo);
	free(args->mtx_fork);
	return(1);
}

void	create_threads(t_philo *philo, t_args *args)
{
	pthread_t	*tid;
	pthread_t	monitor;
	int			i;

	i = 0;
	tid = malloc(sizeof(pthread_t) * philo->args->nbr_p);
	if (!tid)
		return ;
	args->start_time = get_timestamp();
	while (i < philo->args->nbr_p)
	{
		pthread_create(&tid[i], NULL, action_routine, &philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, ft_monitoring, philo);
	i = 0;
	while (i < args->nbr_p)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	free_and_destroy_all_mutex(args, philo);
	free(tid);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_args	args;

	if (argc != 5 && argc != 6)
		return (printf("Invalid number of arguments\n"), 1);
	if (init_args(&args, &argv[1], argc) == 1)
		return (printf("Invalid arguments\n"), 1);
	philo = init_philo(&args);
	create_threads(philo, &args);
	return (0);
}
