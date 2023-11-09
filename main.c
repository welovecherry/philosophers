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

typedef	struct	s_philo_info
{
	int		num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
}	t_philo_info;

void	*thread_func(void *philo_info)
{
	long	start_time;
	long	current_time;

	start_time = get_time_in_ms();
	while (1)
	{
		current_time = get_time_in_ms();
		printf("%ld 1 has taken a fork\n", current_time - start_time);
		current_time = get_time_in_ms();
		printf("%ld 1 has taken a fork\n", current_time - start_time);

		current_time = get_time_in_ms();
		printf("%ld 1 is eating\n", current_time - start_time);
		usleep(1000 * ((t_philo_info *)philo_info)->time_to_eat);

// 자다가 죽을 경우
		current_time = get_time_in_ms();
		if ()

		current_time = get_time_in_ms();
		printf("%ld 1 is sleeping\n", current_time - start_time);
		usleep(1000 * ((t_philo_info *)philo_info)->time_to_sleep);

		current_time = get_time_in_ms();
		printf("%ld 1 is thinking\n", current_time - start_time);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	long	start_time;
	long	curre_time;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		num_of_philo;
	long	meal_time;
	long	sleeping_start_time;
	int		is_dead;
	pthread_t	thread1;
	t_philo_info philo_info;


	is_dead = 0;
	philo_info.num_of_philo = ft_atoi(av[1]);
	philo_info.time_to_die = (long)ft_atoi(av[2]);
	philo_info.time_to_eat = (long)ft_atoi(av[3]);
	philo_info.time_to_sleep = (long)ft_atoi(av[4]);

	if (pthread_create(&thread1, NULL, thread_func, &philo_info) != 0)
		printf("failed to create the thread\n");
	else
		printf("thread created\n");

	if (pthread_join(thread1, NULL) != 0)
		printf("failed to join the thread\n");
	else
		printf("thread finished execution\n");




	//start_time = get_time_in_ms();
	//while (1)
	//{
	//	curre_time = get_time_in_ms();
	//	printf("%ld 1 has taken a fork\n", curre_time - start_time);
	//	curre_time = get_time_in_ms();
	//	printf("%ld 1 has taken a fork\n", curre_time - start_time);

	//	curre_time = get_time_in_ms();
	//	printf("%ld 1 is eating\n", curre_time - start_time);
	//	usleep(time_to_eat * 1000);
	//	meal_time = get_time_in_ms();

	//	curre_time = get_time_in_ms();
	//	printf("%ld 1 is sleeping\n", curre_time - start_time);
	//	sleeping_start_time = get_time_in_ms();
	//	while (1)
	//	{
	//		curre_time = get_time_in_ms();
	//		if (curre_time - meal_time >= time_to_die)
	//		{
	//			curre_time = get_time_in_ms();
	//			printf("%ld 1 died\n", curre_time - start_time);
	//			is_dead = 1;
	//			break ;
	//		}
	//		if (curre_time - sleeping_start_time >= time_to_sleep)
	//			break ;
	//		usleep(10);
	//	}
	//	if (is_dead)
	//		break ;
	//}
	return (0);
}
