#include "main.h"

void	init_mutex(t_philo **philos)
{
	int	idx;

	philos[0]->i->forks_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (philos[0]->i->num_of_philo));
	idx = 0;
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_mutex_init(&(philos[0]->i->forks_lock[idx]), NULL);
		idx++;
	}
}

void	destroy_mutex(t_philo **philos)
{
	int	idx;

	idx = 0;
	while(idx < philos[0]->i->num_of_philo)
	{
		pthread_mutex_destroy(&(philos[0]->i->forks_lock[idx]));
		idx++;
	}
}