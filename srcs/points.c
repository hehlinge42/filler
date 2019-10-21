/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:44:03 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/08 17:18:17 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			is_available(t_var var, int o_y, int o_x)
{
	int		count;
	int		x;
	int		y;

	count = (o_y + var.y_piece > var.y_map || o_x + var.x_piece > var.x_map)
		? 2 : 0;
	y = -1;
	while (count < 2 && ++y < var.y_piece && y + o_y < var.y_map)
	{
		x = -1;
		while (count < 2 && ++x < var.x_piece && x + o_x < var.x_map)
		{
			if (var.map[o_y + y][o_x + x] == var.enemy
				&& var.piece[y][x] == '*')
				count = 2;
			else if (var.piece[y][x] == '*'
				&& (var.map[o_y + y][o_x + x] == var.player
					|| var.map[o_y + y][o_x + x] == var.player + 32))
				count++;
		}
	}
	return (count == 1 ? 1 : 0);
}

void		ft_dist(t_point *point, t_point *point_b, t_var *var, int *dist)
{
	int		test;
	int		x;
	int		y;

	x = point->x;
	y = point->y;
	point = point_b;
	if (x >= 0 && y >= 0 && x < var->x_map && y < var->y_map
		&& var->map[y][x] != '.' && (test = ft_abs(point->x - x)
			+ ft_abs(point->y - y)) <= *dist && var->map[y][x] == var->enemy)
		*dist = test;
}

int			ft_get_dist_enemy(t_point *point, t_var *var, int square_nb)
{
	int			dist;
	t_point		tmp;

	dist = (var->x_map >= var->y_map) ? var->x_map : var->y_map;
	while (dist >= ++square_nb)
	{
		tmp.y = point->y - square_nb - 1;
		tmp.x = point->x - square_nb - 1;
		while (++(tmp.y) <= point->y + square_nb)
		{
			if ((tmp.y == point->y - square_nb || tmp.y == point->y + square_nb)
				&& (tmp.x = point->x - square_nb - 1) > -1)
				while (++(tmp.x) <= point->x + square_nb)
					ft_dist(&tmp, point, var, &dist);
			else
			{
				tmp.x = point->x - square_nb;
				ft_dist(&tmp, point, var, &dist);
				tmp.x = point->x + square_nb;
				ft_dist(&tmp, point, var, &dist);
			}
		}
	}
	return (dist);
}

void		ft_test_dist(t_var *var, t_point *pivot)
{
	t_lst	*elem;
	t_point	*point;
	int		test;

	elem = *var->pts_neutral;
	while (elem)
	{
		point = (t_point *)elem->content;
		if ((test = ft_abs(point->x - pivot->x) + ft_abs(point->y - pivot->y))
			< point->dist)
		{
			point->owner = pivot->owner;
			point->dist = test;
			point->x_owner = pivot->x;
			point->y_owner = pivot->y;
		}
		else if (test == point->dist && point->owner != pivot->owner)
		{
			point->owner = '?';
		}
		elem = elem->next;
	}
}

void		ft_get_points(t_var *var, t_point *point, t_lst *elem, t_lst *tmp)
{
	while (elem && (point = (t_point *)elem->content))
	{
		point->available = is_available(*var, point->y, point->x);
		if (var->map[point->y][point->x] != '.')
		{
			point->owner = var->map[point->y][point->x];
			point->owner == var->enemy ? var->enemy_is_playing = 1 : 0;
			tmp = ft_lstpop(var->pts_neutral, elem);
			elem = elem->next;
			if (tmp && point->owner == var->player)
				ft_lstadd(var->pts_player, tmp);
			ft_test_dist(var, point);
			var->map[point->y][point->x] == var->player ? (point->dist = 0) : 0;
		}
		else
			elem = elem->next;
	}
	elem = *var->pts_player;
	while (elem && (point = (t_point *)elem->content))
	{
		point->available = is_available(*var, point->y, point->x);
		elem = elem->next;
	}
	ft_algo(var, -1, -1);
}
