/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoso.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:26:08 by aparolar          #+#    #+#             */
/*   Updated: 2021/11/21 22:07:38 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_philo(t_philo *philo)
{
	pthread_t	tid;
	int			ret;

	philo->is_eating = 0;
	philo->lfork = philo->position;
	philo->rfork = (philo->lfork + 1) % philo->args->n_philos;
	philo->eat_count = 0;
	philo->max_eat_count = philo->args->must_eat_count;
	philo->start = philo->args->start;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->args->dead_time;
	if (philo->lfork != philo->rfork)
	{
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

	philo = (t_philo *)args;
	while (1)
	{
		take_forks(philo);
		doing_eat(philo);
		doing_sleep(philo);
		doing_think(philo);
		if (philo->max_eat_count > 0 && philo->eat_count >= philo->max_eat_count)
		{		
			pthread_mutex_lock(&philo->args->write);
			philo->args->eated++;
			pthread_mutex_unlock(&philo->args->write);
			break ;
		}
		if (filo_death(philo))
			break ;
	}
	return (0);
}
