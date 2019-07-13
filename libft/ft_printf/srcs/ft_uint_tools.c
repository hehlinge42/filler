/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:03:11 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 13:40:44 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			ft_ucount_chars(unsigned long long ull, int base_size)
{
	int					count;

	count = 1;
	while (ull / base_size > 0)
	{
		ull /= base_size;
		count++;
	}
	return (count);
}

char		ft_find_letter(t_printf *strct)
{
	if (strct->convert == CONVERT_X || strct->convert == CONVERT_P
		|| strct->convert == CONVERT_BB)
		return ('a');
	else if (strct->convert == CONVERT_XX)
		return ('A');
	return (0);
}

int			ft_find_base(t_printf *strct, va_list va)
{
	int		input_base;

	if (strct->convert == CONVERT_X || strct->convert == CONVERT_XX
		|| strct->convert == CONVERT_P)
		return (16);
	else if (strct->convert == CONVERT_O)
		return (8);
	else if (strct->convert == CONVERT_B)
		return (2);
	else if (strct->convert == CONVERT_BB)
	{
		input_base = va_arg(va, int);
		if (input_base < -36 || input_base > 36)
			return (36);
		else if (input_base == 0 || input_base == 1 || input_base == -1)
			return (10);
		else if (input_base < 0)
			return (-input_base);
		else
			return (input_base);
	}
	return (10);
}
