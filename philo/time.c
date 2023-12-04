/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:32:02 by jungmiho          #+#    #+#             */
/*   Updated: 2023/12/02 11:32:33 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	get_time(t_philo *p)
{
	struct timeval	tv;
	long			cur_time;

	gettimeofday(&tv, NULL);
	cur_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (cur_time - (p->i->t_begin_simul_from_70s));
}

long	get_t_begin_simul(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
