/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:30:32 by aparolar          #+#    #+#             */
/*   Updated: 2021/11/09 17:54:33 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    show_status(t_philo *philo, char *status)
{
	__u_long	t;

	t = get_time() - philo->args->start;
	printf("%lu %d %s\n", t, philo->position + 1, status);
}

int     filo_death(t_philo *philo)
{
	if (get_time() > philo->limit)
		return (1);
	return (0);
}

__u_long	get_time()
{
	struct timeval time_now;
	
	gettimeofday(&time_now, 0);
	return (time_now.tv_sec * 1000000 + time_now.tv_usec);
}