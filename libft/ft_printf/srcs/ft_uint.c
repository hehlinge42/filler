/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:36:01 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 13:40:46 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/ft_printf.h"

static ull	ft_return_unb(t_printf *strct, va_list va)
{
	if (strct->length == -1)
		return (unsigned long long)va_arg(va, unsigned int);
	else if (strct->length == LENGTH_H)
		return (unsigned long long)((unsigned short)va_arg(va, unsigned int));
	else if (strct->length == LENGTH_HH)
		return (unsigned long long)((unsigned char)va_arg(va, unsigned int));
	else if (strct->length == LENGTH_L)
		return (unsigned long long)((unsigned long)va_arg(va, unsigned long));
	else if (strct->length == LENGTH_LL)
		return (va_arg(va, unsigned long long));
	return (-1);
}

static int	ft_count_chars_uzero(t_printf *strct, int *count_char)
{
	int		count;

	count = 1;
	if (strct->convert == CONVERT_XX || strct->convert == CONVERT_U)
		strct->convert = CONVERT_X;
	if (strct->precision == 0)
		count = 0;
	if (!((strct->precision == 0
		&& (strct->convert == CONVERT_X || strct->convert == CONVERT_P))
		|| (strct->precision == 0 && strct->convert == CONVERT_O
		&& strct->flag[FLAG_HASH] == -1)))
		count = 1;
	*count_char = count;
	return (count);
}

static void	ft_uint_zero(t_printf *strct, t_buffer *buffer)
{
	int		letter;
	int		count_char;
	int		count;

	letter = ft_find_letter(strct);
	count = ft_count_chars_uzero(strct, &count_char);
	if (strct->flag[FLAG_HASH] == '#' && strct->convert == CONVERT_P)
		count_char += 2;
	if (strct->precision != -1 && strct->precision > count)
		count_char += strct->precision - count;
	if (strct->flag[FLAG_MINUS] == -1 && !(strct->convert == CONVERT_P
		&& strct->flag[FLAG_ZERO] == '0'))
		ft_print_width(strct, buffer, count_char);
	if (strct->flag[FLAG_HASH] == '#' && strct->convert == CONVERT_P)
		ft_display_hash(strct, buffer);
	ft_display_precision(strct, count, buffer, 0);
	if (!((strct->precision == 0 && (strct->convert == CONVERT_X
		|| strct->convert == CONVERT_P)) || (strct->precision == 0
		&& strct->convert == CONVERT_O && strct->flag[FLAG_HASH] == -1)))
		ft_write_buf("0", buffer, 1);
	if (strct->flag[FLAG_MINUS] == '-' || (strct->convert == CONVERT_P
		&& strct->flag[FLAG_ZERO] == '0'))
		ft_print_width(strct, buffer, count_char);
}

static int	ft_count_chars_uint(t_printf *strct, int *count_char,
	long long nb, int base)
{
	int		count;

	count = ft_ucount_chars(nb, base);
	if (strct->flag[FLAG_HASH] == '#' && strct->convert == CONVERT_O)
		count++;
	*count_char = count;
	if (strct->precision != -1 && strct->precision > *count_char)
		*count_char += strct->precision - *count_char;
	if (strct->flag[FLAG_HASH] == '#'
		&& (strct->convert == CONVERT_X || strct->convert == CONVERT_XX
		|| strct->convert == CONVERT_P))
		*count_char += 2;
	return (count);
}

int			ft_uint(t_printf *strct, t_buffer *buffer, va_list va)
{
	unsigned long long	nb;
	int					count;
	int					count_char;
	int					base;
	char				letter;

	nb = ft_return_unb(strct, va);
	if (nb == 0)
		ft_uint_zero(strct, buffer);
	if (nb == 0)
		return (1);
	base = ft_find_base(strct, va);
	letter = ft_find_letter(strct);
	count = ft_count_chars_uint(strct, &count_char, nb, base);
	if (strct->flag[FLAG_ZERO] == '0' && strct->precision == -1)
		ft_display_hash(strct, buffer);
	if (strct->flag[FLAG_MINUS] == -1)
		ft_print_width(strct, buffer, count_char);
	if (!(strct->flag[FLAG_ZERO] == '0' && strct->precision == -1))
		ft_display_hash(strct, buffer);
	ft_display_precision(strct, count, buffer, 0);
	ft_putnbr_ullbase(nb, base, letter, buffer);
	if (strct->flag[FLAG_MINUS] != -1)
		ft_print_width(strct, buffer, count_char);
	return (1);
}
