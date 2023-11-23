#include "main.h"

int	take_left_fork(t_philo *p, char l_or_r)
{
	if (!is_alive(p))
		return (p->is_dead);

// 왼쪽포크의 인덱스는 필로 인덱스와 같다.

		print(p, FORK);
		p->hold_l_fork = 1;

	return (p->is_dead);
}
