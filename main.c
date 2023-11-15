#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>


pthread_mutex_t	fork1;

int	counter = 0;

// TODO: 철학자 수는 1 이상이기 때문에 -, 음수 될  수 없다.
int ft_atoi(const char *str)
{
	int res;
	int sign;
	res = 0;
	sign = 1;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		res = (res * 10) + *str - '0';
		str++;
	}
	return (res * sign);
}

long get_time_in_ms()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// TODO: 	int		num_of_times_each_philo_must_eat;
typedef struct	s_philo
{
	int		num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		philo_idx;
	long	beginning_of_simulation;
}	t_philo;

void	*print_philo_state(void *philo_info)
{
	long	beginning_of_last_meal;
	long	beginning_of_sleeping;
	long	current_time;
	int		is_dead;
	t_philo	*d;

	d = (t_philo *)philo_info;
	is_dead = 0;
	d->beginning_of_simulation = get_time_in_ms();
	while (1)
	{
		pthread_mutex_lock(&fork1);
		current_time = get_time_in_ms();
		printf("%ld %d has taken a fork\n", current_time - d->beginning_of_simulation, d->philo_idx);
		current_time = get_time_in_ms();
		printf("%ld %d has taken a fork\n", current_time - d->beginning_of_simulation, d->philo_idx);

		beginning_of_last_meal = get_time_in_ms();
		printf("%ld %d is eating\n", beginning_of_last_meal - d->beginning_of_simulation, d->philo_idx);
		usleep(1000 * (d->time_to_eat));

		pthread_mutex_unlock(&fork1);

		beginning_of_sleeping = get_time_in_ms();
		printf("%ld %d is sleeping\n", beginning_of_sleeping - d->beginning_of_simulation, d->philo_idx);
		while (1)
		{
			current_time = get_time_in_ms();
			if (current_time - beginning_of_last_meal >= d->time_to_die)
			{
				current_time = get_time_in_ms();
				printf("%ld %d died\n", current_time - d->beginning_of_simulation, d->philo_idx);
				is_dead = 1;
				break;
			}
			current_time = get_time_in_ms();
			if (current_time - beginning_of_sleeping >= (d->time_to_sleep))
			{
				current_time = get_time_in_ms();
				printf("%ld %d is thinking\n", current_time - d->beginning_of_simulation, d->philo_idx);
				break ;
			}
			usleep(10);
		}
		if (is_dead)
			break ;
	}
	return (NULL);
}

int main(int ac, char **av)
{
	pthread_t	thread1;
	pthread_t	thread2;
	t_philo		philo_info[2];

	philo_info[0].num_of_philo = ft_atoi(av[1]);
	philo_info[0].time_to_die = (long)ft_atoi(av[2]);
	philo_info[0].time_to_eat = (long)ft_atoi(av[3]);
	philo_info[0].time_to_sleep = (long)ft_atoi(av[4]);

	philo_info[1].num_of_philo = ft_atoi(av[1]);
	philo_info[1].time_to_die = (long)ft_atoi(av[2]);
	philo_info[1].time_to_eat = (long)ft_atoi(av[3]);
	philo_info[1].time_to_sleep = (long)ft_atoi(av[4]);

	pthread_mutex_init(&fork1, NULL);

	philo_info[0].philo_idx = 1;
	if (pthread_create(&thread1, NULL, print_philo_state, &philo_info[0]) == 0)
		printf("thread 1 created\n");
	else
		printf("failed to create the thread\n");

	philo_info[1].philo_idx = 2;
	if (pthread_create(&thread2, NULL, print_philo_state, &philo_info[1]) == 0)
		printf("thread 2 created\n");
	else
		printf("failed to create the thread\n");


	if (pthread_join(thread1, NULL) == 0)
		printf("thread1 finished execution\n");
	else
		printf("failed to join the thread1 \n");

	if (pthread_join(thread2, NULL) == 0)
		printf("thread 2 finished execution\n");
	else
		printf("failed to join the thread 2 \n");
		
	pthread_mutex_destroy(&fork1);

	return (0);
}
