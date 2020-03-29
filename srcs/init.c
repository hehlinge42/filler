/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:02:19 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/21 13:32:04 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

/*
** Parameters: none
** Return: the allocated t_var *
**
** This function allocate clean memory for the main t_var structure,
** initiate the turn to -1 and allocate memory for two chained lists.
** Both contain t_point structures as contents and are empty at this stage.
** The list pts_player contains the points owned by this program and
** pts_neutral contains the points owned by none of the players.
*/

t_var	*ft_init_filler(void)
{
	t_var	*var;

	if (!(var = (t_var *)easymalloc(sizeof(*var))))
		return (NULL);
	ft_memset(var, 0, sizeof(*var));
	var->turn = -1;
	if (!(var->pts_player = (t_lst **)easymalloc(sizeof(*var->pts_player))))
		return (NULL);
	if (!(var->pts_neutral = (t_lst **)easymalloc(sizeof(*var->pts_neutral))))
		return (NULL);
	return (var);
}

/*
** The function init_neutral_points is only called once during the first turn
** It calls ft_new_point to add one t_lst elem for each point of the map.
** All points are set as neutral.
** Finally, it allocates memory for the map
*/

/*
** Parameters: int x: abscissa of the point; int y: ordinate of the point
** Return: a t_point * in case of success, NULL in case of error in malloc
*/

t_point		*ft_new_point(int x, int y)
{
	t_point		*new;

	if ((new = (t_point *)easymalloc(sizeof(*new))))
	{
		ft_memset(new, 0, sizeof(*new));
		new->x = x;
		new->y = y;
		new->owner = '.';
		new->x_owner = 0;
		new->y_owner = 0;
		new->dist = 0;
		return (new);
	}
	return (0);
}

/*
** Parameters: int i: abscissa of the point; int j: ordinate of the point
** Return: 1 in case of success, 0 in case of error in malloc
*/

int			ft_init_neutral_points(t_var *var, int i, int j)
{
	t_lst	*tmp;

	while (++i < var->y_map)
	{
		j = -1;
		while (++j < var->x_map)
		{
			tmp = ft_lstadd_new(var->pts_neutral,
				(void *)ft_new_point(j, i), sizeof(t_point));
			if (!tmp || !tmp->content)
				return (0);
			((t_point *)tmp->content)->dist = 2147483647;
		}
	}
	if (!(var->map = (char **)easymalloc(sizeof(char *) * var->y_map))
		|| !(var->tmp = (char **)easymalloc(sizeof(char *) * var->y_map)))
		return (0);
	i = -1;
	while (++i < var->y_map)
	{
		if (!(var->map[i] = (char *)easymalloc(var->x_map + 1))
			|| !(var->tmp[i] = (char *)easymalloc(var->x_map + 1)))
			return (0);
	}
	return (1);
}
