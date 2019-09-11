/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:28:16 by hehlinge          #+#    #+#             */
/*   Updated: 2019/09/11 16:36:07 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <unistd.h>
#include <fcntl.h>
#include "filler.h"
#include "libft.h"

#define PLAYER 1
#define NP 2
#define ENEMY 3
#define NE 4
#define NN 5
#define RST 6
#define SLOW 200000
#define MEDIUM 100000
#define FAST 35000

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
	ft_strcmp(name, "hehlinge") ?
		(clr->name_enemy = name) : (clr->name_player = name);
	if (!get_next_line(0, &line))
		return (0);
	pos = ft_strchr_pos(line, '/') + 1;
	if (!(name = ft_strsub(line, pos, ft_strchr_pos(line, '.') - pos)))
		return (0);
	clr->name_player ? (clr->name_enemy = name) : (clr->name_player = name);
	return (1);
}

int		get_faster(t_var *var, int o_y, int o_x, int step)
{
	int		ret[2];
	int		y;
	int		x;
	char	c;

	ft_memset(ret, 0, sizeof(*ret) * 2);
	while (!ret[0] && !ret[1] && ++step < var->y_map + var->x_map)
	{
		y = o_y - step >= 0 ? o_y - step - 1 : -1;
		while (++y < var->y_map && y <= o_y + step)
		{
			x = o_x - step >= 0 ? o_x - step - 1 : -1;
			while (++x < var->x_map && x <= o_x + step)
				if ((c = var->map[y][x]) != '.' && abs(x - o_x) == step
					- abs(y - o_y))
					c == var->player || c == var->player + 32 ? (ret[0])++
						: (ret[1])++;
		}
	}
	if (ret[0] && ret[1])
		return (NN);
	return (ret[0] ? NP : NE);
}

void	ft_print_score(t_clr *clr)
{
	move(1, 0);
	attron(COLOR_PAIR(NP));
	printw("%s %d ", clr->name_player, clr->nb_player);
	attron(COLOR_PAIR(NE));
	printw("%d %s", clr->nb_enemy, clr->name_enemy);
	clr->nb_player = 0;
	clr->nb_enemy = 0;
}

void	print_map_ncurses(t_clr *clr, int i, int j, char c)
{
	while (++i < clr->var->y_map)
	{
		j = -1;
		while (++j < clr->var->x_map)
		{
			if ((c = clr->var->map[i][j]) != '.')
			{
				if (c == clr->var->player || c == clr->var->player + 32)
				{
					attron(COLOR_PAIR(PLAYER));
					clr->nb_player++;
				}
				else
				{
					attron(COLOR_PAIR(ENEMY));
					clr->nb_enemy++;
				}
			}
			else
				attron(COLOR_PAIR(get_faster(clr->var, i, j, 0)));
			printw("%c", clr->var->map[i][j]);
		}
		printw("\n");
	}
	ft_print_score(clr);
}

void	set_ncurses(void)
{
	initscr();
	start_color();
	curs_set(0);
	init_pair(PLAYER, COLOR_CYAN, COLOR_CYAN);
	init_pair(NP, COLOR_CYAN, COLOR_BLACK);
	init_pair(ENEMY, COLOR_RED, COLOR_RED);
	init_pair(NE, COLOR_RED, COLOR_BLACK);
	init_pair(NN, COLOR_WHITE, COLOR_BLACK);
	init_pair(RST, COLOR_WHITE, COLOR_BLACK);
}

void	ft_parse_speed(char *str, t_clr *clr)
{
	if (str && !ft_strcmp(str, "slow"))
		clr->pause = SLOW;
	else if (str && !ft_strcmp(str, "fast"))
		clr->pause = FAST;
	else
		clr->pause = MEDIUM;
}

int		main(int argc, char **argv)
{
	t_clr	clr;

	ft_memset(&clr, 0, sizeof(clr));
	if (argc < 2)
		clr.pause = MEDIUM;
	else
		ft_parse_speed(argv[1], &clr);
	if (!(clr.var = (t_var *)easymalloc(sizeof(*clr.var))))
		return (0);
	ft_memset(clr.var, 0, sizeof(*clr.var));
	set_ncurses();
	newwin(clr.var->y_map + 5, clr.var->x_map + 5, 1, 1);
	ft_parse_first_line(&clr, clr.var);
	while (ft_parse_input_color(clr.var, -1))
	{
		attron(COLOR_PAIR(RST));
		printw("turn %d\n\n", clr.var->turn);
		print_map_ncurses(&clr, -1, -1, 0);
		refresh();
		usleep(clr.pause);
		move(0, 0);
	}
	usleep(clr.pause * 5);
	endwin();
	close(clr.var->fd);
}
