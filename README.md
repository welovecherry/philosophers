# 42 Seoul Philosophers Project

## Overview
A simulation of dining philosophers problem implementation for 42 Seoul curriculum. This project focuses on process synchronization and deadlock prevention using threads and mutexes.

## Key Features
* Concurrent execution of philosopher processes
* Deadlock prevention mechanisms
* Real-time monitoring of philosopher states
* Precise time management for actions

## Technical Requirements
* Language: C
* Allowed functions:
  - memset, printf, malloc, free, write
  - usleep, gettimeofday
  - pthread_create, pthread_detach, pthread_join
  - pthread_mutex_init, pthread_mutex_destroy
  - pthread_mutex_lock, pthread_mutex_unlock

## Program Arguments
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Rules
### Base Rules
* Each philosopher needs two forks to eat
* Philosophers alternate between eating, sleeping, and thinking
* Program ends if a philosopher dies of starvation
* Each fork should be protected by a mutex

### Timing Requirements
* Display state changes with timestamps in milliseconds
* Maximum 10ms delay between death and death message
* Avoid data races

## Output Format
* Timestamp format: [timestamp_in_ms]
* State messages:
  - has taken a fork
  - is eating
  - is sleeping
  - is thinking
  - died

## Error Handling
* Invalid arguments: display error message
* Resource allocation failures: clean exit
* Must work with 2+ philosophers
