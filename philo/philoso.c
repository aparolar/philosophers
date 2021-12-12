/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoso.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:26:08 by aparolar          #+#    #+#             */
/*   Updated: 2021/12/12 02:12:38 by aparolar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_philo(t_philo *philo)
{
	int			ret;

	philo->died = 0; // mirar si es necesaria esta variable de la estructura , evita codigo
	philo->lfork = philo->position;
	philo->rfork = (philo->lfork + 1) % philo->args->n_philos; // estudiar bien porque da los valores correctos
	philo->eat_count = 0;
	philo->max_eat_count = philo->args->must_eat_count; //Es necesario?
	if (philo->lfork != philo->rfork)
	{
		philo->last_eat = timestamp(); //porque quitandolo no funciona bien ¿?¿?¿
		//ret : hacer una verificacion mas exahustiva en caso de fallar un pthread_create
		ret = pthread_create(&philo->thread_id, 0, philoso, (void *)philo);
		if (ret)
			printf("No se ha podido crear el hilo %d\n", philo->position);
	}
	else
	{
		// se pueden ahorrar tres lineas si se da por muerto en caso de que haya soo un filo
		//podria ser dando por hecho que uno ha muerto de inicio y en caso de haber mas de uno ponerlo a cero
		show_status(philo, DIED);
		philo->args->dead++;
	}
}

 //probar a castear los parametros de entrada eje... t_philo *p
 //nos ahorramos lineas y variables
//probar a no requerir de la variable local deadç
//cambiar nombre a la rutina por ejemplo "a_crazy_philosopher"
void    *philoso(void *args)
{
	t_philo	*p;
	int	dead;

	p = (t_philo *)args;
	if (p->position % 2)
		usleep(500);
	p->last_eat = timestamp();
	dead = 0;
	while (!dead && p->args->eated < p->args->n_philos)
	{
		doing_eat(p);
		if (p->max_eat_count > 0 && p->eat_count == p->max_eat_count)
		{		
			pthread_mutex_lock(&p->args->write);
			// en cuanto a problemas con fsanitiz=pthead cuando da problemas
			// como race intentar probar de poner una pausa antes de acceder a la memoria
			p->args->eated++;
			pthread_mutex_unlock(&p->args->write);
		}
		if (p->args->dead)
			dead = 1;
	}
	return (0);
}
