/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:31:53 by jungmiho          #+#    #+#             */
/*   Updated: 2023/12/04 20:40:18 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*choose_action_str(int action)
{
	char	*action_str;

	action_str = 0;
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
	return (action_str);
}

void	print(t_philo *p, int action)
{
	char	*action_str;

	pthread_mutex_lock(&(p->i->print_lock));
	if (p->i->is_died_printed == 0)
	{
		action_str = choose_action_str(action);
		printf("%ld %d %s\n", get_time(p), p->philo_idx + 1, action_str);
		if (action == DIED)
		{
			p->i->is_died_printed = 1;
		}
	}
	pthread_mutex_unlock(&(p->i->print_lock));
}
