#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

// done: 1 philo (fork fork eat)
// TODO: 1 philo (die using thread)

long get_time_in_ms()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

typedef struct	s_philo
{
	int				num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			begin_simul;
	int				philo_idx;
	long			begin_last_meal;
	int				*death_flag;
	pthread_mutex_t	*death_mutex;
}	t_philo;

void	*check_starvation(void *philo)
{
	t_philo	*d;
	long	cur_time;

	d = (t_philo *)philo;
	while (1)
	{
		cur_time = get_time_in_ms();
		//printf("check: %ld, %ld\n", cur_time - d->begin_last_meal, d->time_to_die);
		if (cur_time - d->begin_last_meal >= d->time_to_die)
		{
			//pthread_mutex_lock(d->death_mutex);
			*(d->death_flag) = 1;
			//pthread_mutex_unlock(d->death_mutex);
			printf("%ld %d died\n", get_time_in_ms() - d->begin_simul, d->philo_idx);
			return (NULL);
		}
		usleep (100);
	}
	return (NULL);
}

void	*philo_routine(void *philo)
{
	t_philo	*d;

	d = (t_philo *)philo;

	while (1)
	{
		//pthread_mutex_lock(d->death_mutex);
		if (*(d->death_flag))
		{
			printf("63\n");
			//pthread_mutex_unlock(d->death_mutex);
			return (NULL);
		}
		printf("%ld %d has taken a fork\n", get_time_in_ms() - d->begin_simul, d->philo_idx);
		printf("%ld %d has taken a fork\n", get_time_in_ms() - d->begin_simul, d->philo_idx);

		d->begin_last_meal = get_time_in_ms();
		printf("%ld %d is eating\n", d->begin_last_meal - d->begin_simul, d->philo_idx);
		usleep(1000 * d->time_to_eat);

		printf("%ld %d is sleeping\n", get_time_in_ms() - d->begin_simul, d->philo_idx);
		usleep(1000 * d->time_to_sleep);

		printf("%ld %d is thinking\n", get_time_in_ms() - d->begin_simul, d->philo_idx);
	}

	return (NULL);
}



int	main(void)
{
	t_philo 	*philo;
	long		cur_time;
	long		begin_last_meal;
	pthread_t	thread_1;
	pthread_t	thread_2;
	pthread_t	starvation_check_th;
	pthread_mutex_t	death_mutex;
	int			death_flag;

	death_flag = 0;
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		exit(1);

	pthread_mutex_init(&death_mutex, NULL);

	//philo->time_to_die = 5000;
	philo->num_of_philo = 1;
	philo->time_to_die = 3000;
	philo->time_to_eat = 1000;
	philo->time_to_sleep = 1000;
	philo->begin_simul = get_time_in_ms();
	philo->philo_idx = 1;
	philo->begin_last_meal = philo->begin_simul;
	philo->death_flag = &death_flag;
	philo->death_mutex = &death_mutex;

	pthread_create(&thread_1, NULL, philo_routine, philo);
	pthread_create(&starvation_check_th, NULL, check_starvation, philo);

	
	pthread_join(thread_1, NULL);
	pthread_join(starvation_check_th, NULL);

	pthread_mutex_destroy(&death_mutex);

	free(philo);
	return (0);
}