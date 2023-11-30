/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:25:04 by jungmiho          #+#    #+#             */
/*   Updated: 2023/11/29 19:56:35 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_num(char *str, int min_allowed_value)
{
	int	num_av;

	num_av = ft_atoi(str);
	if (num_av < min_allowed_value)
	{
		//printf("%c %d \n",*str, num_av);
		return (-1);
	}
	return (num_av);
}

int	set_shared_info_args(t_info *info, char **av)
{
	info->num_of_philo = check_num(av[1], 1);
	info->t_die = check_num(av[2], 0);
	info->t_eat = check_num(av[3], 0);
	info->t_sleep = check_num(av[4], 0);

	if (info->num_of_philo == -1 || info->t_die == -1 || \
		info->t_eat == -1 || info->t_sleep == -1)
		return (-1);
	if (av[5] != NULL) 
	{
		info->num_of_times_each_p_must_eat = check_num(av[5], 0);
		if (info->num_of_times_each_p_must_eat == -1)
			return (-1);
	}
	else
	{
		info->num_of_times_each_p_must_eat = 0;
	}
	return (0);
}

t_info	*init_shared_info(char **av)
{
	t_info	*info;
	
	info = malloc(sizeof(t_info));
	if (!info)
		return NULL;
	if (set_shared_info_args(info, av) == -1)
	{
		free(info);
		return NULL;
	}
	info->is_anyone_dead = 0;
	info->is_died_printed = 0;
	return (info);
}

int	init_forks(t_info *info)
{
	int	idx;

	info->forks_occupied = malloc(sizeof(int) * (info->num_of_philo));
	if (!(info->forks_occupied))
		return (-1);
	idx = 0;
	while (idx < info->num_of_philo)
	{
		info->forks_occupied[idx] = 0;
		idx++;
	}
	return (0);
}

t_philo	**init_philo(t_info *info)
{
	t_philo	**philos;
	int		idx;

	if (init_forks(info) == -1)
		return (NULL);
	philos = malloc(sizeof(t_philo *) * (info->num_of_philo));
	if (!philos)
		return (NULL);
	idx = 0;
	while (idx < info->num_of_philo)
	{
		philos[idx] = malloc(sizeof(t_philo));
		philos[idx]->i = info;
		philos[idx]->philo_idx = idx;
		philos[idx]->t_begin_last_meal = 0;
		philos[idx]->am_i_dead = 0;
		philos[idx]->hold_l_fork = 0;
		philos[idx]->hold_r_fork = 0;
		philos[idx]->times_i_ate = 0;
		idx++;
	}
	return (philos);
}
