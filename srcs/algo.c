/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:16:19 by hehlinge          #+#    #+#             */
/*   Updated: 2019/09/01 18:36:24 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <limits.h>

void	ft_reset_piece(t_var *var, t_point *point)
{
	int		i;

	i = -1;
	while (++i < var->y_piece)
		ft_strcpy(var->tmp[i + point->y], var->map[i + point->y]);
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
					&& ft_get_dist_enemy(point, var) < 4)
				{
					dprintf(var->fd, "\t\t\t\tABOUT TO TOUCH WALL: enemy dist =  %d\n"
						, ft_get_dist_enemy(point, var));
					return (1);
				}
			}
		}
	}
	return (0);
}

int		ft_check_change_ownership(t_var *var, t_point *pos, t_point *point_to_win)
{
	int		i;
	int		j;
	int		test;

	i = -1;
	while (++i < var->x_piece)
	{
		j = -1;
		while (++j < var->y_piece)
		{
			if (var->tmp[j + pos->y][i + pos->x] == 'T' // si point temporaire
					&& (test = abs(point_to_win->x - (i + pos->x))
						+ abs(point_to_win->y - (j + pos->y))) < point_to_win->dist) // et que la distance est meilleure
			{
				return (1);
			}
		}
	}
	return (0);
}

int		ft_simulate(t_var *var, t_point *available_spot)
{
	t_lst	*point_to_win;
	int		count;

	if (ft_place_piece(var, available_spot))
		return (INT_MAX); 	
	point_to_win = *(var->pts_neutral);
	count = 0;
	while (point_to_win) // on boucle sur tous les points neutres
	{
		if (((t_point *)point_to_win->content)->owner != var->player // si le point n'est pas à nous
				&& ft_check_change_ownership(var, available_spot, (t_point *)point_to_win->content)) // on regarde pour chaque point si on le gagne
			count++;
		point_to_win = point_to_win->next;
	}
	ft_reset_piece(var, available_spot); // on remet tmp à sa position initiale
	return (count);
}

void	ft_algo(t_var *var)
{
	t_lst	*point;
	int		count;
	int		tmp;

	dprintf(var->fd, "--------\nIN ALGO\n\nNEUTRAL POINTS:\n");
	point = *(var->pts_neutral);
	count = -1; // count c'est le meilleur nombre de points convertis jusqu'a maintenant
	while (point) // on boucle sur tous les points neutre pour chercher les spots dispos
	{
		if (((t_point *)point->content)->available && count < INT_MAX
				&& ((tmp = ft_simulate(var, (t_point *)point->content)) > count))
		{
			var->x_pos = ((t_point *)point->content)->x;
			var->y_pos = ((t_point *)point->content)->y;
			count = tmp;
			print_point(((t_point *)point->content), var->fd);
			dprintf(var->fd, "count: %d\n", count);
			if (!(var->enemy_is_playing))
				return ;
			// si on améliore le meilleur nombre de points convertis on update le meilleur point
		}
		point = point->next;
	}
	// si on est X il faut aussi boucler sur les points de X et vice versa avec O
	dprintf(var->fd, "PLAYER POINTS:\n");
	point = *(var->pts_player);
	while (point)
	{
		if (((t_point *)point->content)->available && count < INT_MAX
				&& ((tmp = ft_simulate(var, (t_point *)point->content)) > count))
		{
			var->x_pos = ((t_point *)point->content)->x;
			var->y_pos = ((t_point *)point->content)->y;
			count = tmp;
			print_point(((t_point *)point->content), var->fd);
			dprintf(var->fd, "count: %d\n", count);
			if (!(var->enemy_is_playing))
				return ;

		}
		point = point->next;
	}
	dprintf(var->fd, "--------\nOUT ALGO, SELECTED: %d-%d\n", var->y_pos, var->x_pos);
}
