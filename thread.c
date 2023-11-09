#include <pthread.h>
#include <stdio.h>

void	*thread_func(void *arg)
{
	printf("hello from the thread\n");
	return NULL;
}


int	main()
{
	pthread_t	my_thread;

	if (pthread_create(&my_thread, NULL, thread_func, NULL) != 0)
		printf("failed to create the thread\n");
	else
		printf("thread created\n");
	
	if (pthread_join(my_thread, NULL) != 0)
		printf("failed to join the thread\n");
	else
		printf("thread finished execution\n");


	return (0);
}