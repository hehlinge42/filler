/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:44:03 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/02 16:28:15 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_point		*ft_new_point(int x, int y, char c)
{
	t_point		*new;

	if ((new = (t_point *)easymalloc(sizeof(*new))))
	{
		ft_memset(new, 0, sizeof(*new));
		new->x = x;
		new->y = y;
		new->owner = c;
		new->x_owner = 0;
		new->y_owner = 0;
		new->dist = 0;
		return (new);
	}
	return (0);
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
		&& var->map[y][x] != '.' && (test = abs(point->x - x)
			+ abs(point->y - y)) <= *dist && var->map[y][x] == var->enemy)
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
		if ((test = abs(point->x - pivot->x) + abs(point->y - pivot->y))
			< point->dist)
		{
			point->owner = pivot->owner;
			point->dist = test;
			point->x_owner = pivot->x;
			point->y_owner = pivot->y;
		}
		else if (test == point->dist && point->owner != pivot->owner)
			point->owner = '?';
		elem = elem->next;
	}
}

void		ft_get_points(t_var *var, t_point *point, t_lst *elem, t_lst *tmp)
{
	while (elem && (point = (t_point *)elem->content))
	{
		point->available = is_available(*var, point->x, point->y);
		if (var->map[point->y][point->x] != '.')
		{
			point->owner = var->map[point->y][point->x];
			point->owner == var->enemy ? var->enemy_is_playing = 1 : 0;
			tmp = elem;
			elem = elem->next;
			ft_lstpop(var->pts_neutral, (void **)tmp, 0);
			if (point->owner == var->player)
				ft_lstadd(var->pts_player, tmp);
			ft_test_dist(var, point);
		}
		else
			elem = elem->next;
	}
	elem = *var->pts_player;
	while (elem && (point = (t_point *)elem->content))
	{
		point->available = is_available(*var, point->x, point->y);
		elem = elem->next;
	}
}
