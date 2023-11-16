#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// mutex lock prac
pthread_mutex_t	lock;
int				counter = 0;

void	*print_state1(void *is_dead)
{
	while (1)
	{
		pthread_mutex_lock(&lock);
		printf("1 has taken a fork\n");
		usleep(10000);
		printf("1 has taken a fork\n");
		usleep(10000);
		printf("1 is eating\n");
		pthread_mutex_unlock(&lock);
		usleep(2000000);
	}
	return (NULL);
}


void	*print_state2(void *is_dead)
{
	while (1)
	{
		pthread_mutex_lock(&lock);
		printf("2 has taken a fork\n");
		usleep(10000);
		printf("2 has taken a fork\n");
		usleep(10000);
		printf("2 is eating\n");
		pthread_mutex_unlock(&lock);
		usleep(3000000);
	}
	return (NULL);
}

int main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	//int			is_dead;

	//is_dead = 0;
	pthread_mutex_init(&lock, NULL);

	pthread_create(&thread1, NULL, &print_state1, NULL);
	pthread_create(&thread2, NULL, &print_state2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&lock);

	return (0);
}