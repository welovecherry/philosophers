#include "main.h"

int print(t_philo *p, int action)
{
	char *action_str;

	// TODO: check death
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

	printf("%ld %d %s\n", get_time(p), p->philo_idx + 1, action_str);

	return (0);
}