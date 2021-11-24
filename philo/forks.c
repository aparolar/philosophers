/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:20:39 by aparolar          #+#    #+#             */
/*   Updated: 2021/11/23 18:51:45 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int    take_forks(t_philo *philo)
{
	if ((philo->position % 2))
	{
		usleep(200);
		pthread_mutex_lock(&(philo->args->forks[philo->rfork]));
		show_status(philo, FORK);
		pthread_mutex_lock(&(philo->args->forks[philo->lfork]));
		show_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&(philo->args->forks[philo->lfork]));
		show_status(philo, FORK);
		pthread_mutex_lock(&(philo->args->forks[philo->rfork]));
		show_status(philo, FORK);
	}
	return (0);
}

void    clean_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->args->forks[philo->lfork]));
	pthread_mutex_unlock(&(philo->args->forks[philo->rfork]));
}

int	doing_eat(t_philo *philo)
{
	/*
		problemas, se pierde mucho tiempo con los mutex,
		 intentar no usar mutex en show_status
		 hay un lapsus de 200ms aprox con el tiempo de muerte
		 los mutex detienen innecesariamente los hilos
		 buscar alternativas con otras variables locales
	*/
	//printf("pre eat lock\n");
	printf("pre eat %lu %d\n", time_diff(philo->last_eat, timestamp()), philo->position + 1);
	take_forks(philo);
	show_status(philo, EAT);
	pthread_mutex_lock(&philo->args->meal_check);
	cond_sleep(philo->args->eat_time, philo->args);
	clean_forks(philo);
	printf("pos eat %lu %d\n", time_diff(philo->last_eat, timestamp()), philo->position +1 );
	philo->last_eat = timestamp();
	
	//pthread_mutex_unlock(&philo->args->meal_check);
	//pthread_mutex_lock(&philo->args->meal_check);
	//philo->last_eat = timestamp();
	//pthread_mutex_unlock(&philo->args->meal_check);
	printf("pre slp %lu %d\n", time_diff(philo->last_eat, timestamp()), philo->position + 1);
	//pthread_mutex_lock(&philo->args->meal_check);
	show_status(philo, SLEEP);
	cond_sleep(philo->args->sleep_time, philo->args);
	pthread_mutex_unlock(&philo->args->meal_check);
	show_status(philo, THINK);
	printf("pos slp %lu %d\n", time_diff(philo->last_eat, timestamp()), philo->position + 1);
//	doing_think(philo);
	//printf("endind eat\n");
	if (philo->max_eat_count > 0)
	{
		philo->eat_count++;
		if (philo->eat_count > philo->max_eat_count)
			return (0);
	}
	return (1);
}

void    doing_sleep(t_philo *philo)
{
}

void    doing_think(t_philo *philo)
{
}