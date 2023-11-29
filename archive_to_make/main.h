#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> // usleep
#include <pthread.h>
#include <stdlib.h>

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIED 4

typedef	struct s_shared
{
	int				num_of_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				t_each_philo_must_eat;
	long			t_begin_simul_from_70s;
	pthread_mutex_t	*forks_lock;
	pthread_mutex_t	anyone_dead_lock;
	int				*forks_occupied;
	int				is_anyone_dead;
} t_shared;

typedef struct s_philo
{
	t_shared		*sh;
	int				philo_idx;
	long			t_begin_last_meal;
	int				am_i_dead;
	int				hold_left_f;
	int				hold_right_f;
	int				*is_left_f_occupied;
	int				*is_right_f_occupied;
	pthread_mutex_t	*left_f_lock;
	pthread_mutex_t	*right_f_lock;
	int				times_i_ate;
}	t_philo;


int			ft_atoi(const char *str);
t_shared	*init_shared_info(char **av);
t_philo		**init_philo(t_shared *shared);
void		init_mutex(t_philo **philos);
void 		destroy_mutex(t_philo **philos);
long		get_time(t_philo *p);
long		get_t_begin_simul(void);
void		thread_control(t_philo **philos);
void		*philo_control(void *ptr);
int			is_alive(t_philo *p);
void		print_routine(t_philo *p, int action);



#endif