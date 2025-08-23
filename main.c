/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:07:24 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/22 16:05:13 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	unlock_mutex_fork(t_philo *philo, int fork1, int fork2)
{
	if (pthread_mutex_unlock(&philo->args->mtx_fork[fork1]) != 0)
		return (1);
	if (pthread_mutex_unlock(&philo->args->mtx_fork[fork2]) != 0)
		return (1);
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
		i++;
	}
	pthread_create(&monitor, NULL, ft_monitoring, philo);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < args->nbr_p)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	free_and_destroy_all_mutex(args, philo);
	free(tid);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_args	args;

	if (argc != 5 && argc != 6)
		return (printf("Invalid number of arguments\n"), 1);
	if (init_all(&args, &argv[1], argc) == 1)
		return (printf("Invalid arguments\n"), 1);
	args.philo_died = 0;
	args.eat_enough = 0;
	args.nbr_args = argc;
	philo = init_philo(&args);
	if (!philo)
		return (0);
	create_threads(philo, &args);
	return (0);
}
