#include "main.h"

int	check_num(char *str, int n)
{
	int	num_av;

	num_av = ft_atoi(str);
	if (num_av < n)
	{
		exit(1);
	}
	return (num_av);
}

t_info	*init_shared_info(char **av)
{
	t_info *info;

	info = malloc(sizeof(t_info));
	if (!info)
		exit(1);
	info->num_of_philo = check_num(av[1], 1);
	info->t_die = check_num(av[2], 0);
	info->t_eat = check_num(av[3], 0);
	info->t_sleep = check_num(av[4], 0);
	if (av[5] != NULL)
	{
		info->num_of_times_each_p_must_eat = check_num(av[5], 0);
		if (info->num_of_times_each_p_must_eat == 0)
			exit (1);
	}
	else
		info->num_of_times_each_p_must_eat = 0;
	info->is_anyone_dead = 0;
	return info;
}

void	init_forks(t_info *info)
{
	int	idx;

	info->forks_occupied = malloc(sizeof(int) * (info->num_of_philo));
	if (!(info->forks_occupied))
		exit (1);
	idx = 0;
	while (idx < info->num_of_philo)
	{
		info->forks_occupied[idx] = 0;
		idx++;
	}
}

t_philo	**init_philo(t_info *info)
{
	t_philo	**philos;
	int		idx;

	init_forks(info);
	philos = malloc(sizeof(t_philo *) * (info->num_of_philo));
	if (!philos)
		exit(1);
	idx = 0;
	while (idx < info->num_of_philo)
	{
		philos[idx] = malloc(sizeof(t_philo));
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
