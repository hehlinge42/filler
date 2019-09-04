/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:16:19 by hehlinge          #+#    #+#             */
/*   Updated: 2019/09/04 17:34:50 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <limits.h>

int		abs(int nb)
{
	return (nb < 0 ? -nb : nb);
}

int		ft_place_piece(t_var *var, t_point *point)
{
	int		i;
	int		j;

	i = -1;
	while (++i < var->y_piece)
	{
		j = -1;
		while (++j < var->x_piece)
		{
			if (var->piece[i][j] == '*')
			{
				var->tmp[i + point->y][j + point->x] = 'T';
				if ((i + point->y == 0 || i + point->y == var->y_map
					|| j + point->x == 0 || j + point->x == var->x_map)
					&& ft_get_dist_enemy(point, var, 0) < 4)
					return (1);
			}
		}
	}
	return (0);
}

int		ft_check_change_ownership(t_var *var, t_point *pos
	, t_point *point_to_win)
{
	int		i;
	int		j;
	int		test;

	i = -1;
	while (++i < var->y_piece)
	{
		j = -1;
		while (++j < var->x_piece)
		{
			if (var->tmp[i + pos->y][j + pos->x] == 'T'
					&& (test = point_to_win->dist > abs(point_to_win->y
						- (i + pos->y)) + abs(point_to_win->x - (j + pos->x))))
				return (1);
		}
	}
	return (0);
}

int		ft_simulate(t_var *var, t_point *spot)
{
	t_lst	*point_to_win;
	int		count;
	int		i;

	if (ft_place_piece(var, spot))
		return (INT_MAX);
	point_to_win = *(var->pts_neutral);
	count = 0;
	while (point_to_win)
	{
		if (((t_point *)point_to_win->content)->owner != var->player
				&& ft_check_change_ownership(var, spot
					, (t_point *)point_to_win->content))
			count++;
		point_to_win = point_to_win->next;
	}
	i = -1;
	while (++i < var->y_piece)
		ft_strcpy(var->tmp[i + spot->y], var->map[i + spot->y]);
	return (count);
}

void	ft_algo(t_var *var, int count, int opt)
{
	int		tmp;
	t_lst	*point;

	point = opt ? *var->pts_neutral : *var->pts_player;
	while (point)
	{
		if (((t_point *)point->content)->available && count < INT_MAX
			&& ((tmp = ft_simulate(var, (t_point *)point->content)) > count))
		{
			var->x_pos = ((t_point *)point->content)->x;
			var->y_pos = ((t_point *)point->content)->y;
			count = tmp;
			if (!(var->enemy_is_playing))
				return ;
		}
		point = point->next;
		opt ? (ft_algo(var, count, 0)) : 0;
	}
	return ;
}
