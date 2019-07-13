/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:35:35 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 13:20:21 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/ft_printf.h"

static int			ft_count_chars_nb(long long int ll, int base_size)
{
	int					count;
	unsigned long long	ull;

	count = 0;
	if (ll < 0)
	{
		ull = -ll;
		count++;
	}
	else
		ull = (unsigned long long)ll;
	count++;
	while (ull / base_size > 0)
	{
		ull /= base_size;
		count++;
	}
	return (count);
}

static long long	ft_return_nb(t_printf *strct, va_list va)
{
	if (strct->length == -1)
		return (long long)va_arg(va, int);
	else if (strct->length == LENGTH_H)
		return (long long)((short int)va_arg(va, int));
	else if (strct->length == LENGTH_HH)
		return (long long)((char)va_arg(va, int));
	else if (strct->length == LENGTH_L)
		return (long long)((long)va_arg(va, long));
	else if (strct->length == LENGTH_LL)
		return (va_arg(va, long long));
	return (-1);
}

static int			ft_count_chars_int(t_printf *strct, int *count_char,
		long long nb, int base)
{
	int		count;

	count = ft_count_chars_nb(nb, base);
	if (nb == 0 && strct->precision == 0)
		count--;
	*count_char = count;
	if (strct->precision != -1 && strct->precision > *count_char)
		*count_char += strct->precision - count;
	if (nb < 0 && strct->precision != -1 && strct->precision > *count_char - 1)
		*count_char += 1;
	if (nb >= 0 && (strct->flag[FLAG_PLUS] == '+'
				|| strct->flag[FLAG_SPACE] == ' '))
		*count_char += 1;
	return (count);
}

static void			ft_int_if_flag_minus(t_printf *strct, t_buffer *buffer,
		long long nb, int count_char)
{
	if (strct->flag[FLAG_MINUS] == -1)
	{
		if (nb >= 0 && strct->flag[FLAG_ZERO] == '0'
				&& strct->precision == -1
				&& (strct->flag[FLAG_PLUS] == '+'
					|| strct->flag[FLAG_SPACE] == ' '))
			ft_display_flag_plus(strct, buffer);
		if (nb < 0 && (strct->flag[FLAG_ZERO] == '0' && strct->precision == -1))
			ft_write_buf("-", buffer, 1);
		ft_print_width(strct, buffer, count_char);
	}
}

int					ft_int(t_printf *strct, t_buffer *buffer, va_list va)
{
	long long			nb;
	int					count;
	int					count_char;
	int					base;
	unsigned long long	unb;

	nb = ft_return_nb(strct, va);
	unb = (nb < 0) ? -nb : nb;
	base = 10;
	count = ft_count_chars_int(strct, &count_char, nb, base);
	ft_int_if_flag_minus(strct, buffer, nb, count_char);
	if (nb >= 0 && !(strct->flag[FLAG_MINUS] == -1
		&& strct->flag[FLAG_ZERO] == '0' && strct->precision == -1
		&& (strct->flag[FLAG_PLUS] == '+' || strct->flag[FLAG_SPACE] == ' ')))
		ft_display_flag_plus(strct, buffer);
	if (nb < 0 && !(strct->flag[FLAG_MINUS] == -1
				&& strct->flag[FLAG_ZERO] == '0' && strct->precision == -1))
		ft_write_buf("-", buffer, 1);
	ft_display_precision(strct, count, buffer, nb);
	if (nb != 0 || strct->precision != 0)
		ft_putnbr_ullbase(unb, base, 0, buffer);
	if (strct->flag[FLAG_MINUS] != -1)
		ft_print_width(strct, buffer, count_char);
	return (1);
}
