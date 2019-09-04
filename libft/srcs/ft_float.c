/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:38:40 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 11:10:06 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		ft_memmove_float(char nb[BUF_FLOAT + 1], int float_size, int shift)
{
	int	i;
	int	len;
	int	nb_zeros;

	i = -1;
	while (nb[++i] == '0' && i < BUF_FLOAT - 1)
		;
	len = BUF_FLOAT - i;
	if (len && float_size && shift)
		nb_zeros = float_size + shift - len;
	else
		nb_zeros = 0;
	i -= nb_zeros;
	ft_memmove(nb, nb + i, BUF_FLOAT - i);
	nb[BUF_FLOAT - i] = '\0';
}

long double	ft_return_ld(t_printf *strct, va_list va)
{
	if (strct->length == -1 || strct->length == LENGTH_L)
		return (long double)(va_arg(va, double));
	else if (strct->length == LENGTH_BIGL)
		return (va_arg(va, long double));
	return (-1);
}

static int	ft_count_chars_float(t_printf *strct, t_float *float_nb,
	int *len_floor, int *len_float)
{
	int		count_char;

	*len_floor = ft_strlen(float_nb->tab_res[1]);
	*len_float = ft_strlen(float_nb->tab_res[2]);
	count_char = float_nb->sign + *len_floor + *len_float + 1;
	if (!(strct->precision) && strct->flag[FLAG_HASH] == -1)
		count_char--;
	if (strct->precision > *len_float)
		count_char += strct->precision - *len_float;
	if (float_nb->sign == 0 && (strct->flag[FLAG_PLUS] == '+'
		|| strct->flag[FLAG_SPACE] == ' '))
		count_char++;
	return (count_char);
}

static void	ft_display_flags_float(t_printf *strct, t_float *float_nb,
	t_buffer *buffer, int count_char)
{
	if (strct->flag[FLAG_MINUS] == -1)
	{
		if (float_nb->sign == 0 && strct->flag[FLAG_ZERO] == '0'
			&& strct->precision == -1
			&& (strct->flag[FLAG_PLUS] == '+'
			|| strct->flag[FLAG_SPACE] == ' '))
			ft_display_flag_plus(strct, buffer);
		if (float_nb->sign && (strct->flag[FLAG_ZERO] == '0'
			|| strct->width < count_char))
			ft_write_buf("-", buffer, 1);
		ft_print_width(strct, buffer, count_char);
	}
	if (float_nb->sign == 0 && !(strct->flag[FLAG_MINUS] == -1
		&& strct->flag[FLAG_ZERO] == '0' && strct->precision == -1
		&& (strct->flag[FLAG_PLUS] == '+' || strct->flag[FLAG_SPACE] == ' ')))
		ft_display_flag_plus(strct, buffer);
}

int			ft_float(t_printf *strct, t_buffer *buffer, va_list va)
{
	t_float			float_nb;
	int				count_char;
	int				len_floor;
	int				len_float;

	ft_fill_float_strct(&float_nb, strct, va);
	if (float_nb.anormal)
		return (ft_manage_anormal(&float_nb, strct, buffer));
	count_char = ft_count_chars_float(strct, &float_nb, &len_floor, &len_float);
	ft_display_flags_float(strct, &float_nb, buffer, count_char);
	if (float_nb.sign && !(strct->flag[FLAG_MINUS] == -1
		&& (strct->flag[FLAG_ZERO] == '0' || strct->width < count_char)))
		ft_write_buf("-", buffer, 1);
	ft_write_buf(float_nb.tab_res[1], buffer, len_floor);
	ft_display_hash(strct, buffer);
	if (strct->precision)
	{
		ft_write_buf(".", buffer, 1);
		ft_write_buf(float_nb.tab_res[2], buffer, len_float);
	}
	if (strct->precision > len_float)
		ft_display_precision(strct, len_float, buffer, 0);
	if (strct->flag[FLAG_MINUS] != -1)
		ft_print_width(strct, buffer, count_char);
	return (1);
}
