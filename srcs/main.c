/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:28:16 by hehlinge          #+#    #+#             */
/*   Updated: 2019/09/04 17:33:39 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

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

int			ft_parse_first_line(t_var *var)
{
	int		pos;
	char	*line;

	if (!(get_next_line(0, &line)))
		return (0);
	pos = ft_strlen("$$$ exec p");
	if (ft_strncmp(line, "$$$ exec p", pos))
		return (0);
	if (line[pos] != '1' && line[pos] != '2')
		return (0);
	var->player = line[pos] == '1' ? 'O' : 'X';
	var->enemy = line[pos] == '1' ? 'X' : 'O';
	pos++;
	if (ft_strcmp(line + pos, " : [players/hehlinge.filler]"))
		return (0);
	return (1);
}

int			ft_init_exit(t_var *var, int opt)
{
	if (opt)
	{
		if (opt == ERR_FIRST_LINE)
			ft_printf("exit - bad first line\n");
		else if (opt == BAD_MAP)
			ft_printf("exit - bad map\n");
		return (0);
	}
	ft_memset(var, 0, sizeof(*var));
	var->turn = -1;
	if ((var->pts_player = (t_lst **)easymalloc(sizeof(*var->pts_player)))
		&& (var->pts_neutral = (t_lst **)easymalloc(sizeof(*var->pts_neutral))))
		return (1);
	return (0);
}

int			ft_init_neutral_points(t_var *var, int i, int j)
{
	t_lst	*tmp;

	while (++i < var->y_map)
	{
		j = -1;
		while (++j < var->x_map)
		{
			if (!((tmp = ft_lstadd_new(var->pts_neutral,
							(void *)ft_new_point(j, i, '.'), sizeof(t_point)))))
				return (0);
			((t_point *)tmp->content)->dist = 2147483647;
		}
	}
	var->nb_neutral = var->x_map * var->y_map;
	if (!(var->map = (char **)easymalloc(sizeof(char *) * var->y_map))
			|| !(var->tmp = (char **)easymalloc(sizeof(char *) * var->y_map)))
		return (0);
	i = -1;
	while (++i < var->y_map)
		if (!(var->map[i] = (char *)easymalloc(var->x_map + 1))
				|| !(var->tmp[i] = (char *)easymalloc(var->x_map + 1)))
			return (0);
	return (1);
}

int			main(void)
{
	t_var		var;
	int			fd;
	t_point		*point;
	t_lst		*tmp;

	point = 0;
	tmp = 0;
	fd = open("debug.txt", O_WRONLY | O_CREAT | O_TRUNC, 777);
	if (ft_init_exit(&var, 0))
	{
		var.fd = fd;
		if (!ft_parse_first_line(&var))
			return (ft_init_exit(&var, ERR_FIRST_LINE));
		while (++var.turn > -1)
		{
			if (!ft_parse_input(&var))
			{
				close(fd);
				return (ft_init_exit(&var, BAD_MAP));
			}
			ft_get_points(&var, point, *var.pts_neutral, tmp);
			ft_algo(&var, -1, 1);
			ft_printf("%d %d\n", var.y_pos, var.x_pos);
			var.x_pos = -1;
			var.y_pos = -1;
		}
	}
	return (1);
}
