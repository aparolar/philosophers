/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:52:33 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/21 14:21:07 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	start(t_philo_args *args)
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
			if ((int)time_diff(p.last_eat, timestamp()) > args->dead_time
				&& args->eated)
			{
				pthread_mutex_lock(&args->write);
				args->dead = 1;
				pthread_mutex_unlock(&args->write);
				usleep(100);
				print_status(&p, DIED);
			}
			usleep(100);
		}
	}
	uninitialize(args);
	return (0);
}
