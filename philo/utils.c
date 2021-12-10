/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:30:32 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/10 06:12:38 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    show_status(t_philo *philo, char *status)
{
	if (!philo->args->dead)
	{
		pthread_mutex_lock(&philo->args->write);
		ft_putnbr_fd(timestamp() - philo->args->start, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->position + 1, 1);
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(status, 1);
		ft_putstr_fd("\n", 1);
		pthread_mutex_unlock(&philo->args->write);
	}
}
