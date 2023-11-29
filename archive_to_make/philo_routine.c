#include "main.h"

int	take_left_fork(t_philo *p)
{
	if (!is_alive(p))
		return (p->am_i_dead);
	p->left_f_lock = &(p->sh->forks_lock[p->philo_idx]);
	while (1)
	{
		if (p->hold_left_f == 1)
			break ;
		pthread_mutex_lock(p->left_f_lock);
		p->is_left_f_occupied = &(p->sh->forks_occupied[p->philo_idx]);
		if (*(p->is_left_f_occupied) == 0)
		{
			*(p->is_left_f_occupied) = 1;
			p->hold_left_f = 1;
			print_routine(p, FORK);
			pthread_mutex_unlock(p->left_f_lock);
			break ;
		}
		pthread_mutex_unlock(p->left_f_lock);
	}
	return (p->am_i_dead);
}

// 함수 둘로 쪼개기
int	take_right_fork(t_philo *p)
{
	int	r_idx;

	if (!(is_alive(p)))
		return (p->am_i_dead);
	if (p->sh->num_of_philo == 1)
		return (p->am_i_dead);
	if (p->philo_idx == 0)
		r_idx = p->sh->num_of_philo - 1;
	else
		r_idx = p->philo_idx - 1;
	p->is_right_f_occupied = &(p->sh->forks_occupied[r_idx]);
	p->right_f_lock = &(p->sh->forks_lock[r_idx]);
	while (1)
	{
		if (p->hold_right_f)
			break ;
		pthread_mutex_lock(p->right_f_lock);
		if (*(p->is_right_f_occupied) == 0)
		{
			*(p->is_right_f_occupied) = 1;
			p->hold_right_f = 1;
			print_routine(p, FORK);
			pthread_mutex_unlock(p->right_f_lock);
			break ;
		}
		pthread_mutex_unlock(p->right_f_lock);
	}
	return (p->am_i_dead);
}

int	take_two_forks(t_philo *p)
{
	if (take_left_fork(p))
		return (p->am_i_dead);
	if (take_right_fork(p))
		return (p->am_i_dead);
	return (p->am_i_dead);
}

// TODO: split the function
int	eating(t_philo *p)
{
	if (!(is_alive(p)))
		return (p->am_i_dead);
	print_routine(p, EAT);
	p->t_begin_last_meal = get_time(p);
	while (is_alive(p))
	{
		if (get_time(p) - (p->t_begin_last_meal) >= (p->sh->t_die))
			break ;
		usleep(100);
	}
	if (p->sh->t_each_philo_must_eat != 0) // NULL??
	{
		p->times_i_ate++;
		if (p->times_i_ate == (p->sh->t_each_philo_must_eat))
			p->am_i_dead = 1;
	}
	pthread_mutex_lock(p->left_f_lock);
	*(p->is_left_f_occupied) = 0;
	pthread_mutex_unlock(p->left_f_lock);
	pthread_mutex_lock(p->right_f_lock);
	*(p->is_right_f_occupied) = 0;
	pthread_mutex_unlock(p->right_f_lock);
	p->hold_left_f = 0;
	p->hold_right_f = 0;
	return (p->am_i_dead);
}

int	sleeping(t_philo *p)
{
	long	t_begin_sleep;

	if(!is_alive(p))
		return (p->am_i_dead);
	print_routine(p, SLEEP);
	t_begin_sleep = get_time(p);
	while (is_alive(p))
	{
		if (get_time(p) - t_begin_sleep >= p->sh->t_sleep)
			break ;
		usleep(100);
	}
	return (p->am_i_dead);
}

int	thinking(t_philo *p)
{
	if(!is_alive(p))
		return (p->am_i_dead);
	print_routine(p, THINK);
	return (p->am_i_dead);
}

void	*philo_control(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (1)
	{
		if (!(is_alive(p)))
			return (NULL);
		if (take_two_forks(p))
			return (NULL);
		if (p->hold_left_f && p->hold_right_f)
		{
			if (eating(p))
				return (NULL);
		}
		else
			continue ;
		if (sleeping(p))
			return (NULL);
		if (thinking(p))
			return (NULL);
	}
	return (NULL);
}
