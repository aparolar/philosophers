/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:20:39 by aparolar          #+#    #+#             */
/*   Updated: 2021/11/09 17:51:05 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->lfork]);
	show_status(philo, FORK);
	pthread_mutex_lock(&philo->args->forks[philo->rfork]);
	show_status(philo, FORK);
}

void    clean_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->args->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->args->forks[philo->rfork]);
}

int	doing_eat(t_philo *philo)
{
	show_status(philo, EAT);
	usleep(philo->args->eat_time * 1000);
	clean_forks(philo);
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->args->dead_time * 1000;
	//printf("%d %d %d\n", philo->position + 1, philo->max_eat_count, philo->eat_count);
	if (philo->max_eat_count > 0)
	{
		philo->eat_count++;
		if (philo->eat_count >= philo->max_eat_count)
			return (0);
	}
	return (1);
}

void    doing_sleep(t_philo *philo)
{
	show_status(philo, SLEEP);    
	usleep(philo->args->sleep_time * 1000);
}

void    doing_think(t_philo *philo)
{
	show_status(philo, THINK);
}