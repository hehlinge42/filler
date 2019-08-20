/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:44:03 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/20 16:12:28 by sikpenou         ###   ########.fr       */
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

void	ft_dist(t_point *tmp, t_lst *point, t_var *var)
{
	int		test;

	//ft_printf("Entrée dans ft_dist : x = %d, y = %d\n", tmp->x, tmp->y);
	//ft_printf("test = %d, dist = %d\n",  abs(((t_point *)point->content)->x - tmp->x)
	//+ abs(((t_point *)point->content)->y - tmp->y),  ((t_point *)point->content)->dist);
	if (tmp->x >= 0 && tmp->y >= 0 && tmp->x < var->x_map && tmp->y < var->y_map
		&& var->map[tmp->y][tmp->x] != '.' && (test = abs(((t_point *)point->content)->x - tmp->x)
		+ abs(((t_point *)point->content)->y - tmp->y)) <= ((t_point *)point->content)->dist)
	{
		//ft_printf("Point valide trouvé, test = %d\n", test);
		if (test == ((t_point *)point->content)->dist &&
			(((var->map[tmp->y][tmp->x] == var->enemy || var->map[tmp->y][tmp->x] == var->enemy + 32) && ((t_point *)point->content)->owner == var->player)
			|| ((var->map[tmp->y][tmp->x] == var->player || var->map[tmp->y][tmp->x] == var->player + 32) && ((t_point *)point->content)->owner == var->enemy)))
			((t_point *)point->content)->owner = '?';
		else
		{
			((t_point *)point->content)->x_owner = tmp->x;
			((t_point *)point->content)->y_owner = tmp->y;
			((t_point *)point->content)->dist = test;
			if (var->map[tmp->y][tmp->x] == var->enemy || var->map[tmp->y][tmp->x] == 'o')
				((t_point *)point->content)->owner = var->enemy;
			else if (var->map[tmp->y][tmp->x] == var->player || var->map[tmp->y][tmp->x] == 'x')
				((t_point *)point->content)->owner = var->player;
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
	int		i;
	int		j;
	char	c;
	t_lst	*point;

	i = -1;
	while (++i < var->y_map)
	{
		j = -1;
		while (++j < var->x_map && (c = var->map[i][j]))
		{
			if (*var->pts_neutral)
				printf("line: %d, i: %d, j: %d, n start dist: %d, n last dist: %d\n"
					, __LINE__, i, j
					, ((t_point *)(*(var->pts_neutral))->content)->dist
					,((t_point *)(*(var->pts_neutral))->last->content)->dist);
			if (c == var->player || c == var->player + 32)
			{
				if (!(ft_lstadd_new(var->pts_player, (void *)ft_new_point(j, i, c)
						, sizeof(t_point))))
					return (0);
			if (*var->pts_neutral)
				printf("line: %d, i: %d, j: %d, n start dist: %d, n last dist: %d\n"
					, __LINE__, i, j
					, ((t_point *)(*(var->pts_neutral))->content)->dist,
					((t_point *)(*(var->pts_neutral))->last->content)->dist);
			}
			else if (c == '.')
			{
				if (!(point = ft_lstadd_new(var->pts_neutral, (void *)ft_new_point(j, i, c)
						, sizeof(t_point))))
					return (0);
				ft_get_closest(point, var);
			}
		}
	}
	ft_available(var);
	return (1);
}
