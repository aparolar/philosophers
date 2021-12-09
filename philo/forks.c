/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:20:39 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/09 11:59:01 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int    take_forks(t_philo *philo)
{
	//if ((philo->position % 2))
	//{
	//	pthread_mutex_lock(&(philo->args->forks[philo->rfork]));
	//	show_status(philo, FORK);
	//	pthread_mutex_lock(&(philo->args->forks[philo->lfork]));
	//	show_status(philo, FORK);
	//}
	//else
	//{
		pthread_mutex_lock(&(philo->args->forks[philo->lfork]));
		show_status(philo, FORK);
		pthread_mutex_lock(&(philo->args->forks[philo->rfork]));
		show_status(philo, FORK);
	//}
	return (0);
}

void    clean_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->args->forks[philo->lfork]));
	pthread_mutex_unlock(&(philo->args->forks[philo->rfork]));
}

int	doing_eat(t_philo *philo)
{
	take_forks(philo);
	show_status(philo, EAT);
	pthread_mutex_lock(&philo->args->meal_check);
	cond_sleep(philo->args->eat_time, philo->args);
	clean_forks(philo);
	usleep(50);
	philo->last_eat = timestamp();
	show_status(philo, SLEEP);
	cond_sleep(philo->args->sleep_time, philo->args);
	pthread_mutex_unlock(&philo->args->meal_check);
	show_status(philo, THINK);
	if (philo->max_eat_count > 0)
	{
		philo->eat_count++;
		if (philo->eat_count > philo->max_eat_count)
			return (0);
	}
	return (1);
}
