#include "main.h"

int	is_alive(t_philo *p)
{
	pthread_mutex_lock(&(p->i->anyone_dead_lock));
	if (p->am_i_dead || p->i->is_anyone_dead)
	{
		pthread_mutex_unlock(&(p->i->anyone_dead_lock));
		return (0);
	}
	pthread_mutex_unlock(&(p->i->anyone_dead_lock));
	if (get_time(p) - (p->t_begin_last_meal) >= (p->i->t_die))
	{
		p->am_i_dead = 1;
		pthread_mutex_lock(&(p->i->anyone_dead_lock));
		p->i->is_anyone_dead = 1;
		pthread_mutex_unlock(&(p->i->anyone_dead_lock));
		print(p, DIED);
		return (0);
	}
	return (1);
}

// 내가 먹는횟수 플래그 만족했을 때, 다른 모든 철학자가 옵셔널 룰만큼 먹었는지 확인
//int	all_ate_times_they_must_eat(t_philo *p)
//{
	// 와일로 돌면서 모든 철학자의 i_ate_all_flag가 1인지 확인하기.
	// 아니면 리턴 0,
	// 와일문 밖에서 리턴 1
//}
// 질문: 파라미터로 ** 들어와서 다른 필로를 다 확인해야하나?
int	met_optional_rules(t_philo *p)
{
	int	idx;

	idx = 0;
	while (idx < p->i->num_of_philo)
	{
		if ()

		idx++;
	}
}

void	*philo(void *ptr)
{
	t_philo *p;

	p = (t_philo *)ptr;
	while (1)
	{
		if (!(is_alive(p)))
			break ;
		if (take_two_forks(p))
			return (NULL);
		if (p->hold_l_fork && p->hold_r_fork)
		{
			if (eating(p))
				return (NULL);
		}
		else
			continue;
		if (sleeping(p))
			return (NULL);
		if (thinking(p))
			return (NULL);
	}
	return (NULL);
}

void	thread_control(t_philo **philos)
{
	int			idx;
	pthread_t	*philo_ths;

	philo_ths = (pthread_t *)malloc(sizeof(pthread_t) * philos[0]->i->num_of_philo);
	idx = 0;
	philos[0]->i->t_begin_simul_from_70s = get_t_begin_simul();
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_create(&(philo_ths[idx]), NULL, philo, philos[idx]);
		usleep(30);
		idx += 2;
	}
	idx = 1;
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_create(&(philo_ths[idx]), NULL, philo, philos[idx]);
		usleep(30);
		idx += 2;
	}


	idx = 0;
	while (idx < philos[0]->i->num_of_philo)
	{
		pthread_join(philo_ths[idx], NULL);
		idx++;
	}

	free(philo_ths);
}