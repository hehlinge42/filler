/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:38:31 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/02 16:20:04 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdio.h>

void	print_map(t_var var)
{
	PRINTENV
	int			i;

	i = -1;
	printf("MAP -- x: %d, y: %d\n", var.x_map, var.y_map);
	printf("\t");
	while (++i < var.x_map)
		printf("%c", i % 10 + 48);
	printf("\n");
	i = -1;
	while (++i < var.y_map)
		printf("%d\t%s\n", i, var.map[i]);
	printf("\n");
}

void	print_piece(t_var var)
{
	int			i;

	i = -1;
	printf("PIECE -- x: %d, y: %d\n", var.x_piece, var.y_piece);
	printf("\t");
	while (++i < var.x_piece)
		printf("%c", i % 10 + 48);
	printf("\n");
	i = -1;
	while (++i < var.y_piece)
		printf("%d\t%s\n", i, var.piece[i]);
	printf("\n");
}

void	print_points(t_var var)
{
	int		i;

	i = 0;
	printf("POINTS DE X\n");
	while (*(var.points_x))
	{
		printf("PT_X %d -- y: %d, x: %d\n"
			, i++, ((t_point *)(*var.points_x)->content)->y
			, ((t_point *)(*var.points_x)->content)->x);
		*(var.points_x) = (*(var.points_x))->next;
	}
	i = 0;
	printf("POINTS DE O\n");
	while (*(var.points_o))
	{
		printf("PT_O %d -- y: %d, x: %d\n"
			, i++, ((t_point *)(*var.points_o)->content)->y
			, ((t_point *)(*var.points_o)->content)->x);
		*(var.points_o) = (*(var.points_o))->next;
	}
}

void	print_debug(t_var var, char *opt)
{
	printf("in debug, address of map: %p, *map: %p\n", var.map, *var.map);
	if (!*opt || ft_strchr(opt, '1'))
		print_map(var);
	if (!*opt || ft_strchr(opt, '2'))
		print_piece(var);
	if (!*opt || ft_strchr(opt, '3'))
		print_points(var);
}
