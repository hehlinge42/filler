/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:28:18 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/11 19:34:08 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>

int		ft_float_size(unsigned long long mantissa)
{
	unsigned long long	mask;
	int					count;

	mask = (unsigned long long)1 << (unsigned long long)63;
	count = 0;
	while (!(mask & mantissa))
	{
		count++;
		mask >>= 1;
	}
	return (64 - count);
}

void	ft_divide_nb(char to_divide[BUF_FLOAT + 1])
{
	int		i;
	int		tmp;
	int		retenue;

	i = 0;
	retenue = 0;
	tmp = 0;
	while (to_divide[i] == '0')
		i++;
	while (i < BUF_FLOAT)
	{
		tmp = to_divide[i] - '0';
		to_divide[i] = (tmp / 2) + retenue + '0';
		if (tmp % 2)
			retenue = 5;
		else
			retenue = 0;
		i++;
	}
}

void	ft_double_nb(char to_double[BUF_FLOAT + 1])
{
	int		i;
	int		tmp;
	int		retenue;

	i = BUF_FLOAT;
	retenue = 0;
	while (--i >= 0)
	{
		tmp = (2 * (to_double[i] - '0')) + retenue;
		retenue = tmp / 10;
		to_double[i] = (tmp % 10) + '0';
	}
}

void	ft_sum(char part1[BUF_FLOAT + 1], char part2[BUF_FLOAT + 1], int opt)
{
	int		i;
	int		retenue;
	int		tmp;

	if (opt)
		i = opt;
	else
		i = BUF_FLOAT;
	retenue = 0;
	while (--i >= 0)
	{
		tmp = (part1[i] - '0') + (part2[i] - '0') + retenue;
		retenue = tmp / 10;
		part2[i] = (tmp % 10) + '0';
	}
}
