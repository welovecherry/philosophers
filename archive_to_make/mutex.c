#include "main.h"

void	init_mutex(t_philo **philos)
{
	int	idx;

	philos[0]->sh->forks_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
	philos[0]->sh->num_of_philo);
	if (!(philos[0]->sh->forks_lock))
		exit (1);
	idx = 0;
	while (idx < philos[0]->sh->num_of_philo)
	{
		pthread_mutex_init(&(philos[0]->sh->forks_lock[idx]), NULL);
		idx++;
	}
	pthread_mutex_init(&(philos[0]->sh->anyone_dead_lock), NULL);
}

void destroy_mutex(t_philo **philos)
{
	int	idx;

	idx = 0;
	while (idx < philos[0]->sh->num_of_philo)
	{
		pthread_mutex_destroy(&(philos[0]->sh->forks_lock[idx]));
		idx++;
	}
	pthread_mutex_destroy(&(philos[0]->sh->anyone_dead_lock));
}