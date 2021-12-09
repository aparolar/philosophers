/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:36:52 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/09 11:55:43 by aparolar         ###   ########.fr       */
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

typedef unsigned long ulong;

typedef struct s_philo_args
{
	int				n_philos;
	ulong			dead_time;
	ulong			eat_time;
	ulong			sleep_time;
	int				must_eat_count;
	int				eated;
	ulong			start;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t meal_check;
	int				dead;

}  t_philo_args;

typedef struct s_philo
{
	int                 position;
	ulong       	    limit;
	ulong   	        last_eat;
	ulong				start;
	int                 lfork;
	int                 rfork;
	int                 eat_count;
	int					max_eat_count;
	int					died;
	struct s_philo_args *args;
	pthread_t			thread_id;
}   t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void    *philoso(void *args);
void	init_philo(t_philo *philo);
int		take_forks(t_philo *philo);
void	clean_forks(t_philo *philo);
int		doing_eat(t_philo *philo);
void	show_status(t_philo *philo, char *status);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_intlen(int n);

/*
**  Time Functions
*/

ulong	timestamp();
ulong	time_diff(ulong past, ulong present);
void	cond_sleep(ulong time, t_philo_args *args);

#endif