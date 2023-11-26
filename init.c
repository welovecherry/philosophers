#include "main.h"

// TODO: free
void	init_forks(t_info *info)
{
	int	idx;

	info->forks_occupied = (int *)malloc(sizeof(int) * (info->num_of_philo));
	if (!(info->forks_occupied))
		exit (1);
	
	idx = 0;
	while (idx < info->num_of_philo)
	{
		info->forks_occupied[idx] = 0;
		idx++;
	}
}

void	init_times_philos_ate(t_info *info)
{
	int	idx;
	info->times_philos_ate = (int *)malloc(sizeof(int) * (info->num_of_philo));
	if (!(info->times_philos_ate))
		exit (1);
	
	idx = 0;
	while (idx < info->num_of_philo)
	{
		info->times_philos_ate[idx] = 0;
		idx++;
	}
}

t_info *init_shared_info(char **av)
{
	t_info *info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		exit(1);
	info->num_of_philo = atoi(av[1]);
	info->t_die = atoi(av[2]);
	info->t_eat = atoi(av[3]);
	info->t_sleep = atoi(av[4]);
	if (av[5] != NULL)
	{
		info->num_of_times_each_p_must_eat = atoi(av[5]);
		init_times_philos_ate(info); // 이때만 초기화해야할듯 
		// TODO: free
	}
	else
		info->num_of_times_each_p_must_eat = 0;
	info->is_anyone_dead = 0;
	return info;
}


t_philo **init_philo(char **av, t_info *info)
{
	t_philo	**philos;
	int		idx;

	init_forks(info);

	philos = (t_philo **)malloc(sizeof(t_philo *) * (info->num_of_philo));
	if (!philos)
		exit(1);
	idx = 0;
	while (idx < info->num_of_philo)
	{
		philos[idx] = (t_philo *)malloc(sizeof(t_philo));
		philos[idx]->i = info;
		philos[idx]->philo_idx = idx;
		philos[idx]->t_begin_last_meal = 0;
		philos[idx]->am_i_dead = 0;
		philos[idx]->hold_l_fork = 0;
		philos[idx]->hold_r_fork = 0;
		philos[idx]->times_i_ate = 0;
		idx++;
	}
	return (philos);
}	