/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_anormal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:40:49 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/11 19:33:19 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_is_nan(t_float *float_nb)
{
	return (((float_nb->float_mantissa & 0xC000000000000000) == 0
		&& float_nb->float_mantissa)
		|| ((float_nb->float_mantissa & 0x4000000000000800)
		== 0x4000000000000800)
		|| ((float_nb->float_mantissa & 0x8000000000000000)
		== 0x8000000000000000
		&& (float_nb->float_mantissa & 0x4000000000000000))
		|| ((float_nb->float_mantissa & 0xC000000000000000)
		== 0xC000000000000000));
}

void		ft_anormal(t_float *float_nb)
{
	if ((float_nb->exponent & 0x7fff) == 0x7fff)
	{
		if (ft_is_nan(float_nb))
			float_nb->anormal = MY_NAN;
		else if ((float_nb->float_mantissa & 0xC000000000000000) == 0
				&& !(float_nb->float_mantissa))
		{
			if (float_nb->sign)
				float_nb->anormal = MINUS_INF;
			else
				float_nb->anormal = PLUS_INF;
		}
		else if ((float_nb->float_mantissa & 0x8000000000000000)
				== 0x8000000000000000
				&& !(float_nb->float_mantissa & 0x4000000000000000))
		{
			if (float_nb->sign)
				float_nb->anormal = MINUS_INF;
			else
				float_nb->anormal = PLUS_INF;
		}
	}
}

static void	ft_manage_plusinf(t_printf *strct, t_buffer *buffer, int count)
{
	if ((strct->flag[FLAG_PLUS] == '+' || strct->flag[FLAG_SPACE] == ' '))
		count++;
	if (strct->flag[FLAG_MINUS] == -1)
	{
		if (strct->flag[FLAG_ZERO] == '0' && (strct->flag[FLAG_PLUS] == '+'
					|| strct->flag[FLAG_SPACE] == ' '))
			ft_display_flag_plus(strct, buffer);
		ft_print_width(strct, buffer, count);
	}
	if (!(strct->flag[FLAG_MINUS] == -1
		&& strct->flag[FLAG_ZERO] == '0'
		&& (strct->flag[FLAG_PLUS] == '+' || strct->flag[FLAG_SPACE] == ' ')))
		ft_display_flag_plus(strct, buffer);
	if (strct->convert == CONVERT_F)
		ft_write_buf("inf", buffer, 3);
	else if (strct->convert == CONVERT_FF)
		ft_write_buf("INF", buffer, 3);
	if (strct->flag[FLAG_MINUS] != -1)
		ft_print_width(strct, buffer, count);
}

static void	ft_manage_nan(t_printf *strct, t_buffer *buffer)
{
	if (strct->flag[FLAG_MINUS] == -1)
		ft_print_width(strct, buffer, 3);
	if (strct->convert == CONVERT_F)
		ft_write_buf("nan", buffer, 3);
	else if (strct->convert == CONVERT_FF)
		ft_write_buf("NAN", buffer, 3);
	if (strct->flag[FLAG_MINUS] != -1)
		ft_print_width(strct, buffer, 3);
}

int			ft_manage_anormal(t_float *float_nb, t_printf *strct,
	t_buffer *buffer)
{
	int		count;

	count = 3;
	strct->flag[FLAG_ZERO] = -1;
	if (float_nb->anormal == MY_NAN)
		ft_manage_nan(strct, buffer);
	else if (float_nb->anormal == PLUS_INF)
		ft_manage_plusinf(strct, buffer, count);
	else if (float_nb->anormal == MINUS_INF)
	{
		count++;
		if (strct->flag[FLAG_MINUS] == -1)
			ft_print_width(strct, buffer, count);
		if (strct->convert == CONVERT_F)
			ft_write_buf("-inf", buffer, 4);
		else if (strct->convert == CONVERT_FF)
			ft_write_buf("-INF", buffer, 4);
		if (strct->flag[FLAG_MINUS] != -1)
			ft_print_width(strct, buffer, count);
	}
	return (1);
}
