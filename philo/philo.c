/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:36:21 by aparolar          #+#    #+#             */
/*   Updated: 2021/11/23 00:05:11 by aparolar         ###   ########.fr       */
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
		if (argc > 5)
			philo->must_eat_count = ft_atoi(argv[5]);
		else
			philo->must_eat_count = 0;
		if (philo->n_philos > 0 && philo->dead_time >= 6 
			&& philo->eat_time >= 60 && philo->sleep_time >= 60)
			return (1);
	}
	return (0);
}

static void	initialize(t_philo_args *args)
{
	int	i;

	pthread_mutex_init(&args->write, 0);
	pthread_mutex_init(&args->meal_check, 0);
	args->forks = malloc(sizeof(pthread_mutex_t *) * args->n_philos);
	args->philos = malloc(sizeof(t_philo) * args->n_philos);
	args->dead = 0;
	args->eated = 0;
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

static void	unitialize(t_philo_args *args)
{
	int i;

	i = args->n_philos;
	while (args->n_philos > 0 && --i >= 0)
		pthread_join(args->philos[i].thread_id, 0);
	i = args->n_philos;
	while (args->n_philos > 0 && --i >= 0)
		pthread_mutex_destroy(&args->forks[i]);
	pthread_mutex_destroy(&args->write);
	pthread_mutex_destroy(&args->meal_check);
	free(args->philos);
	free(args->forks);
}

static int	start(t_philo_args *philo)
{
	int			end;
	int	i;

	initialize(philo);
	end = 0;
	while (!end) {
		i = philo->n_philos;
		while (--i >= 0 && !end)
		{
			pthread_mutex_lock(&philo->meal_check);
			//printf("%lu > %lu\n", time_diff(philo->philos[i].last_eat, timestamp()), philo->dead_time);
			if (time_diff(philo->philos[i].last_eat, timestamp()) > philo->dead_time)
			{
				show_status(&philo->philos[i], DIED);
				pthread_mutex_lock(&philo->write);
				philo->dead = 1;
				end = 1;
				//break;
				pthread_mutex_unlock(&philo->write);
			}
		/*
		if (philo->dead > 0 || philo->eated == philo->n_philos)
		{	
			pthread_mutex_unlock(&philo->write);
			break ;
		}*/
			pthread_mutex_unlock(&philo->meal_check);
			//usleep(100);
		}
	}
	printf("Salimos\n");
	unitialize(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_args	philo;

	if (get_args(argc, argv, &philo))
		start(&philo);
	//system("valgrind ./philo");
	return (0);
}