/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:24:59 by jungmiho          #+#    #+#             */
/*   Updated: 2023/12/04 17:23:31 by jungmiho         ###   ########.fr       */
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
	int			sign;
	int			len;

	str_num = pass_whitespace_reach_str_num((char *)str, &sign);
	if (sign == -1)
		return (-1);
	result = 0;
	len = 0;
	while ('0' <= *str_num && *str_num <= '9')
	{
		result = (result * 10) + (*str_num - '0');
		str_num++;
		len++;
	}
	if (len == 0 || *str_num != '\0')
		return (-1);
	if (len > 11 || result > 2147483647)
		return (-1);
	return ((int)result);
}

int	check_num(char *str, int min_allowed_value)
{
	int	num_av;

	num_av = ft_atoi(str);
	if (num_av < min_allowed_value)
	{
		return (-1);
	}
	return (num_av);
}
