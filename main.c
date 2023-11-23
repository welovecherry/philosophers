#include "main.h"

void	free_all(t_philo **ps)
{
	int	idx;
	int	temp_num_of_philo;

	if (!ps)
		return ;
	temp_num_of_philo = ps[0]->i->num_of_philo;
	free(ps[0]->i);
	idx = 0;
	while (idx < temp_num_of_philo)
	{
		free(ps[idx]);
		idx++;
	}
	free(ps);
}

t_philo **init_philo(void)
{
	t_info	*info;
	t_philo	**ps;
	int		idx;

	info = (t_info *)malloc(sizeof(t_info) * 1);
	if (!info)
		exit(1);
	// TODO: change macro to argv
	info->num_of_philo = NUM_OF_PHILO;
	info->t_die = TIME_DIE;
	info->t_eat = TIME_EAT;
	info->t_sleep = TIME_SLEEP;

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
		ps[idx]->i = info;
		idx++;
	}
	return (ps);
}

int main(void)
{
	t_philo			**philos;
	pthread_t		*philo_ths;
	int			idx;


	philos = init_philo();
	philo_ths = (pthread_t *)malloc(sizeof(pthread_t) * philos[0]->i->num_of_philo);
	if (!philo_ths)
		return (1);
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

	free_all(philos);
	return (0);
}
