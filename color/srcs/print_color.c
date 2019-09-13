/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:47:54 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/12 18:05:05 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <unistd.h>
#include <fcntl.h>
#include "filler.h"
#include "libft.h"

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
				if ((c = var->map[y][x]) != '.' && ft_abs(x - o_x) == step
					- ft_abs(y - o_y))
					c == var->player || c == var->player + 32 ? (ret[0])++
						: (ret[1])++;
		}
	}
	if (ret[0] && ret[1])
		return (NN);
	return (ret[0] ? NP : NE);
}

void	print_title(t_clr *clr, int sleep, int start)
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

void	print_score(t_clr *clr)
{
	attron(COLOR_PAIR(RST));
	mvprintw(clr->top + 1, COLS / 2 - 4, "%s %d", "turn", clr->var->turn++);
	attron(COLOR_PAIR(NP));
	mvprintw(clr->top + 2, clr->border_l + 2, "%s % *d"
		, clr->name_player, clr->width - ft_strlen(clr->name_player) - 3
		, clr->nb_player);
	attron(COLOR_PAIR(NE));
	printw(" %-*d %s ", clr->width - ft_strlen(clr->name_enemy) - 3
		, clr->nb_enemy, clr->name_enemy);
	clr->nb_player = 0;
	clr->nb_enemy = 4;
	refresh();
	if (clr->var->turn == 1 && clr->anim)
		usleep(1000000);
	attron(COLOR_PAIR(RST));
	while (clr->var->turn == 1 && clr->anim && --clr->nb_enemy)
	{
		mvprintw(clr->top + 4, COLS / 2, "%d", clr->nb_enemy);
		refresh();
		usleep(1200000);
	}
	mvprintw(clr->top + 4, COLS / 2, " ");
	clr->nb_enemy = 0;
	usleep(clr->pause);
}

void	print_box(t_clr *clr)
{
	int		j;
	int		i;
	int		sleep;

	print_title(clr, 0, 0);
	i = clr->top - 1;
	sleep = clr->anim ? 800000 : 0;
	while (i++ <= clr->bottom - 1)
	{
		write(1, "\a", 1);
		sleep = (4 * sleep) / 5;
		mvprintw(i, clr->border_l, "*");
		mvprintw(i, clr->border_r, "*");
		if (i == clr->top || i == clr->top + 3 || i == clr->bottom)
		{
			j = clr->border_l - 1;
			while (++j <= clr->border_r)
				mvprintw(i, j, "*");
		}
		refresh();
		usleep(sleep);
	}
	refresh();
	if (clr->anim)
		usleep(1000000);
}

void	print_map_ncurses(t_clr *clr, int i, int j, char c)
{
	while (++i < clr->var->y_map)
	{
		move(clr->top + 5 + i, (COLS - clr->var->x_map) / 2 + 1);
		j = -1;
		while (++j < clr->var->x_map)
		{
			if ((c = clr->var->map[i][j]) != '.')
			{
				if ((c == clr->var->player || c == clr->var->player + 32)
					&& ++clr->nb_player)
					attron(COLOR_PAIR(PLAYER));
				else if (++clr->nb_enemy)
					attron(COLOR_PAIR(ENEMY));
			}
			else
				attron(COLOR_PAIR(get_faster(clr->var, i, j, 0)));
			printw("%c", clr->var->map[i][j]);
		}
	}
	print_score(clr);
}
