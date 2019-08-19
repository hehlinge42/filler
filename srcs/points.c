/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:44:03 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/19 17:54:52 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_point		*ft_new_point(int x, int y, char c)
{
	t_point		*new;

	if ((new = (t_point *)easymalloc(sizeof(*new))))
	{
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
			(((var->map[tmp->y][tmp->x] == 'O' || var->map[tmp->y][tmp->x] == 'o') && ((t_point *)point->content)->owner == 'X')
			|| ((var->map[tmp->y][tmp->x] == 'X' || var->map[tmp->y][tmp->x] == 'x') && ((t_point *)point->content)->owner == 'O')))
			((t_point *)point->content)->owner = '?';
		else
		{
			((t_point *)point->content)->x_owner = tmp->x;
			((t_point *)point->content)->y_owner = tmp->y;
			((t_point *)point->content)->dist = test;
			if (var->map[tmp->y][tmp->x] == 'O' || var->map[tmp->y][tmp->x] == 'o')
				((t_point *)point->content)->owner = 'O';
			else if (var->map[tmp->y][tmp->x] == 'X' || var->map[tmp->y][tmp->x] == 'x')
				((t_point *)point->content)->owner = 'X';
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
}

void		ft_available(t_var *var)
{
	t_lst	*tmp;

	tmp = var->player == 'X' ? *(var->points_x) : *(var->points_o);
	while (tmp)
	{
		((t_point *)tmp->content)->available = is_available(*var
			, ((t_point *)tmp->content)->x, ((t_point *)tmp->content)->y);
		tmp = tmp->next;
	}
	tmp = *var->points_n;
	while (tmp)
	{
		((t_point *)tmp->content)->available = is_available(*var
			, ((t_point *)tmp->content)->x, ((t_point *)tmp->content)->y);
		tmp = tmp->next;
	}
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
			if (c == 'o' || c == 'O')
				if (!(ft_lstadd_new(var->points_o, (void *)ft_new_point(j, i, c)
						, sizeof(t_point *))))
					return (0);
			if (c == 'x' || c == 'X')
				if (!(ft_lstadd_new(var->points_x, (void *)ft_new_point(j, i, c)
						, sizeof(t_point *))))
					return (0);
			if (c == '.')
			{
				if (!(point = ft_lstadd_new(var->points_n, (void *)ft_new_point(j, i, c)
						, sizeof(t_point *))))
					return (0);
				//ft_printf("Enters ft_get_closest : x = %d, y = %d\n", j, i);
				ft_get_closest(point, var);
			}
		}
	}
	ft_available(var);
	return (1);
}
