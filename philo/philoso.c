/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoso.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:26:08 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/13 16:18:57 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo)
{
	int			ret;

	philo->died = 0;
	philo->lfork = philo->position;
	philo->rfork = (philo->lfork + 1) % philo->args->n_philos;
	philo->eat_count = 0;
	philo->max_eat_count = philo->args->must_eat_count;
	philo->last_eat = timestamp();
	ret = pthread_create(&philo->thread_id, 0, philoso, (void *)philo);
	if (ret)
		printf("No se ha podido crear el hilo %d\n", philo->position);
}

void	*philoso(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	if (p->position % 2)
		usleep(500);
	p->last_eat = timestamp();
	while (!p->args->dead && p->args->eated < p->args->n_philos)
	{
		doing_eat(p);
		if (p->max_eat_count > 0 && p->eat_count >= p->max_eat_count)
		{		
			pthread_mutex_lock(&p->args->write);
			p->args->eated++;
			pthread_mutex_unlock(&p->args->write);
		}
	}
	return (0);
}
