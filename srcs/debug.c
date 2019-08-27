/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:38:31 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/21 19:44:49 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdio.h>

void	print_lines(t_var var, char *line, int opt, int nocolor)
{
	int			i;
	int			pos;
	char		*code;
	t_lst		*tmp;
	t_point		*point;

	i = 0;
	while (i < var.y_map)
	{
		dprintf(var.fd, "%d\t", i);
		if (opt)
			line = var.tmp[i];
		else
			line = var.map[i];
		tmp = *(var.pts_neutral);
		while (tmp)
		{
			point = tmp->content;
			if (point->owner == var.enemy)
				var.map[point->y][point->x] = ',';
			else if (point->owner == '?')
				var.map[point->y][point->x] = '?';
			tmp = tmp->next;
		}
		pos = 0;
		while (line[pos])
		{
			code = "\033[0m";
			(line[pos] == var.player || line[pos] == var.player + 32)
			 	? (code = "\033[1;31m") : 0;
			(line[pos] == var.enemy || line[pos] == var.enemy + 32)
				? (code = "\033[1;34m") : 0;
			line[pos] == ',' ? (code = "\033[0;34m") : 0;
			line[pos] == '.' ? (code = "\033[0;31m") : 0;
			if (nocolor)
				dprintf(var.fd, "%c", line[pos]);
			else
				dprintf(var.fd, "%s%c\033[0m", code, line[pos]);
			pos++;
		}
		dprintf(var.fd, "\n");
		i++;
	}
}

void	print_map(t_var var, int opt, int nocolor)
{
	int			i;

	i = -1;
	dprintf(var.fd, "MAP -- x: %d, y: %d\n", var.x_map, var.y_map);
	dprintf(var.fd, "\t");
	while (++i < var.x_map)
		dprintf(var.fd, "%c", i % 10 + 48);
	dprintf(var.fd, "\n");
	print_lines(var, "", opt, nocolor);
	dprintf(var.fd, "\n");
}

void	print_piece(t_var var)
{
	int			i;

	i = -1;
	dprintf(var.fd, "PIECE -- x: %d, y: %d\n", var.x_piece, var.y_piece);
	dprintf(var.fd, "\t");
	while (++i < var.x_piece)
		dprintf(var.fd, "%c", i % 10 + 48);
	dprintf(var.fd, "\n");
	i = -1;
	while (++i < var.y_piece)
		dprintf(var.fd, "%d\t%s\n", i, var.piece[i]);
	dprintf(var.fd, "\n");
}

void	print_point(t_point *point, int fd)
{
	char	*available;

	available = "";
	available = point->available ? " -- available: YES" : " -- available:  NO";
	dprintf(fd, "POINT %d-%d : address:  %p, owner: %c (%d-%d), dist: %d%s\n"
		, point->y, point->x, point
		, point->owner, point->y_owner, point->x_owner, point->dist
		, available);
}

void	print_points(t_var var)
{
	t_lst		*tmp;
	int			i;

	i = 0;
	dprintf(var.fd, "PLAYER POINTS\n");
	tmp = *(var.pts_player);
	while (tmp)
	{
		print_point(tmp->content, var.fd);
		tmp = tmp->next;
	}
	i = 0;
	dprintf(var.fd, "NEUTRAL POINTS\n");
	tmp = *(var.pts_neutral);
	while (tmp)
	{
		print_point(tmp->content, var.fd);
		tmp = tmp->next;
	}
}

void	print_debug(t_var var, char *opt)
{
	dprintf(var.fd, "PLAYER: %c\nMAP:\n", var.player);
	if (!*opt || ft_strchr(opt, '1'))
	{
		if (ft_strchr(opt, '3'))
			print_map(var, 1, 0);
		else if (ft_strchr(opt, '4'))
			print_map(var, 0, 1);
		else
			print_map(var, 0, 0);
		print_piece(var);
	}
	if (!*opt || ft_strchr(opt, '2'))
		print_points(var);
}
