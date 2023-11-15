#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* num)
{
	int id = *(int*)num;

	while (1)
	{
		//// 철학자가 생각하는 부분
        printf("Philosopher %d is thinking.\n", id);

		// 왼쪽 포크 획득
		pthread_mutex_lock(&forks[id]);
		printf("philo %d has taken a fork\n", id);

		// 오른쪽 포크 획득 (다음 철학자의 왼쪽 포크)
		pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
		printf("philo %d has taken a fork\n", id);

		// 철학자가 먹는 부분
		printf("Philosopher %d is eating.\n", id);
		sleep(1); // 먹는 행위를 시뮬레이션

		// 왼쪽 포크 해제
		pthread_mutex_unlock(&forks[id]);
		// 오른쪽 포크 해제
		pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);

		// 철학자가 식사를 마치고 다시 생각하는 부분
	}
	return NULL;
}

int main()
{
	pthread_t philosophers[NUM_PHILOSOPHERS];
	int philosopher_numbers[NUM_PHILOSOPHERS];

	// 뮤텍스 초기화
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
		philosopher_numbers[i] = i;
	}

	// 철학자 스레드 생성
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		pthread_create(&philosophers[i], NULL, philosopher, &philosopher_numbers[i]);
	}

	// 철학자 스레드 종료 대기
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		pthread_join(philosophers[i], NULL);
	}

	// 뮤텍스 파괴
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		pthread_mutex_destroy(&forks[i]);
	}

	return 0;
}
