#include "main.h"

int print(t_philo *p, int action)
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

	pthread_mutex_lock(&(p->i->anyone_dead_lock));
	if (p->am_i_dead == 0 && p->i->is_anyone_dead == 1)
	{
		pthread_mutex_unlock(&(p->i->anyone_dead_lock));
		return (0);
	}
	pthread_mutex_unlock(&(p->i->anyone_dead_lock));
	// FIXME philo_idx
	printf("%ld %d %s\n", get_time(p), p->philo_idx, action_str);

	return (0);
}