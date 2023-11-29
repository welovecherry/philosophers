#include "main.h"

long	get_time(t_philo *p)
{
	struct timeval	tv;
	long			cur_time;

	gettimeofday(&tv, NULL);
	cur_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (cur_time - (p->sh->t_begin_simul_from_70s));
}

long	get_t_begin_simul(void)
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}