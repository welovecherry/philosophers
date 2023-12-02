/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:24:48 by jungmiho          #+#    #+#             */
/*   Updated: 2023/12/02 19:18:05 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_all(t_philo **philos, t_info *info)
{
	int	idx;
	int	temp_num_of_philo;

	temp_num_of_philo = philos[0]->i->num_of_philo;
	if (philos != NULL)
	{
		idx = 0;
		while (idx < temp_num_of_philo)
		{
			free(philos[idx]);
			idx++;
		}
		free(philos);
	}
	if (info != NULL)
	{
		if (info->forks_lock != NULL)
			free(info->forks_lock);
		if (info->forks_occupied != NULL)
			free(info->forks_occupied);
	}
	free(info);
}

int	main(int ac, char **av)
{
	t_info	*info;
	t_philo	**philos;

	if (ac != 5 && ac != 6)
		return (1);
	info = init_shared_info(av);
	if (!info)
		return (0);
	philos = init_philo(info);
	if (!philos)
	{
		free(info);
		return (0);
	}
	init_mutex(philos);
	if (thread_control(philos) == -1)
	{
		destroy_mutex(philos);
		free_all(philos, info);
		return (0);
	}
	destroy_mutex(philos);
	free_all(philos, info);
	return (0);
}
