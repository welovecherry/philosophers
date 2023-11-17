#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// mutex lock prac
pthread_mutex_t	lock;
int				counter = 0;

void	*monitor_death(void *flag_someone_died)
{
	int	*is_anyone_died;

	is_anyone_died = (int *)flag_someone_died;
	//printf("check %d\n", is_anyone_died);
	while (1)
	{
		if (counter == 5)
		{
			*is_anyone_died = 1;
			printf("someone died!!!\n");
			return (NULL);
		}
	}

	return (NULL);
}


void	*print_state1(void *flag_anyone_died)
{
	int	*d;

	d = (int *)flag_anyone_died;
	while (1)
	{
		if (*d == 1)
		{
			printf("state 1 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		pthread_mutex_lock(&lock);

		if (*d == 1)
		{
			printf("state 1 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}

		printf("1 has taken a fork\n");
		usleep(50000);
		if (*d == 1)
		{
			printf("state 1 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		printf("1 has taken a fork\n");
		usleep(50000);
		if (*d == 1)
		{
			printf("state 1 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		printf("1 is eating, counter:%d \n", counter);
		pthread_mutex_unlock(&lock);
		if (*d == 1)
		{
			printf("state 1 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		counter ++;
		usleep(50000);
	}
	return (NULL);
}

void	*print_state2(void *flag_anyone_died)
{
	int	*d;

	d = (int *)flag_anyone_died;
	while (1)
	{
		if (*d == 1)
		{
			printf("state 2 died\n\n");
			return (NULL);
		}
		pthread_mutex_lock(&lock);

		if (*d == 1)
		{
			printf("state 2 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}

		printf("2 has taken a fork\n");
		usleep(50000);
		if (*d == 1)
		{
			printf("state 2 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		printf("2 has taken a fork\n");
		usleep(50000);
		if (*d == 1)
		{
			printf("state 2 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		printf("2 is eating, counter:%d \n", counter);
		pthread_mutex_unlock(&lock);
		if (*d == 1)
		{
			printf("state 2 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		counter ++;
		usleep(50000);
	}
	return (NULL);
}

void	*print_state3(void *flag_anyone_died)
{
	int	*d;

	d = (int *)flag_anyone_died;
	while (1)
	{
		if (*d == 1)
		{
			printf("state 3 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		pthread_mutex_lock(&lock);
		if (*d == 1)
		{
			printf("state 3 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		printf("3 has taken a fork\n");
		usleep(50000);
		if (*d == 1)
		{
			printf("state 3 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		printf("3 has taken a fork\n");
		usleep(50000);
		if (*d == 1)
		{
			printf("state 3 died\n\n");
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		printf("3 is eating, counter:%d \n", counter);
		pthread_mutex_unlock(&lock);
		if (*d == 1)
		{
			printf("state 3 died\n\n");
			return (NULL);
		}
		counter ++;
		usleep(50000);
	}
	return (NULL);
}

int main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_t	thread3;
	pthread_t	god;
	void		*flag_anyone_died;

	flag_anyone_died = malloc(sizeof(int));
	if (flag_anyone_died == NULL)
		return (1);
	*(int *)flag_anyone_died = 0;

	pthread_mutex_init(&lock, NULL);

	pthread_create(&god, NULL, &monitor_death, flag_anyone_died);

	pthread_create(&thread1, NULL, &print_state1, flag_anyone_died);
	pthread_create(&thread2, NULL, &print_state2, flag_anyone_died);
	pthread_create(&thread3, NULL, &print_state3, flag_anyone_died);
	

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(god, NULL);

	pthread_mutex_destroy(&lock);
	free(flag_anyone_died);

	return (0);
}