/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:28:16 by hehlinge          #+#    #+#             */
/*   Updated: 2019/09/12 18:01:19 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <unistd.h>
#include <fcntl.h>
#include "filler.h"
#include "libft.h"

void	set_ncurses(t_clr *clr)
{
	initscr();
	start_color();
	curs_set(0);
	noecho();
	timeout(-1);
	getch();
	init_pair(PLAYER, COLOR_CYAN, COLOR_CYAN);
	init_pair(NP, COLOR_CYAN, COLOR_BLACK);
	init_pair(ENEMY, COLOR_RED, COLOR_RED);
	init_pair(NE, COLOR_RED, COLOR_BLACK);
	init_pair(NN, COLOR_WHITE, COLOR_BLACK);
	init_pair(RST, COLOR_WHITE, COLOR_BLACK);
	clr->top = ft_max(LINES / 2 - clr->var->y_map / 2 - 3, 10);
	clr->center_line = LINES / 2;
	clr->bottom = clr->top + clr->var->y_map + 7;
	clr->width = ft_max(25, clr->var->x_map / 2 + 4);
	clr->center_col = COLS / 2;
	clr->border_l = COLS / 2 - clr->width;
	clr->border_r = COLS / 2 + clr->width;
	print_box(clr);
}

int		get_size_map(t_clr *clr, t_var *var)
{
	int		pos;
	char	*line;

	while (get_next_line(0, &line) && ft_strncmp(line, "Plat", 4))
		if (!line)
			return (0);
	pos = ft_strlen("Plateau ");
	var->y_map = ft_atoi(line + pos);
	while (line[pos] >= '0' && line[pos] <= '9')
		pos++;
	var->x_map = ft_atoi(line + pos);
	if (!(var->map = (char **)easymalloc(sizeof(char *) * var->y_map)))
		return (0);
	pos = -1;
	while (++pos < var->y_map)
		if (!(var->map[pos] = (char *)easymalloc(var->x_map + 1)))
			return (0);
	set_ncurses(clr);
	return (1);
}

int		ft_parse_first_line(t_clr *clr, t_var *var)
{
	int		pos;
	char	*line;
	char	*name;

	while (get_next_line(0, &line) && ft_strncmp(line, "$$$", 3))
		if (!line)
			return (0);
	pos = ft_strlen("$$$ exec p");
	clr->var->player = line[pos] == '1' ? 'O' : 'X';
	var->enemy = line[pos] == '1' ? 'X' : 'O';
	pos = ft_strchr_pos(line, '/') + 1;
	if (!(name = ft_strsub(line, pos, ft_strchr_pos(line, '.') - pos)))
		return (0);
	if (!(var->player == 'O' && (clr->name_player = name)))
		clr->name_enemy = name;
	if (!get_next_line(0, &line))
		return (0);
	pos = ft_strchr_pos(line, '/') + 1;
	if (!(name = ft_strsub(line, pos, ft_strchr_pos(line, '.') - pos)))
		return (0);
	if (!(var->player == 'X' && (clr->name_player = name)))
		clr->name_enemy = name;
	return (get_size_map(clr, var));
}

void	ft_parse_args(char **argv, t_clr *clr)
{
	char	*arg;
	int		pos;

	pos = 0;
	clr->pause = MEDIUM;
	while ((arg = argv[++pos]))
	{
		if (!ft_strcmp(arg, "anim"))
			clr->anim = 1;
		else if (!ft_strcmp(arg, "slow"))
			clr->pause = SLOW;
		else if (!ft_strcmp(arg, "medium"))
			clr->pause = MEDIUM;
		else if (!ft_strcmp(arg, "fast"))
			clr->pause = FAST;
	}
}

int		main(int argc, char **argv)
{
	t_clr	clr;

	(void)argc;
	ft_memset(&clr, 0, sizeof(clr));
	ft_parse_args(argv, &clr);
	if (!(clr.var = (t_var *)easymalloc(sizeof(*clr.var))))
		return (0);
	ft_memset(clr.var, 0, sizeof(*clr.var));
	ft_parse_first_line(&clr, clr.var);
	while (ft_parse_input_color(clr.var))
		print_map_ncurses(&clr, -1, -1, 0);
	usleep(clr.pause * 5);
	endwin();
	close(clr.var->fd);
}
