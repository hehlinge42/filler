/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:29:26 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 12:42:43 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>

int		ft_char(t_printf *strct, t_buffer *buffer, va_list va)
{
	char	c;
	int		count;

	if (strct->convert == CONVERT_C)
		c = (char)va_arg(va, int);
	else
		c = strct->fake_c;
	count = 1;
	if (strct->flag[FLAG_MINUS] != '-' && strct->width > 1)
		ft_print_width(strct, buffer, count);
	if (c)
		ft_write_buf(&c, buffer, 1);
	else if (!c && strct->convert == CONVERT_C)
	{
		buffer->count_total_char += buffer->index;
		buffer->index = 0;
		ft_putstr(buffer->buf);
		ft_bzero(buffer->buf, BUF_SIZE);
		ft_putchar_fd(c, FD);
		buffer->count_total_char += 1;
	}
	if (strct->flag[FLAG_MINUS] == '-' && strct->width > 1)
		ft_print_width(strct, buffer, count);
	return (1);
}
