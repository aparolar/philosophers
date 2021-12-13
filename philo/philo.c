/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:36:21 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/13 22:23:22 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_args(int argc, char **argv, t_philo_args *philo)
{
	if (argc >= 5 && philo)
	{
		philo->n_philos = ft_atoi(argv[1]);
		philo->dead_time = ft_atoi(argv[2]);
		philo->eat_time = ft_atoi(argv[3]);
		philo->sleep_time = ft_atoi(argv[4]);
		philo->must_eat_count = 0;
		if (argc == 6)
			philo->must_eat_count = ft_atoi(argv[5]);
		if (philo->n_philos > 0
			&& philo->dead_time >= 60
			&& philo->eat_time >= 60
			&& philo->sleep_time >= 60
			&& philo->must_eat_count >= 0)
			return (1);
	}
	return (0);
}

static void	initialize(t_philo_args *args)
{
	int	i;

	pthread_mutex_init(&args->write, 0);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->n_philos);
	args->philos = malloc(sizeof(t_philo) * args->n_philos);
	args->dead = 0;
	args->eated = args->n_philos;
	args->start = timestamp();
	i = args->n_philos;
	while (--i >= 0)
		pthread_mutex_init(&args->forks[i], 0);
	i = 0;
	while (i < args->n_philos)
	{
		args->philos[i].args = args;
		args->philos[i].position = i;
		init_philo(&args->philos[i]);
		i++;
	}
}

static void	uninitialize(t_philo_args *args)
{
	int	i;

	i = args->n_philos;
	while (args->n_philos > 0 && --i >= 0)
		pthread_join(args->philos[i].thread_id, 0);
	i = args->n_philos;
	while (args->n_philos > 0 && --i >= 0)
		pthread_mutex_destroy(&args->forks[i]);
	pthread_mutex_destroy(&args->write);
	free(args->philos);
	free(args->forks);
}

static int	start(t_philo_args *args)
{
	int			i;
	t_philo		p;

	initialize(args);
	while (!args->dead && args->eated)
	{
		i = args->n_philos;
		while (--i >= 0 && !args->dead && args->eated)
		{
			p = args->philos[i];
			if (time_diff(p.last_eat, timestamp()) > args->dead_time
				&& args->eated)
			{
				pthread_mutex_lock(&args->write);
				args->dead = 1;
				pthread_mutex_unlock(&args->write);
				usleep(500);
				print_status(&p, DIED);
			}
			usleep(100);
		}
	}
	uninitialize(args);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_args	philo;

	if (get_args(argc, argv, &philo))
		start(&philo);
	else
	{
		printf("Error.\n");
		printf("Command arguments are : \n");
		printf("\tphilo n_philos dead_time eat_time sleep_time [must_eats]\n");
		printf("\tn_philos must be greather of 0\n");
		printf("\tdead_time,\n");
		printf("\teat_time and\n");
		printf("\tsleep_time : needs to be equal or greather of 60\n");
		printf("\t[must_eats] is optional no negative numbers\n");
	}
	//system("valgrind ./philo");
	return (0);
}
