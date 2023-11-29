/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:31:39 by jungmiho          #+#    #+#             */
/*   Updated: 2023/11/29 18:05:10 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_mutex(t_philo **philos)
{
	int	idx;

	philos[0]->i->forks_lock = malloc(sizeof(pthread_mutex_t) * \
	(philos[0]->i->num_of_philo));
	idx = 0;
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_mutex_init(&(philos[0]->i->forks_lock[idx]), NULL);
		idx++;
	}
	pthread_mutex_init(&(philos[0]->i->anyone_dead_lock), NULL);
	pthread_mutex_init(&(philos[0]->i->print_lock), NULL);
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
