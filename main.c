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

int main(void)
{
	t_philo	**philos;
	
	philos = init_philo();

	init_mutex(philos);
	thread_control(philos);
	destroy_mutex(philos);
	
	free_all(philos);
	return (0);
}
