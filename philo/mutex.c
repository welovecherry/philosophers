/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:31:39 by jungmiho          #+#    #+#             */
/*   Updated: 2023/12/04 15:41:21 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init_mutex(t_philo **philos)
{
	int	idx;

	philos[0]->i->forks_lock = malloc(sizeof(pthread_mutex_t) * \
	(philos[0]->i->num_of_philo));
	if (!philos[0]->i->forks_lock)
	{
		free_all(philos, philos[0]->i);
		return (-1);
	}
	idx = 0;
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_mutex_init(&(philos[0]->i->forks_lock[idx]), NULL);
		idx++;
	}
	pthread_mutex_init(&(philos[0]->i->anyone_dead_lock), NULL);
	pthread_mutex_init(&(philos[0]->i->print_lock), NULL);
	return (0);
}

void	destroy_mutex(t_philo **philos)
{
	int	idx;

	idx = 0;
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_mutex_destroy(&(philos[0]->i->forks_lock[idx]));
		idx++;
	}
	pthread_mutex_destroy(&(philos[0]->i->anyone_dead_lock));
	pthread_mutex_destroy(&(philos[0]->i->print_lock));
}
