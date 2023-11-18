#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t	fork1;

//int	counter = 0;

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
	long	begin_of_simul;
	int		*flag_anyone_die;
	int		has_left_fork;
	int		has_right_fork;
}	t_philo;

int	is_this_philo_starve_to_die(long begin_of_last_meal, t_philo *d)
{
	long	current_time;

	if (*(d->flag_anyone_die))
		return (1);
	current_time = get_time_in_ms();
	if (current_time - begin_of_last_meal >= d->time_to_die)
	{
		*(d->flag_anyone_die) = 1;
		current_time = get_time_in_ms();
		printf("%ld %d died\n", current_time - d->begin_of_simul, d->philo_idx);
		return (1);
	}
	return (0);
}

void	*print_philo_state(void *philo_info)
{
	long	begin_of_last_meal;
	long	begin_of_sleeping;
	long	current_time;
	t_philo	*d;

	d = (t_philo *)philo_info;
	d->begin_of_simul = get_time_in_ms();
	begin_of_last_meal = d->begin_of_simul;
	while (1)
	{
		if(is_this_philo_starve_to_die(begin_of_last_meal, d))
			return (NULL);
		if (d->has_left_fork == 0)
		{
			if (*(d->flag_anyone_die))
				return (NULL);
			current_time = get_time_in_ms();
			if(is_this_philo_starve_to_die(begin_of_last_meal, d))
				return (NULL);
			printf("%ld %d has taken aaa fork\n", current_time - d->begin_of_simul, d->philo_idx);
			d->has_left_fork = 1;
		} // has_left_fork == 1 ㅎㅐ야하는거 아아닌닌가가?
		if (d->has_right_fork == 0 && d->num_of_philo > 1)
		{
			if (d->flag_anyone_die)
				return (NULL);
			if(is_this_philo_starve_to_die(begin_of_last_meal, d))
				return (NULL);
			current_time = get_time_in_ms();
			printf("%ld %d has taken a fork\n", current_time - d->begin_of_simul, d->philo_idx);
			d->has_right_fork = 1;
		}
		if (d->has_left_fork && d->has_right_fork)
		{
			if (d->flag_anyone_die)
				return (NULL);
			if(is_this_philo_starve_to_die(begin_of_last_meal, d))
				return (NULL);
			begin_of_last_meal = get_time_in_ms();
			printf("%ld %d is eating\n", begin_of_last_meal - d->begin_of_simul, d->philo_idx);
			usleep(1000 * (d->time_to_eat));
		}
		else
			continue;
		if(is_this_philo_starve_to_die(begin_of_last_meal, d))
			return (NULL);
		begin_of_sleeping = get_time_in_ms();
		printf("%ld %d is sleeping\n", begin_of_sleeping - d->begin_of_simul, d->philo_idx);
		while (1)
		{
			current_time = get_time_in_ms();
			if (current_time - begin_of_sleeping >= (d->time_to_sleep))
			{
				if(is_this_philo_starve_to_die(begin_of_last_meal, d))
					return (NULL);
				current_time = get_time_in_ms();
				printf("%ld %d is thinking\n", current_time - d->begin_of_simul, d->philo_idx);
				break ;
			}
			usleep(10);
		}
	}
	return (NULL);
}

int main(int ac, char **av)
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_t	th_death_monitor;
	t_philo		philo_info[2];
	int			is_anyone_dead;
	
	if (ac != 5 && ac != 6)
	{
		printf("invalid ac\n");
		return (0);
	}

	is_anyone_dead = 0;
	philo_info[0].num_of_philo = ft_atoi(av[1]);
	philo_info[0].time_to_die = (long)ft_atoi(av[2]);
	philo_info[0].time_to_eat = (long)ft_atoi(av[3]);
	philo_info[0].time_to_sleep = (long)ft_atoi(av[4]);
	philo_info[0].flag_anyone_die = &is_anyone_dead;
	philo_info[0].has_left_fork = 0;
	philo_info[0].has_right_fork = 0;

	pthread_mutex_init(&fork1, NULL);

	philo_info[0].philo_idx = 1;
	pthread_create(&thread1, NULL, print_philo_state, &philo_info[0]);

	pthread_join(thread1, NULL);

	pthread_mutex_destroy(&fork1);

	return (0);
}
