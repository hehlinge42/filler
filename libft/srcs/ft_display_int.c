/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:29:26 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 13:09:39 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_display_hash(t_printf *strct, t_buffer *buffer)
{
	if (strct->flag[FLAG_HASH] == '#')
	{
		if (strct->convert == CONVERT_O)
			ft_write_buf("0", buffer, 1);
		else if (strct->convert == CONVERT_X || strct->convert == CONVERT_P)
			ft_write_buf("0x", buffer, 2);
		else if (strct->convert == CONVERT_XX)
			ft_write_buf("0X", buffer, 2);
		else if ((strct->convert == CONVERT_F || strct->convert == CONVERT_FF)
				&& strct->precision == 0)
			ft_write_buf(".", buffer, 1);
	}
}

void	ft_display_flag_plus(t_printf *strct, t_buffer *buffer)
{
	if (strct->flag[FLAG_PLUS] == '+')
		ft_write_buf("+", buffer, 1);
	else if (strct->flag[FLAG_SPACE] == ' ' && strct->flag[FLAG_PLUS] != '+')
		ft_write_buf(" ", buffer, 1);
}

void	ft_display_precision(t_printf *strct, int count,
	t_buffer *buffer, long long nb)
{
	int		i;
	char	c;

	i = -1;
	c = '0';
	if (nb < 0)
		i--;
	if (strct->precision != -1)
		while (++i < strct->precision - count)
			ft_write_buf(&c, buffer, 1);
}

void	ft_print_width(t_printf *strct, t_buffer *buffer, int count)
{
	int		i;
	char	c;

	i = -1;
	if ((strct->convert == CONVERT_F && strct->flag[FLAG_ZERO] == '0')
		|| (strct->flag[FLAG_ZERO] == '0' && strct->precision == -1
		&& strct->flag[FLAG_MINUS] == -1)
		|| (strct->flag[FLAG_ZERO] == '0' && strct->flag[FLAG_MINUS] == -1
		&& (strct->convert == CONVERT_C || strct->convert == CONVERT_PE
		|| strct->convert == CONVERT_S))
		|| (strct->convert == CONVERT_P && strct->flag[FLAG_ZERO] == '0'
		&& strct->flag[FLAG_MINUS] == -1))
		c = '0';
	else
		c = ' ';
	while (++i < strct->width - count)
		ft_write_buf(&c, buffer, 1);
}

void	ft_putnbr_ullbase(ull u_nb, int base_size, char letter_case,
	t_buffer *buffer)
{
	char	c;

	if (u_nb < (unsigned long long)base_size)
	{
		if (u_nb < 10)
			c = u_nb + '0';
		else
			c = letter_case + u_nb - 10;
		ft_write_buf(&c, buffer, 1);
	}
	else if (u_nb >= (unsigned long long)base_size)
	{
		ft_putnbr_ullbase(u_nb / base_size, base_size, letter_case, buffer);
		ft_putnbr_ullbase(u_nb % base_size, base_size, letter_case, buffer);
	}
}
