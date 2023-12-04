/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_and_eat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:24:24 by jungmiho          #+#    #+#             */
/*   Updated: 2023/12/04 21:50:32 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	take_left_fork(t_philo *p)
{
	if (!is_alive(p))
		return (p->am_i_dead);
	if (p->hold_l_fork)
		return (p->am_i_dead);
	p->l_fork_lock = &(p->i->forks_lock[p->philo_idx]);
	p->is_l_fork_occupied = &(p->i->forks_occupied[p->philo_idx]);
	pthread_mutex_lock(p->l_fork_lock);
	if (*(p->is_l_fork_occupied) == 0)
	{
		*(p->is_l_fork_occupied) = 1;
		p->hold_l_fork = 1;
		print(p, FORK);
	}
	pthread_mutex_unlock(p->l_fork_lock);
	return (p->am_i_dead);
}

int	get_right_fork_index(t_philo *p)
{
	if (p->philo_idx == 0)
		return (p->i->num_of_philo - 1);
	else
		return (p->philo_idx - 1);
}

int	take_right_fork(t_philo *p)
{
	int	r_idx;

	if (!is_alive(p))
		return (p->am_i_dead);
	if (p->hold_r_fork)
		return (p->am_i_dead);
	if (p->i->num_of_philo == 1)
		return (p->am_i_dead);
	r_idx = get_right_fork_index(p);
	p->is_r_fork_occupied = &(p->i->forks_occupied[r_idx]);
	p->r_fork_lock = &(p->i->forks_lock[r_idx]);
	pthread_mutex_lock(p->r_fork_lock);
	if (*(p->is_r_fork_occupied) == 0)
	{
		*(p->is_r_fork_occupied) = 1;
		p->hold_r_fork = 1;
		print(p, FORK);
	}
	pthread_mutex_unlock(p->r_fork_lock);
	return (p->am_i_dead);
}

int	take_two_forks(t_philo *p)
{
	p->both_taken = 0;
	if (take_left_fork(p))
		return (p->am_i_dead);
	if (take_right_fork(p))
		return (p->am_i_dead);
	p->both_taken = (p->hold_l_fork && p->hold_r_fork);
	return (p->am_i_dead);
}

int	eating(t_philo *p)
{
	if (!is_alive(p))
		return (p->am_i_dead);
	print(p, EAT);
	p->t_begin_last_meal = get_time(p);
	while (is_alive(p))
	{
		if (get_time(p) - (p->t_begin_last_meal) >= (p->i->t_eat))
			break ;
		usleep(150);
	}
	if (p->i->num_of_times_each_p_must_eat)
	{
		p->times_i_ate++;
		if (p->times_i_ate == (p->i->num_of_times_each_p_must_eat))
			p->am_i_dead = 1;
	}
	pthread_mutex_lock(p->l_fork_lock);
	*(p->is_l_fork_occupied) = 0;
	pthread_mutex_unlock(p->l_fork_lock);
	pthread_mutex_lock(p->r_fork_lock);
	*(p->is_r_fork_occupied) = 0;
	pthread_mutex_unlock(p->r_fork_lock);
	p->hold_l_fork = 0;
	p->hold_r_fork = 0;
	return (p->am_i_dead);
}
