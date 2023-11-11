#include <stdio.h>
#include <pthread.h>

int	counter = 0;
pthread_mutex_t	lock;


void	*increment_counter(void *arg)
{
	//pthread_mutex_lock(&lock);

	int	i;

	i = 0;
	while (i < 10000)
	{
		counter++;
		printf("counter i:%d\n", counter);
		i++;
	}
	//pthread_mutex_unlock(&lock);
	return (NULL);
}

int main()
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_t	thread3;
	pthread_t	thread4;


	pthread_mutex_init(&lock, NULL);

	pthread_create(&thread1, NULL, increment_counter, NULL);
	pthread_create(&thread2, NULL, increment_counter, NULL);
	pthread_create(&thread3, NULL, increment_counter, NULL);
	pthread_create(&thread4, NULL, increment_counter, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);

	pthread_mutex_destroy(&lock);

	return (0);
}