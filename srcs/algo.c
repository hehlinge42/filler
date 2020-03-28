/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:02:36 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/21 13:14:02 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <limits.h>

/*
** Parameter: t_point *point: the point to place the piece on
** Return: 1 if the piece is close enough to a map's border and the enemy is
** at maximum 4 points. In this case, this spot becomes a priority. 0 otherwise
**
** ft_place_piece inserts the piece on the temporary map with 'T'characters
** for further calculations without impacting the actual map
*/

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

/*
** Parameters:
**  - t_point *pos: the point to place the piece on
**  - t_point point_to_win: the neutral point to check the ownership
** Return: 1 is the neutral point becomes closer from the player than the opponent
** thanks to the new piece. 0 otherwise
**
** The function iterates on the temporary map in the area where the piece has been
** placed. For each potential new point owned by the player 'T', it checks the distance
** with the neutral point and compare it with the current distance to owner. 
*/

int		ft_check_change_ownership(t_var *var, t_point *pos
	, t_point *point_to_win)
{
	int		i;
	int		j;

	i = -1;
	while (++i < var->y_piece)
	{
		j = -1;
		while (++j < var->x_piece)
		{
			if (var->tmp[i + pos->y][j + pos->x] == 'T'
					&& (point_to_win->dist > ft_abs(point_to_win->y
						- (i + pos->y)) + ft_abs(point_to_win->x
							- (j + pos->x))))
				return (1);
		}
	}
	return (0);
}

/*
** Parameters: the point considered to place the piece
** Return: the number of neutral points that become closer from the
** player than from the opponent thanks to the new piece.
**
** ft_simulate calls ft_place_piece in order to copy the piece on the
** temporary map for further calculation without modifying the actual map
** ft_simulate iterates on every neutral points.
** It calls ft_check_change_ownership on each neutral point to check if this
** point becomes closer from the player than from the opponent.
** It returns the number of points that meet this condition
*/

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

/*
** Parameters: int count, int opt = determines on which chained list to iterate
**
** ft_algo is launched 2 times per turn to iterate on both the neutral points
** and the player's points.
** It calls ft_simulate on each available point to know is this point is a better
** spot to place the piece than the current best, that is to say that more neutral
** points become closer to the player than the opponent by adding the new piece 
** on this spot. If so, it upgrades the current best.
*/

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
	}
	opt ? (ft_algo(var, count, 0)) : 0;
}
