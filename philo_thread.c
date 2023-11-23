#include "main.h"

int	is_alive(t_philo *p)
{
	if (get_time(p) - (p->t_begin_last_meal) >= (p->i->t_die))
	{
		print(p, DIED);
		p->is_dead = 1;
		return (0);
	}
	return (1);
}

void	*philo(void *ptr)
{
	t_philo *p;

	p = (t_philo *)ptr;
	while (1)
	{
		if (take_two_forks(p))
			return (NULL);
		if (p->hold_l_fork && p->hold_r_fork)
		{
			if (eating(p))
				return (NULL);
		}
		else
			continue;
		if (sleeping(p))
			return (NULL);
		if (thinking(p))
			return (NULL);
	}

	return (NULL);
}

void	thread_control(t_philo **philos)
{
	int			idx;
	pthread_t	*philo_ths;

	philo_ths = (pthread_t *)malloc(sizeof(pthread_t) * philos[0]->i->num_of_philo);
	idx = 0;
	philos[0]->i->t_begin_simul_from_70s = get_t_begin_simul();
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_create(&(philo_ths[idx]), NULL, philo, philos[idx]);
		idx++;
	}

	idx = 0;
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_join(philo_ths[idx], NULL);
		idx++;
	}

	free(philo_ths);
}