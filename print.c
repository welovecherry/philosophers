/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:31:53 by jungmiho          #+#    #+#             */
/*   Updated: 2023/11/29 22:08:12 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*choose_action_str(int action)
{
	char	*action_str;

	if (action == FORK)
		action_str = "has taken a fork";
	else if (action == EAT)
		action_str = "is eating";
	else if (action == SLEEP)
		action_str = "is sleeping";
	else if (action == THINK)
		action_str = "is thinking";
	else if (action == DIED)
		action_str = "died";
	else
		action_str = "UNKNOWN"; // how can i delete this line?
	return (action_str);
}

// TODO: ./philo 100 410 200 200 했을 때 죽었다고 출력 여러번 됨
// TODO: 한 철학자가 죽었는데도 다른 철학자의 로그 출력됨

void	print(t_philo *p, int action)
{
	char	*action_str;

	action_str = choose_action_str(action);
	pthread_mutex_lock(&(p->i->print_lock));
	
	// TODO: died print ㅇㅣ후에는 하하지지마마라라
	if (p->am_i_dead)
		

	if (1)
		printf("%ld %d %s\n", get_time(p), p->philo_idx + 1, action_str);
	pthread_mutex_unlock(&(p->i->print_lock));
}
