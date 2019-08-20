/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:16:19 by hehlinge          #+#    #+#             */
/*   Updated: 2019/08/20 17:17:06 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_reset_piece(t_var *var, t_point *point)
{
	int		i;

	i = -1;
	while (++i < var->y_piece)
		ft_strcpy(var->tmp[i + point->y], var->map[i + point->y]);
}

void	ft_place_piece(t_var *var, t_point *point)
{
	int		i;
	int		j;

	i = -1;
	while (++i < var->x_piece)
	{
		j = -1;
		while (++j < var->y_piece)
		{
			if (var->piece[j][i] == '*')
				var->tmp[j + point->y][i + point->x] = 'T';
		}
	}
}

int		ft_check_change_ownership(t_var *var, t_point *pos, t_point *point_to_win)
{
	int		i;
	int		j;
	int		test;

	i = -1;
//	ft_printf("TESTED POINT : x = %d, y = %d, dist = %d\n", point_to_win->x, point_to_win->y, point_to_win->dist);
	while (++i < var->x_piece)
	{
		j = -1;
		while (++j < var->y_piece)
		{
			if (var->tmp[j + pos->y][i + pos->x] == 'T' // si point temporaire
					&& (test = abs(point_to_win->x - (i + pos->x))
						+ abs(point_to_win->y - (j + pos->y))) < point_to_win->dist) // et que la distance est meilleure
			{
				ft_printf("OWNERSHIP CHANGED FOR Y: %d, X: %d\n"
					, point_to_win->y, point_to_win->x);
				ft_printf("test = %d, dist = %d\n", test, point_to_win->dist);
				// LE PROBLEME c'est que ici la valeur point->dist n'est pas bonne alors qu'elle a bien été écrite dans les fonctions précédentes
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

	ft_printf("AVAILABLE PT : x = %d, y = %d (current owner: %c)\n",
			available_spot->x, available_spot->y, available_spot->owner);
	ft_place_piece(var, available_spot); // on place la piece dans tmp
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

	point = *(var->pts_neutral);
	count = 0; // count c'est le meilleur nombre de points convertis jusqu'a maintenant
	while (point) // on boucle sur tous les points neutre pour chercher les spots dispos
	{
		if (((t_point *)point->content)->available // si le point est disponible
				&& ((tmp = ft_simulate(var, (t_point *)point->content)) > count))
		{
			var->x_pos = ((t_point *)point->content)->x;
			var->y_pos = ((t_point *)point->content)->y;
			count = tmp;
			// si on améliore le meilleur nombre de points convertis on update le meilleur point
		}
		point = point->next;
	}
	// si on est X il faut aussi boucler sur les points de X et vice versa avec O
	point = *(var->pts_player);
	while (point)
	{
		if (((t_point *)point->content)->available
				&& ((tmp = ft_simulate(var, (t_point *)point->content)) > count))
		{
			var->x_pos = ((t_point *)point->content)->x;
			var->y_pos = ((t_point *)point->content)->y;
			count = tmp;
		}
		point = point->next;
	}
}
