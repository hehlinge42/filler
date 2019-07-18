/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:28:16 by hehlinge          #+#    #+#             */
/*   Updated: 2019/07/11 19:08:51 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_parse_first_line(t_var *var)
{
	char	*str;
	char	*tmp;

	str = 0;
	if (gnl(1, &str, 0) <= 0)
		return (0);
	tmp = str;
	if (ft_strncmp(tmp, "$$$ exec p", ft_strlen("$$$ exec p")))
		return (0);
	tmp += ft_strlen("$$$ exec p");
	if (!((var->player = tmp[0]) == '1' || tmp[0] == '2'))
		return (0);
	tmp++;
	if (ft_strncmp(tmp, " : [players/", ft_strlen(" : [players/")))
		return (0);
	tmp += ft_strlen(" : [players/");
	if (ft_strcmp(tmp, "hehlinge.filler]"))
		return (0);
	if (str)
		free(str);
	return (1);
}

void	ft_display(int x, int y)
{
	ft_putnbr(x);
	write(1, " ", 1);
	ft_putnbr(y);
	write(1, "\n", 1);
}

int		ft_exit(t_var *var, int opt)
{
	int		y;

	y = -1;
	while (++y < var->y_max)
	{
		if (var->map[y])
			free(var->map[y]);
		if (var->piece[y])
			free(var->piece[y]);
	}
	if (opt == ERR_FIRST_LINE)
		ft_putendl("Incorrect firstline");
	else if (opt == BAD_MAP)
		ft_putendl("Bad map");
	else if (opt == FULL_MAP)
		ft_display(0, 0);
	return (1);
}

int		main(void)
{
	t_var	var;

	ft_memset(&var, 0, sizeof(var));
	if (!ft_parse_first_line(&var))
		return (ft_exit(&var, ERR_FIRST_LINE));
	ft_putendl("ft_parse_first_line ok");
	while (1)
	{
		if (!ft_parse_input(&var))
			return (ft_exit(&var, BAD_MAP));
		ft_print_debug(&var);
		return (1);
		if (!place_piece())
			return (ft_exit(&var, FULL_MAP));
		ft_display(var.x, var.y);
	}
	return (0);
}
