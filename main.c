#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

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

typedef struct	s_philo
{
	int		num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		num_of_times_each_philo_must_eat;
}	t_philo;

void	*print_philo_state(void *philo_info)
{
	long	beginning_of_simulation;
	long	beginning_of_last_meal;
	long	beginning_of_sleeping;
	long	current_time;
	int		is_dead;

	is_dead = 0;
	beginning_of_simulation = get_time_in_ms();
	while (1)
	{
		current_time = get_time_in_ms();
		printf("%ld 1 has taken a fork\n", current_time - beginning_of_simulation);
		current_time = get_time_in_ms();
		printf("%ld 1 has taken a fork\n", current_time - beginning_of_simulation);

		beginning_of_last_meal = get_time_in_ms();
		printf("%ld 1 is eating\n", beginning_of_last_meal - beginning_of_simulation);
		usleep(1000 * ((t_philo *)philo_info)->time_to_eat);

		beginning_of_sleeping = get_time_in_ms();
		printf("%ld 1 is sleeping\n", beginning_of_sleeping - beginning_of_simulation);

		while (1) 	// 자다가 죽을 경우, 자다가 깨어나야 할 때
		{
			current_time = get_time_in_ms();
			if (current_time - beginning_of_last_meal >= ((t_philo *)philo_info)->time_to_die)
			{
				current_time = get_time_in_ms();
				printf("%ld 1 died\n", current_time - beginning_of_simulation);
				is_dead = 1;
				break;
			}

			current_time = get_time_in_ms();
			if (current_time - beginning_of_sleeping >= ((t_philo *)philo_info)->time_to_sleep)
			{
				current_time = get_time_in_ms();
				printf("%ld 1 is thinking\n", current_time - beginning_of_simulation);
				break ;
			}
			usleep(10);
		}
		if (is_dead)
			break ;
	}
	return (NULL);
}

void	*print_philo_state2(void *philo_info)
{
	long	beginning_of_simulation;
	long	current_time;
	long	beginning_of_last_meal;
	long	beginning_of_sleeping;
	int		is_dead;

	is_dead = 0;
	beginning_of_simulation = get_time_in_ms();
	while (1)
	{
		current_time = get_time_in_ms();
		printf("%ld 2 has taken a fork\n", current_time - beginning_of_simulation);
		current_time = get_time_in_ms();
		printf("%ld 2 has taken a fork\n", current_time - beginning_of_simulation);

		beginning_of_last_meal = get_time_in_ms();
		printf("%ld 2 is eating\n", beginning_of_last_meal - beginning_of_simulation);
		usleep(1000 * ((t_philo *)philo_info)->time_to_eat);

		beginning_of_sleeping = get_time_in_ms();
		printf("%ld 2 is sleeping\n", beginning_of_sleeping - beginning_of_simulation);
		
		while (1) 	// 자다가 죽을 경우, 자다가 깨어나야 할 때
		{
			current_time = get_time_in_ms();
			if (current_time - beginning_of_last_meal >= ((t_philo *)philo_info)->time_to_die)
			{
				current_time = get_time_in_ms();
				printf("%ld 2 died\n", current_time - beginning_of_simulation);
				is_dead = 1;
				break ;
			}
			current_time = get_time_in_ms();
			if (current_time - beginning_of_sleeping >= ((t_philo *)philo_info)->time_to_sleep)
			{
				current_time = get_time_in_ms();
				printf("%ld 2 is thinking\n", current_time - beginning_of_simulation);
				break ;
			}
			usleep(10);
		}
		if (is_dead)
			break ;
	}
	return (NULL);
}

//void	*hello(void *philo_info)
//{
//	printf("hello from thread 2\n");
//	return (NULL);
//}

int main(int ac, char **av)
{
	pthread_t	thread1;
	pthread_t	thread2;
	t_philo		philo_info;

	philo_info.num_of_philo = ft_atoi(av[1]);
	philo_info.time_to_die = (long)ft_atoi(av[2]);
	philo_info.time_to_eat = (long)ft_atoi(av[3]);
	philo_info.time_to_sleep = (long)ft_atoi(av[4]);

	//printf("current time:%ld\n", get_time_in_ms());

	if (pthread_create(&thread1, NULL, print_philo_state, &philo_info) != 0)
		printf("failed to create the thread\n");
	else
		printf("thread 1 created\n");

	//if (pthread_create(&thread2, NULL, print_philo_state2, &philo_info) != 0)
	//	printf("failed to create the thread\n");
	//else
	//	printf("thread 2 created\n");


	if (pthread_join(thread1, NULL) != 0)
		printf("failed to join the thread1 \n");
	else
		printf("thread1 finished execution\n");

	//if (pthread_join(thread2, NULL) != 0)
	//	printf("failed to join the thread 2 \n");
	//else
	//	printf("thread 2 finished execution\n");

	return (0);
}
