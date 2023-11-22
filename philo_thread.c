#include "main.h"

int is_alive(t_philo *p)
{
	if (get_time(p) - p->t_begin_last_meal >= p->i->t_die)
	{
		print(p, DIED);
		p->is_dead = 1;
		return (0);
	}
	return (1);
}

void *philo(void *ptr)
{
	t_philo *p;

	p = (t_philo *)ptr;

	while (1)
	{
		if (take_two_forks(p))
			return (NULL);
		if (eating(p))
			return (NULL);
		if (sleeping(p))
			return (NULL);
		if (thinking(p))
			return (NULL);
	}

	return (NULL);
}
