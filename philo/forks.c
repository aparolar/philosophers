/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:20:39 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/13 16:27:10 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->forks[philo->lfork]));
	show_status(philo, FORK);
	if (philo->lfork != philo->rfork)
	{
		pthread_mutex_lock(&(philo->args->forks[philo->rfork]));
		show_status(philo, FORK);
		return (1);
	}
	else
	{
		cond_sleep(philo->args->dead_time + 50, philo->args);
		return (0);
	}
}

static void	clean_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->args->forks[philo->lfork]));
	pthread_mutex_unlock(&(philo->args->forks[philo->rfork]));
}

void	doing_eat(t_philo *philo)
{
	if (take_forks(philo))
	{
		show_status(philo, EAT);
		if (philo->args->eated + 1 >= philo->args->must_eat_count)
			return ;
		if (!cond_sleep(philo->args->eat_time, philo->args))
			clean_forks(philo);
		else
		{
			clean_forks(philo);
			return ;
		}
		if (philo->max_eat_count > 0)
			philo->eat_count++;
		usleep(100);
		if (philo->args->eated >= philo->args->must_eat_count)
			return ;
		philo->last_eat = timestamp();
		show_status(philo, SLEEP);
		if (philo->args->eated >= philo->args->must_eat_count)
			return ;
		if (cond_sleep(philo->args->sleep_time, philo->args))
			return ;
		show_status(philo, THINK);
	}
	else
		clean_forks(philo);
}
