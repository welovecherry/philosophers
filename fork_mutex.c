#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_OF_PHILO 5

pthread_mutex_t	forks[NUM_OF_PHILO];

void	*print_philo_state(void *num)
{
	int	id = 
}


int main(void)
{
	pthread_t	philo[NUM_OF_PHILO];
	int			philo_number[NUM_OF_PHILO];
	int			i;

	i = 0;
	while (i < NUM_OF_PHILO)
	{
		pthread_mutex_init(&forks[i], NULL);
		philo_number[i] = i;
		i++;
	}

	i = 0;
	while (i < NUM_OF_PHILO)
	{
		pthread_create(&philo[i], NULL, print_philo_state, NULL);
		i++;
	}


	return (0);
}