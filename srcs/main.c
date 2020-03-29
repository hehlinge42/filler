/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:02:19 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/21 13:32:04 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/*
** Parameter: t_var *var
** Return: 1 in case of success, 0 in case of error
**
** This function reads the first line of the vm input and checks its content.
** It sets the values for player and enemy to X and O or vice versa.
*/

int			ft_parse_first_line(t_var *var)
{
	int		pos;
	char	*line;

	if (!(filler_gnl(0, &line)))
		return (0);
	pos = ft_strlen("$$$ exec p");
	if (ft_strncmp(line, "$$$ exec p", pos))
		return (0);
	if (line[pos] != '1' && line[pos] != '2')
		return (0);
	var->player = line[pos] == '1' ? 'O' : 'X';
	var->enemy = line[pos] == '1' ? 'X' : 'O';
	pos++;
	if (ft_strcmp(line + pos, " : [players/hehlinge.filler]"))
		return (0);
	return (1);
}

/*
** Parameters: int opt: indicates the nature of the error.
** Return: EXIT_FAILURE
**
** This function displays an error message depending on its parameter opt.
** Then, it frees the garbage collector.
*/

int			ft_exit(int opt)
{
	if (opt == ERR_FIRST_LINE)
		ft_printf("exit - bad first line\n");
	else if (opt == BAD_MAP)
		ft_printf("exit - bad map\n");
	ft_free_gc();
	return (EXIT_FAILURE);
}

/*
** The program contains a main loop, which represents a turn.
** At each turn, the program reads the input and executes its algorithm
** to find the optimal point to drop the piece it has received from the vm.
** When there is no spot to drop the piece, the program sets the coordinates to -1,
** frees the memory and exits.
*/

int			main(void)
{
	t_var		*var;
	t_point		*point;
	t_lst		*tmp;

	point = 0;
	tmp = 0;
	if (!(var = ft_init_filler()))
		return (ft_exit(ERR_FIRST_LINE));
	if (!ft_parse_first_line(var))
		return (EXIT_FAILURE);
	while (++var->turn > -1)
	{
		if (!ft_parse_input(var))
			return (ft_exit(BAD_MAP));
		ft_get_points(var, point, *(var->pts_neutral), tmp);
		ft_algo(var, -1, -1);
		ft_printf("%d %d\n", var->y_pos, var->x_pos);
		if (var->y_pos == -1 || var->x_pos == -1)
		{
			ft_free_gc();
			return (EXIT_SUCCESS);
		}
		var->x_pos = var->x_map + 1;
		var->y_pos = -1;
	}
	return (EXIT_FAILURE);
}
