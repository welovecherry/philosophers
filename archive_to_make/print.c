#include "main.h"

void	print_routine(t_philo *p, int action)
{
	char *action_str;

	if (action == FORK)
		action_str = "has taken a fork";
	else if (action == EAT)
		action_str = "is eating";
	else if (action == SLEEP)
		action_str = "is sleeping";
	else if (action == THINK)
		action_str = "is thinking";
	else if (action == DIED)
		action_str = "died";
	pthread_mutex_lock(&(p->sh->anyone_dead_lock));
		if (!(p->am_i_dead) && (p->sh->is_anyone_dead))
		{
			pthread_mutex_unlock(&(p->sh->anyone_dead_lock));
			return ;
		}
		pthread_mutex_unlock(&(p->sh->anyone_dead_lock));
		printf("%ld %d %s\n", get_time(p), p->philo_idx + 1, action_str);
}