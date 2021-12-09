/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:05:51 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/09 12:05:22 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	long	no;
	char	str[12];

	if (fd)
	{
		len = 0;
		while (len < 12)
			str[len++] = 0;
		no = n;
		len = ft_intlen(n);
		str[len + 1] = 0;
		if (n < 0)
			len++;
		while (len > 0)
		{	
			if (n < 0)
				str[len - 1] = -(n % 10) + 48;
			else
				str[len - 1] = (n % 10) + 48;
			n /= 10;
			len--;
		}
		if (no < 0)
			str[0] = '-';
		ft_putstr_fd(str, fd);
	}
}
