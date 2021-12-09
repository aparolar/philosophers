/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:30:32 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/09 18:57:52 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    show_status(t_philo *philo, char *status)
{
	if (!philo->args->dead)
	{
		pthread_mutex_lock(&philo->args->write);
		///*putstr_fd no funciona?¿
		ft_putnbr_fd(timestamp() - philo->args->start, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->position + 1, 1);
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(status, 1);
		ft_putstr_fd("\n", 1);
		//*/
		//printf("%8lu %2d %s\n", timestamp() - philo->args->start, philo->position + 1, status);
		pthread_mutex_unlock(&philo->args->write);
	}
}
