/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:53:56 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 13:14:24 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <unistd.h>
#include <stdio.h>

void		ft_write_buf(char *str, t_buffer *buffer, unsigned long long size)
{
	unsigned long long	i;

	i = 0;
	while (str[i] && buffer->index < BUF_SIZE && i < size)
	{
		buffer->buf[buffer->index] = str[i];
		buffer->index += 1;
		i++;
	}
	if (i < size)
	{
		buffer->count_total_char += (buffer->index);
		buffer->index = 0;
		ft_putstr(buffer->buf);
		ft_bzero(buffer->buf, BUF_SIZE);
		ft_write_buf(str + i, buffer, size - i);
	}
}

static void	ft_init_tab(int (*tab[15])(t_printf *, t_buffer *, va_list))
{
	tab[CONVERT_C - 1] = ft_char;
	tab[CONVERT_D - 1] = ft_int;
	tab[CONVERT_U - 1] = ft_uint;
	tab[CONVERT_X - 1] = ft_uint;
	tab[CONVERT_XX - 1] = ft_uint;
	tab[CONVERT_O - 1] = ft_uint;
	tab[CONVERT_F - 1] = ft_float;
	tab[CONVERT_P - 1] = ft_pointer;
	tab[CONVERT_S - 1] = ft_string;
	tab[CONVERT_PE - 1] = ft_percent;
	tab[CONVERT_B - 1] = ft_bits;
	tab[CONVERT_FF - 1] = ft_float;
	tab[CONVERT_FAKE - 1] = ft_char;
	tab[CONVERT_BB - 1] = ft_uint;
}

static int	ft_printstr(char **str, t_buffer *buffer)
{
	unsigned long long	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '%')
		{
			ft_write_buf(*str, buffer, i);
			*str += (i + 1);
			if (!((*str)[0]))
				return (0);
			return (1);
		}
		i++;
	}
	ft_write_buf(*str, buffer, i);
	*str += (i + 1);
	return (0);
}

int			ft_printf(const char *format, ...)
{
	t_buffer	buffer;
	va_list		va;
	t_printf	var;
	char		*str;
	int			(*tab[15])(t_printf *, t_buffer *, va_list);

	ft_bzero(&buffer, sizeof(buffer));
	str = (char *)format;
	ft_init_tab(tab);
	va_start(va, format);
	while (ft_printstr(&str, &buffer))
	{
		ft_memset(&var, -1, sizeof(var));
		if (ft_parse(&str, &var))
			tab[var.convert - 1](&var, &buffer, va);
	}
	buffer.count_total_char += buffer.index;
	ft_putstr(buffer.buf);
	va_end(va);
	return (buffer.count_total_char);
}
