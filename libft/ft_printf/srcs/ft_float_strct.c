/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_strct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:52:06 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 11:21:16 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_float_part(t_float *float_nb)
{
	int					i;
	unsigned long long	mask;

	if (float_nb->exponent < 0)
		float_nb->shift_float = -(float_nb->exponent);
	float_nb->float_size = ft_float_size(float_nb->float_mantissa);
	mask = (unsigned long long)1
		<< ((unsigned long long)(float_nb->float_size - 1));
	ft_memset(float_nb->tab_res[0], '0', sizeof(float_nb->tab_res[0]));
	float_nb->tab_res[0][BUF_FLOAT] = '\0';
	float_nb->tab_res[0][BUF_FLOAT - 1 - float_nb->float_size
		- float_nb->shift_float] = '1';
	i = 0;
	while (++i <= (float_nb->float_size + float_nb->shift_float))
	{
		ft_divide_nb(float_nb->tab_res[0]);
		if (float_nb->float_mantissa & mask && i > float_nb->shift_float)
			ft_sum(float_nb->tab_res[0], float_nb->tab_res[2], 0);
		if (i > float_nb->shift_float)
			mask >>= 1;
	}
}

static void	ft_floor_part(t_float *float_nb)
{
	unsigned long long	mask;
	int					i;

	mask = (unsigned long long)1;
	i = 1;
	float_nb->tab_res[0][BUF_FLOAT - 1] = '1';
	if ((float_nb->floor_mantissa & mask) && (i > float_nb->shift))
		ft_sum(float_nb->tab_res[0], float_nb->tab_res[1], 0);
	if (i >= float_nb->shift)
		mask <<= 1;
	while (i <= float_nb->exponent)
	{
		ft_double_nb(float_nb->tab_res[0]);
		if ((float_nb->floor_mantissa & mask) && (i >= float_nb->shift))
			ft_sum(float_nb->tab_res[0], float_nb->tab_res[1], 0);
		if (i >= float_nb->shift)
			mask <<= 1;
		i++;
	}
}

static void	ft_split_mantissa(t_float *float_nb)
{
	int					size;
	unsigned long long	mask;
	int					exponent_cpy;

	size = 64;
	mask = (unsigned long long)1 << (unsigned long long)size;
	exponent_cpy = float_nb->exponent + 1;
	while (--exponent_cpy >= float_nb->shift)
		mask |= ((unsigned long long)1 << (unsigned long long)size--);
	float_nb->floor_mantissa = (mask & float_nb->float_mantissa)
		>> (64 - float_nb->exponent + float_nb->shift);
	float_nb->float_mantissa |= mask;
	float_nb->float_mantissa ^= mask;
	mask = (unsigned long long)1 << (unsigned long long)63;
	float_nb->shift_float = 0;
	while ((mask & float_nb->float_mantissa) == 0 && float_nb->float_mantissa)
	{
		float_nb->shift_float += 1;
		mask >>= 1;
	}
	if (float_nb->shift_float)
		float_nb->shift_float -= float_nb->exponent;
	while (!(float_nb->float_mantissa & 1) && float_nb->float_mantissa)
		float_nb->float_mantissa >>= 1;
}

static void	ft_init_float_strct(t_float *float_nb, t_printf *strct, va_list va)
{
	if (strct->precision == -1)
		strct->precision = 6;
	float_nb->nb = ft_return_ld(strct, va);
	float_nb->sign = 0;
	float_nb->float_mantissa = (unsigned long long)0;
	float_nb->floor_mantissa = (unsigned long long)0;
	float_nb->shift = 0;
	float_nb->shift_float = 0;
	float_nb->float_size = 0;
	float_nb->anormal = 0;
	ft_memset(float_nb->tab_res, '0', sizeof(float_nb->tab_res));
	float_nb->tab_res[0][BUF_FLOAT] = '\0';
	float_nb->tab_res[1][BUF_FLOAT] = '\0';
	float_nb->tab_res[2][BUF_FLOAT] = '\0';
}

void		ft_fill_float_strct(t_float *float_nb, t_printf *strct, va_list va)
{
	unsigned long long *ptr;

	ft_init_float_strct(float_nb, strct, va);
	ptr = (unsigned long long*)&(float_nb->nb);
	float_nb->sign = ptr[1] & ((unsigned long long)1 << (unsigned long long)15);
	float_nb->sign >>= 15;
	float_nb->exponent = ptr[1] & 0x7FFF;
	float_nb->float_mantissa = ptr[0];
	float_nb->anormal = 0;
	ft_anormal(float_nb);
	if (!float_nb->anormal)
	{
		float_nb->exponent -= 16382;
		if (float_nb->exponent > 64)
			float_nb->shift = float_nb->exponent - 64;
		ft_split_mantissa(float_nb);
		ft_floor_part(float_nb);
		if (float_nb->float_mantissa)
			ft_float_part(float_nb);
		ft_memmove_float(float_nb->tab_res[1], 0, 0);
		ft_memmove_float(float_nb->tab_res[2],
			float_nb->float_size, float_nb->shift_float);
		if ((float_nb->float_size + float_nb->shift_float) > strct->precision)
			ft_round(float_nb, strct->precision);
	}
}
