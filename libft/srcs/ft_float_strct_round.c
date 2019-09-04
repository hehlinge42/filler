/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_strct_round.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:19:06 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/11 19:37:31 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>

static int	ft_bank_round(t_float *float_nb, int precision, char c, int len)
{
	int		i;

	i = precision;
	if (c == '5' || float_nb->tab_res[2][precision] == '5')
	{
		while (float_nb->tab_res[2][++i] == '0')
			;
		if (float_nb->tab_res[2][i])
			return (0);
		if (!precision && ((float_nb->tab_res[1][len - 1] - '0') % 2) == 1)
			return (0);
		if (precision && ((float_nb->tab_res[2][precision - 1] - '0') % 2) == 1)
			return (0);
		if (precision)
		{
			float_nb->tab_res[2][precision] = '\0';
			return (1);
		}
		else
		{
			float_nb->tab_res[2][0] = '\0';
			return (1);
		}
	}
	return (0);
}

static void	ft_round_if_precision(t_float *float_nb, int precision, int len)
{
	char	c;

	c = float_nb->tab_res[2][0];
	ft_memset(float_nb->tab_res[0], '0', sizeof(char) * precision);
	float_nb->tab_res[0][precision] = '\0';
	float_nb->tab_res[0][precision - 1] = '1';
	ft_sum(float_nb->tab_res[0], float_nb->tab_res[2], precision);
	float_nb->tab_res[2][precision] = '\0';
	if (c != '0' && float_nb->tab_res[2][0] == '0')
	{
		float_nb->tab_res[0][len] = '\0';
		ft_memset(float_nb->tab_res[0], '0', sizeof(char) * len);
		float_nb->tab_res[0][len - 1] = '1';
		ft_sum(float_nb->tab_res[0], float_nb->tab_res[1], len);
		if (float_nb->tab_res[1][0] == '0')
		{
			ft_memmove(float_nb->tab_res[1] + 1, float_nb->tab_res[1], len);
			float_nb->tab_res[1][0] = '1';
			float_nb->tab_res[1][len + 1] = '\0';
		}
	}
}

static void	ft_round_if_not_precision(t_float *float_nb, int len)
{
	float_nb->tab_res[0][len] = '\0';
	ft_memset(float_nb->tab_res[0], '0', sizeof(char) * len);
	float_nb->tab_res[0][len - 1] = '1';
	ft_sum(float_nb->tab_res[0], float_nb->tab_res[1], len);
	ft_bzero(float_nb->tab_res[2], BUF_FLOAT);
	if (float_nb->tab_res[1][0] == '0')
	{
		ft_memmove(float_nb->tab_res[1] + 1, float_nb->tab_res[1], len);
		float_nb->tab_res[1][0] = '1';
		float_nb->tab_res[1][len + 1] = '\0';
	}
}

void		ft_round(t_float *float_nb, int precision)
{
	char	c;
	int		len;

	c = 0;
	len = ft_strlen(float_nb->tab_res[1]);
	if (!precision)
		c = float_nb->tab_res[2][0];
	if (float_nb->tab_res[2][precision] > '4' || c > '4')
	{
		if (ft_bank_round(float_nb, precision, c, len))
			return ;
		float_nb->tab_res[2][precision] = '\0';
		if (precision)
			ft_round_if_precision(float_nb, precision, len);
		else
			ft_round_if_not_precision(float_nb, len);
	}
	else
		float_nb->tab_res[2][precision] = '\0';
}
