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
	if (opt == ERR_FIRS_LINE)
		ft_putendl("Incorrect firstline");
	else if (opt == BAD_MAP)
		ft_putendl("Bad map");
	else if (opt == FULL_MAP)
		ft_display(0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_var	var;

	ft_memset(&var, 0, sizeof(var));
	if (!argc || !argv)
		return (0);
	if (!ft_parse_first_line(&var))
		return (ft_exit(&var, ERR_FIRST_LINE));
	while (1)
	{
		if (!ft_parse_input(&var))
			return (ft_exit(&var, BAD_MAP));
		if (!place_piece)
			return (ft_exit(&var, FULL_MAP);
		ft_display(var.x, var.y);
	}
	return (0);
}
