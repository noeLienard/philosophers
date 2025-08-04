/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlienard <nlienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:07:24 by nlienard          #+#    #+#             */
/*   Updated: 2025/08/04 12:26:42 by nlienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	printf("%zu\n", args.nbr_p);
	printf("%zu\n", args.time_to_die);
	printf("%zu\n", args.time_to_eat);
	printf("%zu\n", args.time_to_sleep);
	printf("%zu\n", args.nbr_time);
*/

void	init_args(t_args *args, char **argv, int nb_args)
{
	args->nbr_p = ft_atoi(argv[0]);
	args->time_to_die = ft_atoi(argv[1]);
	args->time_to_eat = ft_atoi(argv[2]);
	args->time_to_sleep = ft_atoi(argv[3]);
	args->tab_philo1 = malloc(sizeof(int) * (args->nbr_p / 2));
	args->tab_philo2 = malloc(sizeof(int) * (args->nbr_p / 2));
	args->is_die = 0;
	if (nb_args == 6)
		args->nbr_time = ft_atoi(argv[4]);
}

// void ft_monitor(t_args *args)
// {

// }


void	create_threads(t_args args)
{
	pthread_t	tid;
	int			i;

	i = 0;
	while (i++ < args.nbr_p / 2)
	{
		args.i = i;
		pthread_create(&tid, NULL, action_routine, &args);
		pthread_join(tid, NULL);
		if (args.is_die == 1)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc != 5 && argc != 6)
		return (1);
	init_args(&args, &argv[1], argc);
	fill_tab(&args);
	create_threads(args);
	free(args.tab_philo1);
	free(args.tab_philo2);
	return (0);
}
