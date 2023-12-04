/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:31:49 by jungmiho          #+#    #+#             */
/*   Updated: 2023/12/04 15:37:56 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_alive(t_philo *p)
{
	pthread_mutex_lock(&(p->i->anyone_dead_lock));
	if (p->am_i_dead || p->i->is_anyone_dead)
	{
		pthread_mutex_unlock(&(p->i->anyone_dead_lock));
		return (0);
	}
	pthread_mutex_unlock(&(p->i->anyone_dead_lock));
	if (get_time(p) - (p->t_begin_last_meal) >= (p->i->t_die))
	{
		pthread_mutex_lock(&(p->i->anyone_dead_lock));
		p->i->is_anyone_dead = 1;
		pthread_mutex_unlock(&(p->i->anyone_dead_lock));
		p->am_i_dead = 1;
		print(p, DIED);
		return (0);
	}
	return (1);
}

void	*philo(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (1)
	{
		if (!(is_alive(p)))
			break ;
		if (take_two_forks(p))
			return (NULL);
		if (p->i->num_of_philo == 1)
			continue ;
		if (p->both_taken)
		{
			if (eating(p))
				return (NULL);
			p->both_taken = 0;
			if (sleeping(p))
				return (NULL);
			if (thinking(p))
				return (NULL);
		}
		else
			continue ;
	}
	return (NULL);
}

void	join_threads(t_philo **philos, pthread_t *philo_ths)
{
	int	idx;

	idx = 0;
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_join(philo_ths[idx], NULL);
		idx++;
	}
}

int	thread_control(t_philo **philos)
{
	int			idx;
	pthread_t	*philo_ths;

	philo_ths = malloc(sizeof(pthread_t) * philos[0]->i->num_of_philo);
	if (!philo_ths)
		return (-1);
	idx = 0;
	philos[0]->i->t_begin_simul_from_70s = get_t_begin_simul();
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_create(&(philo_ths[idx]), NULL, philo, philos[idx]);
		usleep(1);
		idx += 2;
	}
	usleep(20);
	idx = 1;
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_create(&(philo_ths[idx]), NULL, philo, philos[idx]);
		usleep(1);
		idx += 2;
	}
	join_threads(philos, philo_ths);
	free(philo_ths);
	return (0);
}
