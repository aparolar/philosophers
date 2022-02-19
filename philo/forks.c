/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:20:39 by aparolar          #+#    #+#             */
/*   Updated: 2022/02/19 11:11:57 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->forks[philo->lfork]));
	show_status(philo, FORK);
	if (philo->lfork != philo->rfork && !philo->args->dead)
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
	if (!philo->args->dead && take_forks(philo))
	{
		show_status(philo, EAT);
		if (!cond_sleep(philo->args->eat_time, philo->args))
			clean_forks(philo);
		else
		{
			clean_forks(philo);
			return ;
		}
		philo->last_eat = timestamp();
	}
	else
		clean_forks(philo);
}

void	do_sleep_and_think(t_philo *philo)
{
	if (!philo->args->dead && philo->args->eated)
		show_status(philo, SLEEP);
	if (!cond_sleep(philo->args->sleep_time, philo->args)
		&& !philo->args->dead
		&& philo->args->eated)
		show_status(philo, THINK);
}
