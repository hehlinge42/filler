/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:41:07 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 13:12:06 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int	ft_valid(char c)
{
	char	tab[18];
	int		i;

	tab[0] = 'd';
	tab[1] = 'i';
	tab[2] = 'u';
	tab[3] = 'f';
	tab[4] = 'x';
	tab[5] = 'X';
	tab[6] = 'o';
	tab[7] = 's';
	tab[8] = 'c';
	tab[9] = 'p';
	tab[10] = '%';
	tab[11] = 'U';
	tab[12] = 'D';
	tab[13] = 'O';
	tab[14] = 'b';
	tab[15] = 'F';
	tab[16] = 'B';
	tab[17] = '\0';
	i = -1;
	while (tab[++i])
		if (c == tab[i])
			return (1);
	return (0);
}

static int	ft_undefined_behavior(char c)
{
	char	tab[6];
	int		i;

	tab[0] = '-';
	tab[1] = '+';
	tab[2] = '0';
	tab[3] = ' ';
	tab[4] = '#';
	tab[5] = '\0';
	i = -1;
	while (tab[++i])
		if (c == tab[i])
			return (1);
	return (0);
}

static int	ft_is_convert_type_optional(t_printf *var, char c)
{
	if (c == 'F' && var->convert == -1)
		var->convert = CONVERT_FF;
	else if (c == 'p' && var->convert == -1)
		var->convert = CONVERT_P;
	else if (c == '%' && var->convert == -1)
		var->convert = CONVERT_PE;
	else if (c == 'b' && var->convert == -1)
		var->convert = CONVERT_B;
	else if (c == 'B' && var->convert == -1)
		var->convert = CONVERT_BB;
	else if (c == 'U' && var->convert == -1)
	{
		var->convert = CONVERT_U;
		var->length = LENGTH_L;
	}
	else if (c == 'O' && var->convert == -1)
	{
		var->convert = CONVERT_O;
		var->length = LENGTH_L;
	}
	else if (c == 'D' && var->convert == -1)
	{
		var->convert = CONVERT_D;
		var->length = LENGTH_L;
	}
	return (0);
}

int			ft_is_convert_type(t_printf *var, char *c)
{
	if (ft_valid(*c))
	{
		if ((*c == 'd' || *c == 'i') && var->convert == -1)
			var->convert = CONVERT_D;
		else if (*c == 'u' && var->convert == -1)
			var->convert = CONVERT_U;
		else if (*c == 'f' && var->convert == -1)
			var->convert = CONVERT_F;
		else if (*c == 'x' && var->convert == -1)
			var->convert = CONVERT_X;
		else if (*c == 'X' && var->convert == -1)
			var->convert = CONVERT_XX;
		else if (*c == 'o' && var->convert == -1)
			var->convert = CONVERT_O;
		else if (*c == 's' && var->convert == -1)
			var->convert = CONVERT_S;
		else if (*c == 'c' && var->convert == -1)
			var->convert = CONVERT_C;
		else
			return (ft_is_convert_type_optional(var, *c));
		return (0);
	}
	else if (ft_undefined_behavior(*c))
		return (1);
	return (2);
}
