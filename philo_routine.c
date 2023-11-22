#include "main.h"

int take_two_forks(t_philo *p)
{
	if (!is_alive(p))
		return (p->is_dead);
	print(p, FORK);
	if (!is_alive(p))
		return (p->is_dead);
	print(p, FORK);
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
		if (get_time(p) - p->t_begin_last_meal >= p->i->t_eat)
			break;
		usleep(100);
	}
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