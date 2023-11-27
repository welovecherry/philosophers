#include "main.h"

t_shared *init_shared_info(char **av)
{
	t_shared	*shared;

	shared = (t_shared *)malloc(sizeof(t_shared) * 1);
	if (!shared)
		exit(1);
	shared->num_of_philo = ft_atoi(av[1]);
	if (shared->num_of_philo == -1)
	{
		free(shared);
		exit (1);
	}
	shared->t_die = ft_atoi(av[2]);
	// die 도 음수 안되네!!!
	shared->t_eat = ft_atoi(av[3]);
	//
	shared->t_sleep = ft_atoi(av[4]);
	//
	if (av[5] != NULL)
		shared->t_each_philo_must_eat = ft_atoi(av[5]);
	else
		shared->t_each_philo_must_eat = 0;
	shared->is_anyone_dead = 0;
	return(shared);
}

t_philo **init_philo(t_shared *shared)
{
	t_philo **philos;
	int	idx;

	philos = (t_philo **)malloc(sizeof(t_philo *) * shared->num_of_philo);
	if (!philos)
		exit (1);
	idx = 0;
	while (idx < shared->num_of_philo)
	{
		philos[idx] = (t_philo *)malloc(sizeof(t_philo));
		philos[idx]->sh = shared;
		philos[idx]->philo_idx = idx;
		philos[idx]->t_begin_last_meal = 0;
		philos[idx]->am_i_dead = 0;
		philos[idx]->hold_left_f = 0;
		philos[idx]->hold_right_f = 0;
		philos[idx]->times_i_ate = 0;
		idx++;
	}
	return (philos);
}
