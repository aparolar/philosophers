/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoso.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:26:08 by aparolar          #+#    #+#             */
/*   Updated: 2022/02/19 12:27:51 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philo)
{
	philo->died = 0;
	philo->lfork = philo->position;
	philo->rfork = (philo->lfork + 1) % philo->args->n_philos;
	philo->eat_count = 0;
	philo->max_eat_count = philo->args->must_eat_count;
	philo->last_eat = timestamp();
	return (pthread_create(&philo->thread_id, 0, philoso, (void *)philo));
}

void	*philoso(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	if (p->position % 2)
		usleep(500);
	p->last_eat = timestamp();
	while (!p->args->dead && p->args->eated)
	{
		if (!p->args->dead)
			doing_eat(p);
		else
			break ;
		p->eat_count++;
		if (p->max_eat_count && p->eat_count == p->max_eat_count)
		{
			pthread_mutex_lock(&p->args->write);
			p->args->eated--;
			pthread_mutex_unlock(&p->args->write);
			break ;
		}
		do_sleep_and_think(p);
	}
	return (0);
}
