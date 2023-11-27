#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_info
{
	int				num_of_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				num_of_times_each_p_must_eat;
	long			t_begin_simul_from_70s;
	pthread_mutex_t	*forks_lock;
	pthread_mutex_t anyone_dead_lock;
	int				*forks_occupied;
	int				is_anyone_dead;
}	t_info;

typedef struct s_philo
{
	t_info			*i;
	int 			philo_idx;
	long			t_begin_last_meal;
	int				am_i_dead;
	int				hold_l_fork;
	int				hold_r_fork;
	int 			*is_l_fork_occupied;
	int 			*is_r_fork_occupied;
	pthread_mutex_t *l_fork_lock;
	pthread_mutex_t *r_fork_lock;
	int				times_i_ate;
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
int	take_left_fork(t_philo *p);
int	take_right_fork(t_philo *p);

t_philo **init_philo(t_info *info);
t_info *init_shared_info(char **av);
