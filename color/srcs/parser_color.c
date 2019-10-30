/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 10:37:56 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/13 22:25:39 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

void			print_title(t_clr *clr, int sleep, int start)
{
	char	*line;

	sleep = clr->anim ? 150000 : 0;
	usleep(sleep * 6);
	line = "    *********  ***  ***     ***     ******  ******";
	start = COLS / 2 - ft_strlen(line) / 2;
	mvprintw(clr->top - 7, start, "%s", line);
	refresh();
	usleep(sleep);
	line = "   ***        ***  ***     ***     **      **   ***";
	mvprintw(clr->top - 6, start, "%s", line);
	refresh();
	usleep(sleep);
	line = "  ******     ***  ***     ***     ****    *** *** ";
	mvprintw(clr->top - 5, start, "%s", line);
	refresh();
	usleep(sleep);
	line = " ***        ***  ***     ***     **      ***   ***";
	mvprintw(clr->top - 4, start, "%s", line);
	refresh();
	usleep(sleep);
	line = "***        ***  ******  ******  ******  ***     ***";
	mvprintw(clr->top - 3, start, "%s", line);
	refresh();
	usleep(sleep);
}

static int		ft_parse_map(int nb, char *line, t_var *var)
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

int				ft_parse_input_color(t_var *var)
{
	char	*line;
	int		nb;

	var->enemy_is_playing = (var->turn) ? 0 : 1;
	while (filler_gnl(0, &line) && ft_strncmp(line, "   ", 3))
		if (!ft_strncmp(line, "==", 2))
			return (0);
	nb = 0;
	while (nb < var->y_map
			&& filler_gnl(0, &line) > -1 && ft_parse_map(nb, line, var))
		nb++;
	if (nb == var->y_map)
		return (1);
	return (0);
}

int				get_size_map(t_clr *clr, t_var *var, int pos)
{
	char	*line;

	while (filler_gnl(0, &line) && line && ft_strncmp(line, "Plat", 4))
		if (!line)
			return (0);
	pos = ft_strlen("Plateau ");
	var->y_map = ft_atoi(line + pos);
	while (line[pos] >= '0' && line[pos] <= '9')
		pos++;
	var->x_map = ft_atoi(line + pos);
	if (!(var->map = (char **)malloc(sizeof(char *) * var->y_map)))
		return (0);
	clr->map_allocated = 1;
	pos = -1;
	while (++pos < var->y_map)
		if (!(var->map[pos] = (char *)malloc(var->x_map + 1)))
			return (0);
	clr->map_allocated = 2;
	if (set_ncurses(clr))
		return (1);
	while (!ft_strrchr(line, '='))
		filler_gnl(0, &line);
	return (0);
}

int				ft_parse_first_line_color(t_clr *clr, t_var *var, int pos
	, int stop)
{
	char	*line;
	char	*name;

	while (filler_gnl(0, &line) && line && ft_strncmp(line, "$$$", 3))
		stop++;
	if (!line || stop > 50)
		return (0);
	clr->var->player = line[pos] == '1' ? 'O' : 'X';
	var->enemy = line[pos] == '1' ? 'X' : 'O';
	pos = ft_strchr_pos(line, '/') + 1;
	if (!(name = ft_strsub(line, pos, ft_strchr_pos(line, '.') - pos)))
		return (0);
	if (!(var->player == 'O' && (clr->name_player = name)))
		clr->name_enemy = name;
	if (!filler_gnl(0, &line))
		return (0);
	pos = ft_strchr_pos(line, '/') + 1;
	if (!(name = ft_strsub(line, pos, ft_strchr_pos(line, '.') - pos)))
		return (0);
	if (!(var->player == 'X' && (clr->name_player = name)))
		clr->name_enemy = name;
	if (get_size_map(clr, var, 0))
		while (ft_parse_input_color(clr->var))
			print_map_ncurses(clr, -1, -1);
	return (1);
}
