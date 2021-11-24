/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoso.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:26:08 by aparolar          #+#    #+#             */
/*   Updated: 2021/11/23 18:49:41 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_philo(t_philo *philo)
{
	pthread_t	tid;
	int			ret;

	philo->died = 0;
	philo->lfork = philo->position;
	philo->rfork = (philo->lfork + 1) % philo->args->n_philos;
	philo->eat_count = 0;
	philo->max_eat_count = philo->args->must_eat_count;
	philo->start = timestamp();//philo->args->start;
	philo->limit = philo->last_eat + philo->args->dead_time;
	if (philo->lfork != philo->rfork)
	{
		philo->last_eat = timestamp();
		ret = pthread_create(&philo->thread_id, 0, philoso, (void *)philo);
		if (ret)
			printf("No se ha podido crear el hilo %d\n", philo->position);
	}
	else
	{
		show_status(philo, DIED);
		philo->args->dead++;
	}
}

void    *philoso(void *args)
{
	t_philo	*philo;
	int	dead;

	philo = (t_philo *)args;
	if (philo->position % 2)
		usleep(500);
	//pthread_mutex_lock(&philo->args->meal_check)
	pthread_mutex_lock(&philo->args->meal_check);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&philo->args->meal_check);
	dead = 0;
	while (!dead)
	{
		//take_forks(philo);
		doing_eat(philo);
		//doing_sleep(philo);
		//doing_think(philo);
		/*
		if (philo->max_eat_count > 0 && philo->eat_count >= philo->max_eat_count)
		{		
			pthread_mutex_lock(&philo->args->write);
			philo->args->eated++;
			pthread_mutex_unlock(&philo->args->write);
			break ;
		}*/
		
		pthread_mutex_lock(&philo->args->write);
		if (philo->args->dead)
			dead = 1;
		pthread_mutex_unlock(&philo->args->write);

	}
	return (0);
}
