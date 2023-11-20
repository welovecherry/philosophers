#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

// done: 1 philo (fork fork eat)
// TODO: 1 philo (die)

long get_time_in_ms()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
typedef struct	s_philo
{
	int		num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	begin_simul;
	int		philo_idx;
}	t_philo;

//void	*print_philo_state(void * philo)
//{
//	t_philo *d;
//	long	begin_last_meal;
//	long	cur_time;

//	d = (t_philo *)philo;
//	begin_last_meal = d->begin_simul;

//	cur_time = get_time_in_ms();
//	printf("%ld %d has taken a fork\n", d->begin_simul - cur_time, d->philo_idx);

//	cur_time = get_time_in_ms();
//	printf("%ld %d has taken a fork\n", d->begin_simul - cur_time, d->philo_idx);

//	cur_time = get_time_in_ms();
//	printf("%ld %d is eating\n", )

//	return (NULL);
//}

//int	is_starved(t_philo *philo, long begin_last_meal)
//{
//	long	cur_time;

//	cur_time = get_time_in_ms();
	
//	if (cur_time - begin_last_meal >= philo->time_to_die)
//	{
//		printf("dieeee\n");
//	}


//	return (0);
//}

int	main(void)
{
	t_philo *philo;
	long	cur_time;
	long	begin_last_meal;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		exit(1);

	philo->num_of_philo = 1;
	//philo->time_to_die = 5000;
	philo->time_to_die = 500;
	philo->time_to_eat = 1000;
	philo->time_to_sleep = 2000;
	philo->begin_simul = get_time_in_ms();
	philo->philo_idx = 1;
	begin_last_meal = philo->begin_simul;

	while (1)
	{
		cur_time = get_time_in_ms();
		printf("%ld %d has taken a fork\n", cur_time - philo->begin_simul , philo->philo_idx);

		cur_time = get_time_in_ms();
		printf("%ld %d has taken a fork\n", cur_time - philo->begin_simul, philo->philo_idx);

		//printf("check: %ld %ld\n", begin_last_meal, philo->begin_simul);
		begin_last_meal = get_time_in_ms();
		printf("%ld %d is eating\n", begin_last_meal - philo->begin_simul, philo->philo_idx);
		usleep(1000 * philo->time_to_eat);

		cur_time = get_time_in_ms();
		printf("%ld %d is sleeping\n", cur_time - philo->begin_simul, philo->philo_idx);
		usleep(1000 * philo->time_to_sleep);

		cur_time = get_time_in_ms();
		printf("%ld %d is thinking\n", cur_time - philo->begin_simul, philo->philo_idx);

	}

	free(philo);
	return (0);
}