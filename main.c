#include "main.h"

void	free_all(t_philo **philos, t_info *info)
{
	int	idx;
	int	temp_num_of_philo;

	temp_num_of_philo = philos[0]->i->num_of_philo;
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
	if (info != NULL)
	{
		if (info->forks_lock != NULL)
			free(info->forks_lock);
		if (info->forks_occupied != NULL)
			free(info->forks_occupied);
	}
	free(info);
}

void c(void) // deletttttteeeeee
{
	system("leaks a.out");
}

int main(int ac, char **av)
{
	t_info	*info;
	t_philo	**philos;
	
	atexit(c);

	if (ac != 5 && ac != 6)
	{
		return (1);
	}
	info = init_shared_info(av);
	philos = init_philo(info);
	init_mutex(philos);
	thread_control(philos);
	destroy_mutex(philos);
	free_all(philos, info);
	return (0);
}
