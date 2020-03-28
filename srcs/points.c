/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:44:03 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/08 17:18:17 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Parameters: int o_y = point->y (ordinate); int o_x = point->x (absissa)
** Return: 1 if the point is a valid spot to drop the piece. 0 otherwise
**
** First, is_available makes sure that the piece fits in the map if dropped
** at these coordinates.
** Then, it makes sure that none of the points in the area of the piece size
** belongs to the opponent. It also makes sure that one and only one point of
** the area belongs to the player.
*/

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

/*
** Parameter: t_point *pivot: a point that was neutral until last turn and that
** was used by either the player or the opponent during the last turn
**
** ft_test_dist iterates on every neutral point.
** It checks if this point is now closer to the pivot point than the previously
** closest non-neutral point. If so, it upgrades its owner and distance.
*/

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

/*
** Parameters:
** - t_point *point: pointer on the content of each successive point of
**   the list of neutral points
** - t_lst *elem: each successive neutral point
** - t_lst *tmp
**
** ft_get_points iterates on every neutral point.
** It calls is_available to know if the point is a valid spot to drop the piece
** If the point is not neutral anymore (earned in the last turn), it is popped
** from the neutral points and added to the player points if coherent. Then,
** it calls ft_test_dist.
** Finally, ft_get_points iterates on every player's point and calls is_available
** to determine if they are valid spots to drop the piece
*/

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
}
