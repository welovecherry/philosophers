#include "main.h"

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

t_philo **init_philo(void)
{
	t_info	*info;
	t_philo	**ps;
	int		idx;

	info = (t_info *)malloc(sizeof(t_info) * 1);
	if (!info)
		exit(1);
	info->num_of_philo = NUM_OF_PHILO;
	info->t_die = TIME_DIE;
	info->t_eat = TIME_EAT;
	info->t_sleep = TIME_SLEEP;
	init_forks(info);

	ps = (t_philo **)malloc(sizeof(t_philo *) * (info->num_of_philo));
	if (!ps)
		exit(1);
	idx = 0;
	while (idx < info->num_of_philo)
	{
		ps[idx] = (t_philo *)malloc(sizeof(t_philo) * 1);
		ps[idx]->philo_idx = idx;
		ps[idx]->t_begin_last_meal = 0;
		ps[idx]->is_dead = 0;
		ps[idx]->hold_l_fork = 0;
		ps[idx]->hold_r_fork = 0;
		ps[idx]->i = info;
		idx++;
	}
	return (ps);
}	