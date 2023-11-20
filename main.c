#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


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

typedef struct s_shared_info
{
	int				forks[2];
	pthread_mutex_t	fork_lock[2];
	int				is_anyone_dead;
}	t_shared_info;

typedef struct	s_philo
{
	int		num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		philo_idx;
	long	begin_simul;
	int		*flag_anyone_die;
	int		*left_fork;
	int		*right_fork;
	pthread_mutex_t		*left_fork_lock;
	pthread_mutex_t		*right_fork_lock;
	int		have_left_fork;
	int		have_right_fork;
	t_shared_info *shared;
}	t_philo;


int check_starvation(t_philo *philosopher, long begin_last_meal)
{
    long current_time = get_time_in_ms();

    if (*(philosopher->flag_anyone_die)) {
        return 1;
    }
    if (current_time - begin_last_meal >= philosopher->time_to_die)
	{
        *(philosopher->flag_anyone_die) = 1;
		printf("here\n");
        return 1;
    }
    return 0;
}


int take_fork(int *fork, pthread_mutex_t *fork_lock, int philosopher_idx, long begin_simul) 
{
    pthread_mutex_lock(fork_lock);
    if (*fork == 0) {
        *fork = 1;
        printf("%ld %d has taken a fork\n", get_time_in_ms() - begin_simul, philosopher_idx);
        return 1;
    }
    pthread_mutex_unlock(fork_lock);
    return 0;
}

void release_forks(int *left_fork, pthread_mutex_t *left_lock, int *right_fork, pthread_mutex_t *right_lock)
{
	// 왼쪽 포크를 내려놓기
	*left_fork = 0;
	pthread_mutex_unlock(left_lock);

	// 오른쪽 포크를 내려놓기
	*right_fork = 0;
	pthread_mutex_unlock(right_lock);
}


void eat(t_philo *philosopher, long *begin_last_meal, long begin_simul)
{
    *begin_last_meal = get_time_in_ms();
    printf("%ld %d is eating\n", *begin_last_meal - begin_simul, philosopher->philo_idx);
    usleep(1000 * (philosopher->time_to_eat));
}

void sleep_and_think(t_philo *philosopher)
{
    long begin_sleeping = get_time_in_ms();
    printf("%ld %d is sleeping\n", begin_sleeping - philosopher->begin_simul, philosopher->philo_idx);
    usleep(1000 * (philosopher->time_to_sleep));
    printf("%ld %d is thinking\n", get_time_in_ms() - philosopher->begin_simul, philosopher->philo_idx);
}

void *print_even_philo_state(void *philo_info) {
    t_philo *d = (t_philo *)philo_info;
    d->begin_simul = get_time_in_ms();
    long begin_last_meal = d->begin_simul;

    while (1) {
        if (check_starvation(d, begin_last_meal)) return NULL;

        if (d->have_left_fork == 0 && take_fork(d->left_fork, d->left_fork_lock, d->philo_idx, d->begin_simul))
            d->have_left_fork = 1;

        if (d->have_right_fork == 0 && take_fork(d->right_fork, d->right_fork_lock, d->philo_idx, d->begin_simul))
            d->have_right_fork = 1;

        if (d->have_left_fork && d->have_right_fork) {
            eat(d, &begin_last_meal, d->begin_simul);
            release_forks(d->left_fork, d->left_fork_lock, d->right_fork, d->right_fork_lock);
            d->have_left_fork = 0;
            d->have_right_fork = 0;
        }

        sleep_and_think(d);
    }
    return NULL;
}
void *print_odd_philo_state(void *philo_info) {
    t_philo *d = (t_philo *)philo_info;
    d->begin_simul = get_time_in_ms();
    long begin_last_meal = d->begin_simul;

    while (1) {
        if (check_starvation(d, begin_last_meal)) return NULL;

        if (d->have_right_fork == 0 && take_fork(d->right_fork, d->right_fork_lock, d->philo_idx, d->begin_simul))
            d->have_right_fork = 1;

        if (d->have_left_fork == 0 && take_fork(d->left_fork, d->left_fork_lock, d->philo_idx, d->begin_simul))
            d->have_left_fork = 1;

        if (d->have_left_fork && d->have_right_fork) {
            eat(d, &begin_last_meal, d->begin_simul);
            release_forks(d->left_fork, d->left_fork_lock, d->right_fork, d->right_fork_lock);
            d->have_left_fork = 0;
            d->have_right_fork = 0;
        }

        sleep_and_think(d);
    }
    return NULL;
}

int main(int ac, char **av)
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_t	th_death_monitor;
	t_philo		philo_info[2];
	t_shared_info	shared_info;
	
	if (ac != 5 && ac != 6)
	{
		printf("invalid ac\n");
		return (0);
	}

	shared_info.is_anyone_dead = 0;
	shared_info.forks[0] = 0;
	shared_info.forks[1] = 0;

	philo_info[0].num_of_philo = ft_atoi(av[1]);
	philo_info[0].time_to_die = (long)ft_atoi(av[2]);
	philo_info[0].time_to_eat = (long)ft_atoi(av[3]);
	philo_info[0].time_to_sleep = (long)ft_atoi(av[4]);
	philo_info[0].flag_anyone_die = &shared_info.is_anyone_dead;
	philo_info[0].left_fork = &shared_info.forks[0];
	philo_info[0].right_fork = &shared_info.forks[1];
	philo_info[0].left_fork_lock = &shared_info.fork_lock[0];
	philo_info[0].right_fork_lock = &shared_info.fork_lock[1];
	philo_info[0].have_left_fork = 0;
	philo_info[0].have_right_fork = 0;
	philo_info[0].philo_idx = 1;
	philo_info[0].shared = &shared_info;

	philo_info[1].num_of_philo = ft_atoi(av[1]);
	philo_info[1].time_to_die = (long)ft_atoi(av[2]);
	philo_info[1].time_to_eat = (long)ft_atoi(av[3]);
	philo_info[1].time_to_sleep = (long)ft_atoi(av[4]);
	philo_info[1].flag_anyone_die = &shared_info.is_anyone_dead;
	philo_info[1].left_fork = &shared_info.forks[1];
	philo_info[1].right_fork = &shared_info.forks[0];
	philo_info[1].left_fork_lock = &shared_info.fork_lock[1];
	philo_info[1].right_fork_lock = &shared_info.fork_lock[0];
	philo_info[1].have_left_fork = 0;
	philo_info[1].have_right_fork = 0;
	philo_info[1].philo_idx = 2;
	philo_info[1].shared = &shared_info;

	pthread_mutex_init(&(shared_info.fork_lock[0]), NULL);
	pthread_mutex_init(&(shared_info.fork_lock[1]), NULL);

	philo_info[0].philo_idx = 1;
	pthread_create(&thread1, NULL, print_even_philo_state, &philo_info[0]);
	philo_info[1].philo_idx = 2;
	pthread_create(&thread2, NULL, print_odd_philo_state, &philo_info[1]);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&shared_info.fork_lock[0]);
	pthread_mutex_destroy(&shared_info.fork_lock[1]);

	return (0);
}
