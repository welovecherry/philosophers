#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_OF_PHILO 1
#define TIME_DIE 1600
#define TIME_EAT 1000
#define TIME_SLEEP 1500

typedef struct s_info
{
	int num_of_philo;
	long t_die;
	long t_eat;
	long t_sleep;
	long t_begin_simul_from_70s;
} t_info;

typedef struct s_philo
{
	int 	philo_idx;
	long	t_begin_last_meal;
	int		is_dead;
	t_info	*i;
} t_philo;

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