#include "main.h"

int	take_left_fork(t_philo *p)
{
	if (!is_alive(p))
		return (p->is_dead);
	p->is_l_fork_occupied = &(p->i->forks_occupied[p->philo_idx]);
	p->l_fork_lock = &(p->i->forks_lock[p->philo_idx]);
	while (1)
	{
		if (p->hold_l_fork == 1)
			break ;
		pthread_mutex_lock(p->l_fork_lock);
		if (*(p->is_l_fork_occupied) == 0)
		{
			print(p, FORK);
			*(p->is_l_fork_occupied) = 1;
			p->hold_l_fork = 1;
			pthread_mutex_unlock(p->l_fork_lock);	
			break ;
		}
		pthread_mutex_unlock(p->l_fork_lock);
	}
	return (p->is_dead);
}

int	take_right_fork(t_philo *p)
{
	int	r_idx;

	if (!is_alive(p))
		return (p->is_dead);
	if (p->i->num_of_philo == 1)
		return (p->is_dead);
	if (p->philo_idx == 0)
		r_idx = p->i->num_of_philo - 1;
	else
		r_idx = p->philo_idx - 1;
	p->is_r_fork_occupied = &(p->i->forks_occupied[r_idx]);
	p->r_fork_lock = &(p->i->forks_lock[r_idx]);
	while (1)
	{
		if (p->hold_r_fork == 1)
			break ;
		pthread_mutex_lock(p->r_fork_lock);
		if (*(p->is_r_fork_occupied) == 0)
		{
			print(p, FORK);
			*(p->is_r_fork_occupied) = 1;
			p->hold_r_fork = 1;
			pthread_mutex_unlock(p->r_fork_lock);
			break ;
		}
		pthread_mutex_unlock(p->r_fork_lock);
	}
	return (p->is_dead);
}

int take_two_forks(t_philo *p)
{
	if (take_left_fork(p))
		return (p->is_dead);
	if (take_right_fork(p))
		return (p->is_dead);	
	return (p->is_dead);
}

int eating(t_philo *p)
{
	if (!is_alive(p))
		return (p->is_dead);

	print(p, EAT);
	p->t_begin_last_meal = get_time(p);
	while (is_alive(p))
	{
		if (get_time(p) - (p->t_begin_last_meal) >= (p->i->t_eat))
			break;
		usleep(100);
	}
	p->hold_l_fork = 0;
	p->hold_r_fork = 0;
	*(p->is_l_fork_occupied) = 0;
	*(p->is_r_fork_occupied) = 0;
	return (p->is_dead);
}

int sleeping(t_philo *p)
{
	long t_begin_sleep;

	if (!is_alive(p))
		return (p->is_dead);
	print(p, SLEEP);
	t_begin_sleep = get_time(p);
	while (is_alive(p))
	{
		if (get_time(p) - t_begin_sleep >= p->i->t_sleep)
			break;
		usleep(100);
	}
	return (p->is_dead);
}

int thinking(t_philo *p)
{
	if (!is_alive(p))
		return (p->is_dead);
	print(p, THINK);
	return (p->is_dead);
}