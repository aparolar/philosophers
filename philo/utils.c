/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:30:32 by aparolar          #+#    #+#             */
/*   Updated: 2021/11/22 23:56:58 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    show_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->args->write);
	if (!philo->args->dead)
		printf("%lu %d %s\n", timestamp() - philo->args->start, philo->position + 1, status);
	pthread_mutex_unlock(&philo->args->write);
}
/*
int     filo_death(t_philo *philo)
{
	//printf("%lu > %lu\n", get_time() - philo->last_eat, philo->args->dead_time);
	pthread_mutex_lock(&philo->args->write);
	if (philo->args->dead)
	{
		pthread_mutex_unlock(&philo->args->write);
		pthread_exit(0);
	}
	pthread_mutex_unlock(&philo->args->write);

	if (get_time() - philo->last_eat > philo->args->dead_time)
	{
		//if (philo->args->dead == 0)
		show_status(philo, DIED);
		pthread_mutex_lock(&philo->args->write);
		//philo->args->dead++;
		if (philo->args->dead > 1)
		{
			pthread_mutex_unlock(&philo->args->write);
			pthread_exit(0);
		}
		pthread_mutex_unlock(&philo->args->write);
		
		return (1);
	}
	return (0);
}

ulong	get_time()
{
	struct timeval time_now;
	
	gettimeofday(&time_now, 0);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}
/*
int	if_death_time(t_philo *p)
{

}*/