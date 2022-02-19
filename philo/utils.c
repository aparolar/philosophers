/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:30:32 by aparolar          #+#    #+#             */
/*   Updated: 2022/02/18 19:40:20 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	ft_putnbr_fd(timestamp() - philo->args->start, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->position + 1, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(status, 1);
	ft_putstr_fd("\n", 1);
}

void	show_status(t_philo *philo, char *status)
{
	if (!philo->args->dead && philo->args->eated)
	{
		pthread_mutex_lock(&philo->args->write);
		print_status(philo, status);
		pthread_mutex_unlock(&philo->args->write);
	}
}
