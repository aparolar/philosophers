/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_aint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:53:45 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/24 00:06:31 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define AINT_MAX "2147483647"
#define AINT_MIN "-2147483648"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static int	all_digit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static	int	inside_limit(char *str, char *limit)
{
	int	i;

	if (ft_strlen(str) == ft_strlen(limit))
	{
		i = 0;
		while (str[i])
		{
			if (str[i] > limit[i])
				return (0);
			i++;
		}
	}
	return (1);
}

int	ft_is_valid_aint(char *str)
{
	char	*cstr;

	if (!str)
		return (0);
	cstr = AINT_MAX;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			cstr = &AINT_MIN[1];
		str++;
	}
	if (ft_strlen(str) <= ft_strlen(cstr)
		&& all_digit(str)
		&& inside_limit(str, cstr))
		return (1);
	return (0);
}
