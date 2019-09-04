/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:31:06 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 13:12:18 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>

static void	ft_parse_flag(char **str, t_printf *var)
{
	while (*str[0] == '+'
			|| *str[0] == '-'
			|| *str[0] == '0'
			|| *str[0] == '#'
			|| *str[0] == ' ')
	{
		if (*str[0] == '+' && var->flag[FLAG_PLUS] == -1)
			var->flag[FLAG_PLUS] = '+';
		else if (*str[0] == '-' && var->flag[FLAG_MINUS] == -1)
			var->flag[FLAG_MINUS] = '-';
		else if (*str[0] == ' ' && var->flag[FLAG_SPACE] == -1)
			var->flag[FLAG_SPACE] = ' ';
		else if (*str[0] == '0' && var->flag[FLAG_ZERO] == -1)
			var->flag[FLAG_ZERO] = '0';
		else if (*str[0] == '#' && var->flag[FLAG_HASH] == -1)
			var->flag[FLAG_HASH] = '#';
		*str += 1;
	}
}

static void	ft_parse_width(char **str, t_printf *var)
{
	int		marker;

	marker = 0;
	if (*str[0] >= '0' && *str[0] <= '9')
	{
		marker = 1;
		var->width = 0;
	}
	while (*str[0] >= '0' && *str[0] <= '9')
	{
		var->width = var->width * 10 - '0' + (*str[0]);
		*str += 1;
	}
	if (marker && var->width < 0)
		var->width = -1;
}

static int	ft_parse_precision(char **str, t_printf *var)
{
	if (*str[0] == '.')
	{
		while (*str[0] == '.')
			*str += 1;
		var->precision = 0;
		while (*str[0] >= '0' && *str[0] <= '9')
		{
			var->precision = var->precision * 10 + *str[0] - '0';
			*str += 1;
		}
		if (var->precision < 0)
			var->precision = -1;
		return (1);
	}
	return (0);
}

static int	ft_parse_length(char **s, t_printf *var)
{
	if (*s[0] == 'z' || (*s[0] == 'h' && *(*s + 1) != 'h') || (*s[0] == 'l'
		&& *(*s + 1) != 'l') || *s[0] == 'L' || *s[0] == 'j')
	{
		if (*s[0] == 'h' && var->length < LENGTH_H)
			var->length = LENGTH_H;
		else if (*s[0] == 'l' && var->length < LENGTH_L)
			var->length = LENGTH_L;
		else if (*s[0] == 'L' && var->length < LENGTH_BIGL)
			var->length = LENGTH_BIGL;
		else if ((*s[0] == 'j' || *s[0] == 'z') && var->length < LENGTH_LL)
			var->length = LENGTH_LL;
		*s += 1;
		return (1);
	}
	else if ((*s[0] == 'h' && *(*s + 1) == 'h')
		|| (*s[0] == 'l' && *(*s + 1) == 'l'))
	{
		if (*s[0] == 'h' && var->length < LENGTH_HH)
			var->length = LENGTH_HH;
		else if (*s[0] == 'l' && var->length < LENGTH_LL)
			var->length = LENGTH_LL;
		*s += 2;
		return (1);
	}
	return (0);
}

int			ft_parse(char **str, t_printf *var)
{
	int		loop;

	loop = 1;
	while (loop == 1)
	{
		ft_parse_flag(str, var);
		while (**str == ' ')
			*str += 1;
		ft_parse_width(str, var);
		while (ft_parse_precision(str, var))
			;
		while (ft_parse_length(str, var))
			;
		if ((loop = ft_is_convert_type(var, *str)) == 0)
			*str += 1;
		if (loop == 2)
		{
			var->convert = CONVERT_FAKE;
			var->fake_c = **str;
			if (var->fake_c)
				*str += 1;
		}
	}
	return (1);
}
