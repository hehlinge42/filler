/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:40:20 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 11:18:07 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../includes/ft_printf.h"

static void	ft_putnstr(char *str, int n, int opt, t_buffer *buffer)
{
	if (opt)
		ft_write_buf(str, buffer, ft_strlen(str));
	else
		ft_write_buf(str, buffer, n);
}

static int	ft_manage_null(t_printf *strct, t_buffer *buffer)
{
	char	str_null[7];
	int		i;

	str_null[0] = '(';
	str_null[1] = 'n';
	str_null[2] = 'u';
	str_null[3] = 'l';
	str_null[4] = 'l';
	str_null[5] = ')';
	str_null[6] = '\0';
	i = -1;
	if (strct->precision == -1 || strct->precision > 6)
		strct->precision = 6;
	if (strct->flag[FLAG_MINUS] == -1)
		ft_print_width(strct, buffer, strct->precision);
	while (++i < strct->precision && i < 7)
		ft_write_buf(str_null + i, buffer, 1);
	if (strct->flag[FLAG_MINUS] != -1)
		ft_print_width(strct, buffer, strct->precision);
	return (1);
}

int			ft_string(t_printf *strct, t_buffer *buffer, va_list va)
{
	char	*str;
	int		count_char;

	str = va_arg(va, char *);
	if (!str)
		return (ft_manage_null(strct, buffer));
	count_char = ft_strlen(str);
	if (strct->precision != -1 && strct->precision < count_char)
		count_char += strct->precision - count_char;
	if (strct->flag[FLAG_MINUS] == -1)
		ft_print_width(strct, buffer, count_char);
	if (strct->precision == -1)
		ft_putnstr(str, 0, 1, buffer);
	else if (strct->precision != -1)
		ft_putnstr(str, count_char, 0, buffer);
	if (strct->flag[FLAG_MINUS] != -1)
		ft_print_width(strct, buffer, count_char);
	return (1);
}
