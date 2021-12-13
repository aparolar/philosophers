/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:36:52 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/13 22:20:05 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <time.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef unsigned long	t_ulong;

typedef struct s_philo_args
{
	int				n_philos;
	t_ulong			dead_time;
	t_ulong			eat_time;
	t_ulong			sleep_time;
	int				must_eat_count;
	int				eated;
	t_ulong			start;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	int				dead;

}	t_philo_args;

typedef struct s_philo
{
	int					position;
	t_ulong				last_eat;
	int					lfork;
	int					rfork;
	int					eat_count;
	int					max_eat_count;
	int					died;
	struct s_philo_args	*args;
	pthread_t			thread_id;
}	t_philo;

/*
** General functions
*/

int		init_philo(t_philo *philo);
void	*philoso(void *args);
void	doing_eat(t_philo *philo);
void	do_sleep_and_think(t_philo *philo);
int		is_p_int(int n);

/*
** Print functions
*/

void	print_status(t_philo *philo, char *status);
void	show_status(t_philo *philo, char *status);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*
**  Time Functions
*/

t_ulong	timestamp(void);
t_ulong	time_diff(t_ulong past, t_ulong present);
int		cond_sleep(t_ulong time, t_philo_args *args);

/*
** Other functions
*/

int		ft_intlen(int n);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

#endif