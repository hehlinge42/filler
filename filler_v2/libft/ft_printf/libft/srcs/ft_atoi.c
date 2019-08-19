/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 12:23:55 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/23 11:30:42 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int i;
	int res;
	int is_neg;

	i = 0;
	is_neg = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		is_neg = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res < 0 && is_neg)
			return (0);
		else if (res < 0 && !is_neg)
			return (-1);
		res = res * 10 + (int)str[i] - '0';
		i++;
	}
	if (is_neg)
		return (-res);
	return (res);
}
