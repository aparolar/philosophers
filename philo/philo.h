/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:36:52 by aparolar          #+#    #+#             */
/*   Updated: 2021/11/10 11:02:33 by aparolar         ###   ########.fr       */
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

typedef struct s_philo_args
{
	int				n_philos;
	__u_long		dead_time;
	__u_long		eat_time;
	__u_long		sleep_time;
	int				must_eat_count;
	__u_long		start;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	somebody_dead;
	int				dead;

}  t_philo_args;

typedef struct s_philo
{
	int                 position;
	int                 is_eating;
	__u_long            limit;
	__u_long            last_eat;
	__u_long			start;
	int                 lfork;
	int                 rfork;
	int                 eat_count;
	int					max_eat_count;
	struct s_philo_args *args;
	pthread_mutex_t     mutex;
	pthread_mutex_t     eat_m;
}   t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void    *philoso();
void	init_philo(t_philo *philo);
void	take_forks(t_philo *philo);
void	clean_forks(t_philo *philo);
int		doing_eat(t_philo *philo);
void	doing_sleep(t_philo *philo);
void	doing_think(t_philo *philo);
void	show_status(t_philo *philo, char *status);
int		filo_death(t_philo *philo);
__u_long	get_time();

#endif