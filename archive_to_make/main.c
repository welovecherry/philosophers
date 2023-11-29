#include "main.h"

void	free_all(t_philo **philos, t_shared *shared)
{
	int	idx;
	int	temp_num_of_philo;

	temp_num_of_philo = philos[0]->sh->num_of_philo;
	if (philos != NULL)
	{
		idx = 0;
		while (idx < temp_num_of_philo)
		{
			free(philos[idx]);
			idx++;
		}
		free(philos);
	}
	if (shared != NULL)
	{
		if (shared->forks_lock != NULL)
			free(shared->forks_lock);
		if (shared->forks_occupied != NULL)
			free(shared->forks_occupied);
		free(shared);
	}
}

void	c(void)
{
	system("leaks a.out");
}

int	main(int ac, char **av)
{
	t_shared	*shared;
	t_philo		**philos;

	atexit(c);

	if (ac != 5 && ac != 6)
	{
		printf("Invalid ac\n");
		return (1);
	}
	shared = init_shared_info(av);
	philos = init_philo(shared);
	init_mutex(philos);

	thread_control(philos);

	destroy_mutex(philos);
	free_all(philos, shared);
	return (0);
}