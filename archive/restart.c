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
	int				*death_flag; // mutex
	pthread_mutex_t	*death_mutex;
	int				have_fork_l;
	int				have_fork_r;
}	t_philo;

void	*check_starvation(void *philo)
{
	t_philo	*d;
	long	cur_time;

	d = (t_philo *)philo;
	while (1)
	{
		cur_time = get_time_in_ms();
		if (cur_time - d->begin_last_meal >= d->time_to_die)
		{
			*(d->death_flag) = 1;
			printf("%ld %d died\n", get_time_in_ms() - d->begin_simul, d->philo_idx);
			return (NULL);
		}
		usleep (100);
	}
	return (NULL);
}

int	sleeping_routine(t_philo *d)
{
	// 자다가 죽는 경우 생각하기
	long	begin_sleeping;

	while (1)
	{
		printf("%ld %d is sleeping\n", get_time_in_ms() - d->begin_simul, d->philo_idx);
		usleep(1000 * d->time_to_sleep);
		// wake up
		if (get_time_in_ms() - d-> >= d->time_to_die)


	}
	
	return (0);
}

void	*philo_routine(void *philo)
{
	t_philo	*d;

	d = (t_philo *)philo;
	while (1)
	{
		if (d->have_fork_l == 0)
		{
			printf("%ld %d has taken a fork\n", get_time_in_ms() - d->begin_simul, d->philo_idx);
			d->have_fork_l = 1;
		}
		else
			continue;
		
		if (d->have_fork_l && d->have_fork_r == 0)
		{
			printf("%ld %d has taken a fork\n", get_time_in_ms() - d->begin_simul, d->philo_idx);
			d->have_fork_r = 1;
		}
		else
			continue;

		if (d->have_fork_l && d->have_fork_r)
		{
			d->begin_last_meal = get_time_in_ms();
			printf("%ld %d is eating\n", d->begin_last_meal - d->begin_simul, d->philo_idx);
			usleep(1000 * d->time_to_eat);
			d->have_fork_l = 0;
			d->have_fork_r = 0;
		}
		else
			continue;
	
		sleeping_routine(d);

		printf("%ld %d is thinking\n", get_time_in_ms() - d->begin_simul, d->philo_idx);
	}
	return (NULL);
}



int	main(void)
{
	t_philo 	*philo;
	pthread_t	thread_1;
	pthread_t	starvation_check_th;
	int			death_flag;

	death_flag = 0;
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		exit(1);

	philo->num_of_philo = 1;
	philo->time_to_die = 3000;
	philo->time_to_eat = 1000;
	philo->time_to_sleep = 1000;
	philo->begin_simul = get_time_in_ms();
	philo->begin_last_meal = philo->begin_simul;
	philo->death_flag = &death_flag;
	philo->have_fork_l = 0;
	philo->have_fork_r = 0;

	philo->philo_idx = 1;
	pthread_create(&thread_1, NULL, philo_routine, philo);
	pthread_create(&starvation_check_th, NULL, check_starvation, philo);
	pthread_join(thread_1, NULL);
	pthread_join(starvation_check_th, NULL);
	free(philo);
	return (0);
}
