/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:09:30 by aparolar          #+#    #+#             */
/*   Updated: 2022/02/19 12:30:32 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ulong	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, 0);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

t_ulong	time_diff(t_ulong past, t_ulong present)
{
	return (present - past);
}

int	cond_sleep(t_ulong time, t_philo_args *args)
{
	t_ulong	t;

	t = timestamp() + time;
	while (timestamp() < t && !args->dead)
		usleep(50);
	if (args->dead || !args->eated)
		return (1);
	return (0);
}
