#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_OF_PHILO 2

pthread_mutex_t	forks[NUM_OF_PHILO];

void	*philo(void *num)
{

}

int	main(void)
{
	pthread_t	philo[NUM_OF_PHILO];
	int			philo_num[NUM_OF_PHILO];
	int			i;

	i = 0;
	while (i < NUM_OF_PHILO)
	{
		pthread_mutex_init(&forks[i], NULL);
		
		i++;
	}
	

}