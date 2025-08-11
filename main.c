/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:07:24 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/11 15:05:35 by nlienard         ###   ########.fr       */
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
		philo[i].last_meal = 0;
		philo[i].i = i;
		philo[i].args = args;
		i++;
	}
	return (philo);
}

int	init_args(t_args *args, char **argv, int nb_args)
{
	args->nbr_p = ft_atoi(argv[0]);
	args->time_to_die = ft_atoi(argv[1]) * 1000;
	args->time_to_eat = ft_atoi(argv[2]) * 1000;
	args->time_to_sleep = ft_atoi(argv[3]) * 1000;
	if (nb_args == 6)
		args->must_eat = ft_atoi(argv[4]);
	args->mtx_fork = init_fork(args->nbr_p);
	if (!args->mtx_fork)
		return (0);
	pthread_mutex_init(&args->mtx_print, NULL);
	args->start_time = 0;
	return (1);
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
		usleep(1000);
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
}

/*
ft_printf("Philosophers Number : %d\nTime to eat : %d\nTime to die :
	%d\nTime to sleep : %d\n", args.nbr_p, args.time_to_eat, args.time_to_die,
	args.time_to_sleep);
ft_printf("---------------------------Philo---------------------------\n");
for (size_t i = 0; i < args.nbr_p; i++)
ft_printf("Idx : %d\nLast meal : %d\nNumbers meal : %d\n", philo[i].idx,
	philo[i].last_meal, philo[i].nbr_meal);
*/

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_args	args;

	if (argc != 5 && argc != 6)
		return (1);
	init_args(&args, &argv[1], argc);
	philo = init_philo(&args);
	create_threads(philo, &args);
	return (0);
}
