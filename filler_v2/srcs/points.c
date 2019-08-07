/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:44:03 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/03 15:28:43 by sikpenou         ###   ########.fr       */
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

t_lst		ft_get_closest(t_lst	*point, t_var *var)
{
	t_lst		*tmp;
	t_lst		*res;
	int			min_dist;
	int			dist;

	min_dist = var->x_map + var->y_map;
	if ((tmp = *((t_lst)var->points_o)))
	{
		while (tmp->next)
		{
			dist = abs(((t_point *)tmp->content)->x - point->x)
				+ abs(((t_point *)tmp->content)->y - point->y);
			if (dist < min_dist)
			{
				min_dist = dist;
				res = tmp;
			}
		}
	}
	if ((tmp = *((t_lst)var->points_o)))
	{
		while (tmp->next)
		{
			dist = abs(((t_point *)tmp->content)->x - point->x)
				+ abs(((t_point *)tmp->content)->y - point->y);
			if (dist < min_dist)
			{
				min_dist = dist;
				res = tmp;
			}
		}
	}
	return (res);
}

int			ft_get_points(t_var *var)
{
	int		i;
	int		j;
	char	c;

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
				if (!(ft_lstadd_new(var->points_n, (void *)ft_new_point(j, i, c)
						, sizeof(t_point *))))
					return (0);
		}
	}
	print_debug(*var, "123");
	return (1);
}
