/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 10:37:56 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/04 14:56:51 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdio.h>

int		ft_parse_size(char *line, t_var *var, char *option)
{
	int		pos;

	pos = ft_strlen(option);
	if (ft_strncmp(line, option, pos))
		return (0);
	if (ft_strcmp(option, "Piece "))
		var->y_map = ft_atoi(line + pos);
	else
		var->y_piece = ft_atoi(line + pos);
	while (line[pos] >= '0' && line[pos] <= '9')
		pos++;
	if (line[pos++] != ' ')
		return (0);
	if (ft_strcmp(option, "Piece "))
		var->x_map = ft_atoi(line + pos);
	else
		var->x_piece = ft_atoi(line + pos);
	while (line[pos] >= '0' && line[pos] <= '9')
		pos++;
	if (!ft_strcmp(option, "Plateau ") || (!(ft_strcmp(option, "Piece "))
		&& (var->piece = (char **)easymalloc(sizeof(char *) * var->y_piece))))
		if (line[pos] == ':' && line[pos + 1] == 0)
			return (1);
	return (0);
}

int		ft_parse_map_l0(char *line, t_var var)
{
	int		pos;
	int		mod;

	pos = 3;
	if ((*line == '\t' && !(pos = 0))
		|| (ft_isspace(line[0]) && ft_isspace(line[1]) && ft_isspace(line[2])))
	{
		while (ft_isspace(line[pos++]) && var.y_map > 100)
			var.y_map /= 10;
		mod = 0;
		while (line[pos++] - 48 == mod % 10)
			mod++;
		if (!line[pos] && mod == var.x_map)
			return (1);
	}
	return (0);
}

int		ft_parse_map(int nb, char *line, t_var *var)
{
	if (nb > -1)
	{
		if (ft_atoi(line) == nb)
		{
			while (ft_isdigit(*line))
				line++;
			if (*(line++) == ' ' && (int)ft_strlen(line) == var->x_map)
			{
				ft_strncpy(var->map[nb], line, var->x_map);
				while (*line == 'o' || *line == 'x' || *line == 'O'
						|| *line == 'X' || *line == '.')
					line++;
				if (!*line)
					return (1);
			}
		}
		return (0);
	}
	return (ft_parse_map_l0(line, *var));
}

int		ft_parse_piece(int nb, char *line, t_var *var)
{
	if ((var->piece[nb] = (char *)easymalloc(var->x_piece + 1)))
	{
		ft_strcpy(var->piece[nb], line);
		while (*line == '.' || *line == '*')
			line++;
		if (!*line)
			return (1);
	}
	return (0);
}

int			alloc_map(t_var *var)
{
	int		i;

	var->turn++;
	if (!(var->map = (char **)easymalloc(sizeof(char *) * var->y_map)))
		return (0);
	i = -1;
	while (++i < var->y_map)
		if (!(var->map[i] = (char *)easymalloc(var->x_map + 1)))
			return (0);
	return (1);
}

int		ft_parse_input(t_var *var)
{
	char	*line;
	int		nb;

	var->enemy_is_playing = (var->turn) ? 0 : 1;
	while (get_next_line(0, &line) && ft_strncmp(line, "Plat", 4))
		if (!ft_strncmp(line, "==", 2))
			return (0);
	if (ft_parse_size(line, var, "Plateau "))
	{
		if (!var->turn)
			alloc_map(var);
		nb = -1;
		while (nb < var->y_map
			&& get_next_line(0, &line) > -1 && ft_parse_map(nb, line, var))
			nb++;
		if (nb == var->y_map
			&& get_next_line(0, &line) && ft_parse_size(line, var, "Piece "))
		{
			nb = 0;
			while (nb < var->y_piece
				&& get_next_line(0, &line) && ft_parse_piece(nb, line, var))
				nb++;
			if (nb == var->y_piece)
				return (1);
		}
	}
	return (0);
}
