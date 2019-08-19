/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:38:31 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/19 18:14:59 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdio.h>

void	print_map(t_var var)
{
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
	int			i;
	t_lst		*tmp;

	i = 0;
	printf("ENEMY POINTS\n");
	tmp = var.player == 'X' ? *(var.points_o) : *(var.points_x);
	while (tmp)
	{
		printf("PT_ENEMY   %d -- y: %d, x: %d\n"
			, i++, ((t_point *)tmp->content)->y
			, ((t_point *)tmp->content)->x);
		tmp = tmp->next;
	}
	i = 0;
	printf("PLAYER POINTS\n");
	tmp = var.player == 'X' ? *(var.points_x) : *(var.points_o);
	while (tmp)
	{
		printf("PT_PLAYER  %d -- y: %d\tx: %d\t%s\n"
			, i++, ((t_point *)tmp->content)->y
			, ((t_point *)tmp->content)->x
			, ((t_point *)tmp->content)->available ? "-- available" : "");
		tmp = tmp->next;
	}
	i = 0;
	printf("NEUTRAL POINTS\n");
	tmp = *(var.points_n);
	while (tmp)
	{
		printf("PT_PLAYER  %d -- y: %d\tx: %d\t-- owner: %c%s\n"
			, i++, ((t_point *)tmp->content)->y
			, ((t_point *)tmp->content)->x
			, ((t_point *)tmp->content)->owner
			, ((t_point *)tmp->content)->available ? " -- available" : "");
		tmp = tmp->next;
	}
}

void	print_debug(t_var var, char *opt)
{
	printf("PLAYER: %c\nMAP:\n", var.player);
	if (!*opt || ft_strchr(opt, '1'))
	{
		print_map(var);
		print_piece(var);
	}
	if (!*opt || ft_strchr(opt, '2'))
		print_points(var);
}
