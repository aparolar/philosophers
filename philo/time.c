/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:09:30 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/13 11:59:37 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ulong   timestamp(void)
{
    struct timeval    t;

    gettimeofday(&t, 0);
    return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

ulong   time_diff(ulong past, ulong present)
{
    return (present - past);
}

int    cond_sleep(ulong time, t_philo_args *args)
{
    ulong   t;

    t = timestamp() + time;
    while (timestamp() < t && !args->dead)
        usleep(50);
    if (args->dead)
        return (1);
    return (0);
}
