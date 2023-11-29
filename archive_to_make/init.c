#include "main.h"

int	check_num(char *str, int n)
{
	int	num_av;

	num_av = ft_atoi(str);
	if (num_av < n)
	{
		printf("invalid av!\n");
		exit(1);
	}
	return (num_av);
}

t_shared *init_shared_info(char **av)
{
	t_shared	*shared;

	shared = (t_shared *)malloc(sizeof(t_shared) * 1);
	if (!shared)
		exit(1);
	shared->num_of_philo = check_num(av[1], 1);
	shared->t_die = check_num(av[2], 0);
	shared->t_eat = check_num(av[3], 0);
	shared->t_sleep = check_num(av[4], 0);
	if (av[5] != NULL)
		shared->t_each_philo_must_eat = ft_atoi(av[5]);
	else
		shared->t_each_philo_must_eat = 0;
	shared->is_anyone_dead = 0;
	return(shared);
}
// TODO: free
void	init_forks(t_shared *shared)
{
	int	idx;

	shared->forks_occupied = (int *)malloc(sizeof(int) * shared->num_of_philo);
	if (!shared->forks_occupied)
		exit (1);
	idx = 0;
	while (idx < shared->num_of_philo)
	{
		shared->forks_occupied[idx] = 0;
		idx++;
	}
}


t_philo **init_philo(t_shared *shared)
{
	t_philo **philos;
	int	idx;

	init_forks(shared);
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
