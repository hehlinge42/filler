/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:00:03 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/21 13:03:46 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

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
	while (line[pos] && line[pos] >= '0' && line[pos] <= '9')
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

	pos = 2;
	if ((*line == '\t' && (pos = -1))
		|| (ft_isspace(line[0]) && ft_isspace(line[1]) && ft_isspace(line[2])))
	{
		if (!ft_isspace(line[++pos]))
			return (0);
		mod = 0;
		while (line[++pos] - 48 == mod % 10)
			mod++;
		if (!line[pos] && mod == var.x_map)
		{
			return (1);
		}
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
				ft_strncpy(var->tmp[nb], line, var->x_map);
				while (*line == 'o' || *line == 'x' || *line == 'O'
						|| *line == 'X' || *line == '.')
					line++;
				if (!*line)
				{
					return (1);
				}
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
		{
			return (1);
		}
	}
	return (0);
}

int		ft_parse_input(t_var *var)
{
	int		nb;
	char	*line;

	var->enemy_is_playing = (var->turn) ? 0 : 1;
	if (filler_gnl(0, &line) && ft_parse_size(line, var, "Plateau "))
	{
		if (var->turn == 0)
			if (!ft_init_neutral_points(var, -1, -1))
				return (0);
		nb = -1;
		while (nb < var->y_map && filler_gnl(0, &(line))
				&& ft_parse_map(nb, line, var))
			nb++;
		if (nb == var->y_map && filler_gnl(0, &(line))
			&& ft_parse_size(line, var, "Piece "))
		{
			nb = 0;
			while (nb < var->y_piece && filler_gnl(0, &(line))
				&& ft_parse_piece(nb, line, var))
				nb++;
			if (nb == var->y_piece)
				return (1);
		}
	}
	return (0);
}
