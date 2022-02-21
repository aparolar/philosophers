/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:36:21 by aparolar          #+#    #+#             */
/*   Updated: 2022/02/21 11:53:46 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_args(int argc, char **argv, t_philo_args *philo)
{
	if (argc >= 5 && philo)
	{
		philo->n_philos = ft_atoi(argv[1]);
		philo->dead_time = ft_atoi(argv[2]);
		philo->eat_time = ft_atoi(argv[3]);
		philo->sleep_time = ft_atoi(argv[4]);
		philo->must_eat_count = 0;
		if (argc == 6)
			philo->must_eat_count = ft_atoi(argv[5]);
		if (philo->n_philos > 0
			&& philo->n_philos <= 200
			&& philo->dead_time >= 60
			&& philo->eat_time >= 60
			&& philo->sleep_time >= 60
			&& philo->must_eat_count >= 0)
			return (1);
	}
	return (0);
}

static int	check_args(int argc, char **argv)
{
	while (--argc > 0)
	{
		if (!ft_is_valid_aint(argv[argc]))
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo_args	philo;

	if (check_args(argc, argv)
		&& get_args(argc, argv, &philo))
		start(&philo);
	else
	{
		printf("Error.\n");
		printf("Command arguments are : \n");
		printf("\tphilo n_philos dead_time eat_time sleep_time [must_eats]\n");
		printf("\tn_philos must be greather of 0 and minor or equal of 200\n");
		printf("\tdead_time,\n");
		printf("\teat_time and\n");
		printf("\tsleep_time : needs to be equal or greather of 60\n");
		printf("\t[must_eats] is optional no negative numbers\n");
	}
	return (0);
}
