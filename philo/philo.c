/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:36:21 by aparolar          #+#    #+#             */
/*   Updated: 2021/11/10 11:14:23 by aparolar         ###   ########.fr       */
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
		if (philo->n_philos > 0 && philo->dead_time > 0
			&& philo->eat_time > 0 && philo->sleep_time > 0)
			return (1);
		//if (argc == 6 && !philo->must_eat_count)
		//	philo->must_eat_count = -1;
	}
	return (0);
}

static int	start(t_philo_args *philo)
{
	pthread_t	tids[philo->n_philos];
	t_philo		philos[philo->n_philos];
	int			i;

	i = 0;
	philo->forks = malloc(sizeof(pthread_mutex_t *) * philo->n_philos);
	philo->philos = philos;
	philo->dead = 0;
	philo->start = get_time();
	pthread_mutex_init(&philo->write, 0);
	while (i < philo->n_philos)
	{
		pthread_mutex_init(&philo->forks[i], 0);
		i++;
	}
	i = 0;
	while (i < philo->n_philos)
	{
		philos[i].args = philo;
		philos[i].position = i;
		init_philo(&philos[i]);
		i++;
	}
	while (1) {
		//pthread_mutex_lock(&philo->write);
		if (philo->dead > 0)
		{
			//pthread_mutex_unlock(&philo->write);
			//printf("Finish\n");
			break ;
		}
		//pthread_mutex_unlock(&philo->write);
	}
	free(philo->forks);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_args	philo;

	if (get_args(argc, argv, &philo))
		start(&philo);
	system("valgrind ./philo");
	return (0);
}