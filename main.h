#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_OF_PHILO 3
#define TIME_DIE 5000
#define TIME_EAT 1000
#define TIME_SLEEP 6000

typedef struct s_info
{
	int				num_of_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			t_begin_simul_from_70s;
	pthread_mutex_t	*forks_lock;
	int				*forks_occupied;
}	t_info;

typedef struct s_philo
{
	int 	philo_idx;
	long	t_begin_last_meal;
	int		is_dead;
	int		hold_l_fork;
	int		hold_r_fork;
	t_info	*i;
}	t_philo;

#define FORK 0
#define EAT 1
#define SLEEP 2
#define THINK 3
#define DIED 4

long get_time(t_philo *p);
long get_t_begin_simul();
int take_two_forks(t_philo *p);
int eating(t_philo *p);
int sleeping(t_philo *p);
int thinking(t_philo *p);
int print(t_philo *p, int action);
int is_alive(t_philo *p);
void *philo(void *ptr);
void	init_mutex(t_philo **philos);
void	destroy_mutex(t_philo **philos);
void	thread_control(t_philo **philos);
int	take_left_fork(t_philo *p, char l_or_r);
int	take_right_fork(t_philo *p, char l_or_r);

t_philo **init_philo(void);