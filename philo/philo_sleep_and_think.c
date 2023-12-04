/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep_and_think.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:31:45 by jungmiho          #+#    #+#             */
/*   Updated: 2023/12/04 21:51:38 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	sleeping(t_philo *p)
{
	long	t_begin_sleep;

	if (!is_alive(p))
		return (p->am_i_dead);
	print(p, SLEEP);
	t_begin_sleep = get_time(p);
	while (is_alive(p))
	{
		if (get_time(p) - t_begin_sleep >= p->i->t_sleep)
			break ;
		usleep(1000);
	}
	return (p->am_i_dead);
}

int	thinking(t_philo *p)
{
	if (!is_alive(p))
		return (p->am_i_dead);
	print(p, THINK);
	return (p->am_i_dead);
}
