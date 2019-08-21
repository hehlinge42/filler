/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:44:03 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/21 18:59:42 by sikpenou         ###   ########.fr       */
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
		return (new);
	}
	return (0);
}

// point est la ref, le point a convertir, et tmp est le point actuel pour
// lequel on regarde si il fait basculer, on le recupere dans une liste
void	ft_dist(t_point *point, t_lst *tmp, t_var *var)
{
	int		test;
	int		x;
	int		y;

	x = point->x;
	y = point->y;
	point = tmp->content;
	//ft_printf("Entrée dans ft_dist : x = %d, y = %d\n", x, y);
	//ft_printf("test = %d, dist = %d\n",  abs(((t_point *)point->content)->x - x)
	//+ abs(((t_point *)point->content)->y - y),  ((t_point *)point->content)->dist);
	if (x >= 0 && y >= 0 && x < var->x_map && y < var->y_map
		&& var->map[y][x] != '.' && (test = abs(point->x - x)
		+ abs(point->y - y)) <= point->dist)
	{
		//ft_printf("Point valide trouvé, test = %d\n", test);
		// le if en dessous dit aue si le test (la distance au point actuel) est
		// egal a la distance a l'owner actuel, et si soit sur la map on a
		// l'ennemi et en owner le player ou l'inverse alors on ne sait pas
		// on peut resumer ça en si map != owner && map + 32 != owner je crois
		 /*
		if (test == ((t_point *)point->content)->dist
			&& (((var->map[y][x] == var->enemy
				|| var->map[y][x] == var->enemy + 32)
			&& (((t_point *)point->content)->owner == var->player
				|| var->map[y][x] == var->player + 32))
			|| ((var->map[y][x] == var->player
				|| var->map[y][x] == var->player + 32)
			&& ((t_point *)point->content)->owner == var->enemy)))
			*/
		if (test == point->dist && var->map[y][x] != point->owner
			&& var->map[y][x] - 32 != point->owner)
			point->owner = '?';
		else
		{
			point->x_owner = x;
			point->y_owner = y;
			point->dist = test;
			if (var->map[y][x] == var->enemy
				|| var->map[y][x] == var->enemy + 32)
				point->owner = var->enemy;
			else if (var->map[y][x] == var->player
				|| var->map[y][x] == var->player + 32)
				point->owner = var->player;
		}
	}
	//ft_printf("Sortie de ft_distr\n");
}

void	ft_get_closest(t_lst	*point, t_var *var)
{
	int			square_nb;
	t_point		tmp;

	square_nb = 1;
	ft_memset(&tmp, 0, sizeof(tmp));
	((t_point *)point->content)->dist = (var->x_map >= var->y_map) ? var->x_map : var->y_map;
	//ft_printf("tmp.dist = %d\n", ((t_point *)point->content)->dist);
	while (((t_point *)point->content)->dist >= square_nb)
	{
		//ft_printf("loop %d, dist = %d\n", square_nb, ((t_point *)point->content)->dist);
		tmp.y = ((t_point *)point->content)->y - square_nb - 1;
		tmp.x = ((t_point *)point->content)->x - square_nb - 1;
		while (++(tmp.y) <= ((t_point *)point->content)->y + square_nb)
		{
			//ft_printf("y = %d, limit = %d\n", tmp.y, ((t_point *)point->content)->y + square_nb);
			if (tmp.y == ((t_point *)point->content)->y - square_nb
				|| tmp.y == ((t_point *)point->content)->y  + square_nb)
			{
				tmp.x = ((t_point *)point->content)->x - square_nb - 1;
				while (++(tmp.x) <= ((t_point *)point->content)->x  + square_nb)
				{
					//ft_printf("tested point : x = %d, y = %d\n", tmp.x, tmp.y);
					ft_dist(&tmp, point, var);
				}
			}
			else
			{
				tmp.x = ((t_point *)point->content)->x - square_nb;
				//ft_printf("tested point : x = %d, y = %d\n", tmp.x, tmp.y);
				ft_dist(&tmp, point, var);
				tmp.x = ((t_point *)point->content)->x + square_nb;
				//ft_printf("tested point : x = %d, y = %d\n", tmp.x, tmp.y);
				ft_dist(&tmp, point, var);
			}
		}
		square_nb++;
	}
	/*
	ft_printf("Point x = %d, y = %d : Owner = %c, x_owner = %d, y_owner = %d, dist = %d\n",
		((t_point *)point->content)->x,
		((t_point *)point->content)->y,
		((t_point *)point->content)->owner,
		((t_point *)point->content)->x_owner,
		((t_point *)point->content)->y_owner,
		((t_point *)point->content)->dist);
		*/
	/*
	if (*var->pts_neutral)
		printf("in get_cl, n start dist (%p): %d, n last dist: %d\n"
			, ((t_point *)(*(var->pts_neutral))->content)
			, ((t_point *)(*(var->pts_neutral))->content)->dist
			,((t_point *)(*(var->pts_neutral))->last->content)->dist);
		*/
}

void		ft_available(t_var *var)
{
	t_lst	*tmp;

//	printf("dist ft start: %d\n", ((t_point *)(*var->pts_neut)->content)->dist);
	tmp = *(var->pts_player);
	while (tmp)
	{
		((t_point *)tmp->content)->available = is_available(*var
			, ((t_point *)tmp->content)->x, ((t_point *)tmp->content)->y);
		tmp = tmp->next;
	}
	tmp = *(var->pts_neutral);
	while (tmp)
	{
//		printf("dist before assign: %d\n", ((t_point *)tmp->content)->dist);
		((t_point *)tmp->content)->available = is_available(*var
			, ((t_point *)tmp->content)->x, ((t_point *)tmp->content)->y);
		tmp = tmp->next;
//		printf("dist after  assign: %d\n", ((t_point *)tmp->content)->dist);
	}
	//this line is to SEGFAULT because i have the flemme to include the lib for
	//exit
//	tmp->next->next = NULL;
//	printf("dist ft end  : %d\n", ((t_point *)(*var->pts_neut)->content)->dist);
}

int			ft_get_points(t_var *var)
{
	char	c;
	t_lst	*point;
	t_lst	*tmp;

	//print_points(*var);
	point = *var->pts_neutral;
	while (point)
	{
		if ((c = var->map[((t_point *)point->content)->y][((t_point *)point->content)->x]) != '.')
		{
			if (point == *var->pts_neutral)
				*var->pts_neutral = ((t_lst *)*var->pts_neutral)->next;
			else
				tmp->next = point->next;
			point->next = NULL;
			if (c == var->player || c == var->player + 32)
				ft_lstadd(var->pts_player, point);
			else
				ft_free((void **)point);
		}
		tmp = point;
		((t_point *)point)->available = is_available(*var, ((t_point *)point)->x
			, ((t_point *)point)->y);
		point = point->next;
	}
	print_points(*var);
	return (1);
}
