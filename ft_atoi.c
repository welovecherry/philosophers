/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:24:59 by jungmiho          #+#    #+#             */
/*   Updated: 2023/11/29 17:22:22 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*pass_whitespace_reach_str_num(char *str, int *sign)
{
	while ((9 <= *str && *str <= 13) || (*str == 32))
		str++;
	*sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

int	ft_atoi(char *str)
{
	char		*str_num;
	long long	result;
	long long	prev_result;
	int			sign;

	str_num = pass_whitespace_reach_str_num((char *)str, &sign);
	if (str_num == NULL)
		return (-1);
	result = 0;
	prev_result = result;
	while ('0' <= *str_num && *str_num <= '9')
	{
		result = (result * 10) + (*str_num - '0');
		if (result / 10 != prev_result)
		{
			if (sign == 1)
				return (-1);
			if (sign == -1)
				return (0);
		}
		str_num++;
		prev_result = result;
	}
	result *= sign;
	return ((int)result);
}
