/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 10:37:56 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/12 15:35:22 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdio.h>
#include <curses.h>
#include <unistd.h>

int		ft_parse_map(int nb, char *line, t_var *var)
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

int		ft_parse_input_color(t_var *var)
{
	char	*line;
	int		nb;

	var->enemy_is_playing = (var->turn) ? 0 : 1;
	while (get_next_line(0, &line) && ft_strncmp(line, "   ", 3))
		if (!ft_strncmp(line, "==", 2))
			return (0);
	nb = 0;
	while (nb < var->y_map
			&& get_next_line(0, &line) > -1 && ft_parse_map(nb, line, var))
		nb++;
	if (nb == var->y_map)
		return (1);
	return (0);
}
