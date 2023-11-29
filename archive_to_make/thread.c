#include "main.h"

int	is_alive(t_philo *p)
{
	pthread_mutex_lock(&(p->sh->anyone_dead_lock));
	if (p->am_i_dead || p->sh->is_anyone_dead)
	{
		pthread_mutex_unlock(&(p->sh->anyone_dead_lock));
		return (0);
	}
	pthread_mutex_unlock(&(p->sh->anyone_dead_lock));
	if (get_time(p) - (p->t_begin_last_meal) >= (p->sh->t_die))
	{
		pthread_mutex_lock(&(p->sh->anyone_dead_lock));
		p->sh->is_anyone_dead = 1;
		pthread_mutex_unlock(&(p->sh->anyone_dead_lock));
		p->am_i_dead = 1;
		print_routine(p, DIED);
		return (0);
	}
	return (1);
}


// TODO: 함수 나누던가 아니면 아이디엑스 쁠쁠을 []안에 넣던가
void	thread_control(t_philo **philos)
{
	int			idx;
	pthread_t	*philo_ths;

	philo_ths = (pthread_t *)malloc(sizeof(pthread_t) * \
	philos[0]->sh->num_of_philo);
	idx = 0;
	philos[0]->sh->t_begin_simul_from_70s = get_t_begin_simul();
	while (idx < philos[0]->sh->num_of_philo)
	{
		pthread_create(&(philo_ths[idx]), NULL, philo_control, philos[idx]);
		usleep(50);
		idx += 2;
	}
	idx = 1;
	while (idx < philos[0]->sh->num_of_philo)
	{
		pthread_create(&(philo_ths[idx]), NULL, philo_control, philos[idx]);
		usleep(50);
		idx += 2;
	}
	idx = 0;
	while (idx < philos[0]->sh->num_of_philo)
	{
		pthread_join(philo_ths[idx], NULL);
		idx++; // move to line 51
	}
}