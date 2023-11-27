#include "main.h"

// leak check
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

void c(void)
{
	system("leaks a.out");
}

int main(int ac, char **av)
{
	t_info	*info;
	t_philo	**philos;
	

	atexit(c);
	if (ac != 5 && ac != 6)
	{
		printf("invalid ac\n");
		return (1);
	}
	info = init_shared_info(av);
	philos = init_philo(av, info);
	init_mutex(philos);
	thread_control(philos);
	destroy_mutex(philos);
	free_all(philos);
	return (0);
}
