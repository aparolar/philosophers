/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:20:39 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/10 05:52:59 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->forks[philo->lfork]));
	show_status(philo, FORK);
	pthread_mutex_lock(&(philo->args->forks[philo->rfork]));
	show_status(philo, FORK);
}

void    clean_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->args->forks[philo->lfork]));
	pthread_mutex_unlock(&(philo->args->forks[philo->rfork]));
}

void	doing_eat(t_philo *philo)
{
	take_forks(philo);
	show_status(philo, EAT);
	cond_sleep(philo->args->eat_time, philo->args);
	clean_forks(philo);
	usleep(60);
	philo->last_eat = timestamp();
	show_status(philo, SLEEP);
	cond_sleep(philo->args->sleep_time, philo->args);
	show_status(philo, THINK);
	if (philo->max_eat_count > 0)
		philo->eat_count++;
}
