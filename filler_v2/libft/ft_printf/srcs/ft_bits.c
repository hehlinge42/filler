/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:04:42 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 13:05:47 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_return_b(ull *nb, t_printf *strct, va_list va, int *size)
{
	if (strct->length == -1)
	{
		*size = sizeof(unsigned int);
		*nb = (unsigned long long)va_arg(va, unsigned int);
	}
	else if (strct->length == LENGTH_H)
	{
		*size = sizeof(unsigned short);
		*nb = (unsigned long long)((unsigned short)va_arg(va, unsigned int));
	}
	else if (strct->length == LENGTH_HH)
	{
		*size = sizeof(unsigned char);
		*nb = (unsigned long long)((unsigned char)va_arg(va, unsigned int));
	}
	else if (strct->length == LENGTH_L)
	{
		*size = sizeof(unsigned long);
		*nb = (unsigned long long)((unsigned long)va_arg(va, unsigned long));
	}
	else if (strct->length == LENGTH_LL)
	{
		*size = sizeof(unsigned long long);
		*nb = va_arg(va, unsigned long long);
	}
}

static void	ft_print_bits(ull nb, int size, t_buffer *buf, t_printf *strct)
{
	unsigned long long	limit;
	int					power;
	int					i;

	power = 8 * size - 1;
	i = -1;
	limit = 1;
	while (++i < power)
		limit *= 2;
	i = -1;
	while (limit)
	{
		(nb / limit) ? ft_write_buf("1", buf, 1) : ft_write_buf("0", buf, 1);
		(nb / limit) ? nb -= limit : 0;
		limit /= 2;
		i++;
		if (limit && i % 8 == 7 && strct->flag[FLAG_SPACE] == ' ')
			ft_write_buf(" ", buf, 1);
	}
}

int			ft_bits(t_printf *strct, t_buffer *buffer, va_list va)
{
	unsigned long long	nb;
	int					size;

	ft_return_b(&nb, strct, va, &size);
	ft_print_bits(nb, size, buffer, strct);
	return (1);
}
