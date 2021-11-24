/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:09:30 by aparolar          #+#    #+#             */
/*   Updated: 2021/11/23 18:25:39 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ulong   timestamp()
{
    struct timeval    t;

    gettimeofday(&t, 0);
    return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

ulong   time_diff(ulong past, ulong present)
{
    return (present - past);
}

void    cond_sleep(ulong time, t_philo_args *args)
{
    ulong   t;

    t = timestamp() + time;
    while (timestamp() < t)
        usleep(100);
}