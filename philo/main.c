/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:24:48 by jungmiho          #+#    #+#             */
/*   Updated: 2023/12/04 18:21:42 by jungmiho         ###   ########.fr       */
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
		free(info);
	}
}

int	main(int ac, char **av)
{
	t_info	*info;
	t_philo	**philos;

	info = init_shared_info(ac, av);
	if (!info)
		return (1);
	philos = init_philo(info);
	if (!philos)
	{
		free(info);
		return (1);
	}
	if (init_mutex(philos) == -1 || thread_control(philos) == -1)
	{
		destroy_mutex(philos);
		free_all(philos, info);
		return (1);
	}
	destroy_mutex(philos);
	free_all(philos, info);
	return (0);
}
