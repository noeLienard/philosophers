/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelienard <noelienard@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:07:24 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/07 18:05:48 by noelienard       ###   ########.fr       */
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

t_philo *init_philo(t_args *args) {
	int i;
	t_philo *tab;
	tab = malloc(sizeof(t_philo) * args->nbr_p);
	if (!tab)
		return (0);
	i = 0;
	while (i < args->nbr_p)
	{
		tab[i].idx = i + 1;
		tab[i].nbr_meal = 0;
		tab[i].last_meal = 0;
		i++;
	}
	return (tab);
}

int	init_args(t_args *args, char **argv, int nb_args)
{
	args->nbr_p = ft_atoi(argv[0]);
	args->time_to_die = ft_atoi(argv[1]) * 1000;
	args->time_to_eat = ft_atoi(argv[2]) * 1000;
	args->time_to_sleep = ft_atoi(argv[3]) * 1000;
	if (nb_args == 6)
		args->nbr_time = ft_atoi(argv[4]);
	args->tab_philo = init_philo(args);
	if (!args->tab_philo)
		return (0);
	args->mtx_fork = init_fork(args->nbr_p);
	if (!args->mtx_fork)
	{
		free(args->tab_philo);
		return (0);
	}
	return (1);
}

void	create_threads(t_args args)
{
	pthread_t	tid[args.nbr_p];
	pthread_t 	monitor;
	
	args.i = 0;
	while (args.i < args.nbr_p)
	{
		pthread_create(&tid[args.i], NULL, action_routine, &args);
		usleep(1000);
		args.i++;
	}
	pthread_create(&monitor, NULL, ft_monitoring, &args);
	args.i = 0;
	while (args.i < args.nbr_p)
	{
		pthread_join(tid[args.i], NULL);
		args.i++;
	}
	pthread_join(monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc != 5 && argc != 6)
		return (1);
	init_args(&args, &argv[1], argc);
	printf("nbr_p :%d\ntime_to_die :%d\ntime_to_eat : %d\ntime_to_sleep : %d\n", args.nbr_p, args.time_to_die, args.time_to_eat, args.time_to_sleep);
	for (int i = 0; i < args.nbr_p; i++)
		printf("idx :%d\nbr meal : %d\nlast meal : %d\n", args.tab_philo[i].idx, args.tab_philo[i].nbr_meal, args.tab_philo[i].last_meal);
	create_threads(args);
	return (0);
}
