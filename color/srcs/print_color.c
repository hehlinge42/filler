/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:47:54 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/13 22:30:55 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <unistd.h>
#include "filler.h"

static int		get_color(t_var *var, int o_y, int o_x, int step)
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
			x = o_x - (step - ft_abs(o_y - y));
			if (x >= 0 && x < var->x_map && (c = var->map[y][x]) != '.')
				c == var->player || c == var->player + 32 ? ret[0]++
					: ret[1]++;
			x = o_x + (step - ft_abs(o_y - y));
			if (x >= 0 && x < var->x_map && (c = var->map[y][x]) != '.')
				c == var->player || c == var->player + 32 ? ret[0]++
					: ret[1]++;
		}
	}
	if ((ret[0] && ret[1]) || (!ret[0] && !ret[1]))
		return (NN);
	return (ret[0] ? NP : NE);
}

static void		print_score(t_clr *clr)
{
	attron(COLOR_PAIR(RST));
	mvprintw(clr->top + 1, COLS / 2 - 4, "%s %d", "turn", clr->var->turn++);
	clr->color ? (attron(COLOR_PAIR(NP))) : 0;
	mvprintw(clr->top + 2, clr->border_l + 2, "%s %c % *d"
			, clr->name_player, clr->var->player
			, clr->width - ft_strlen(clr->name_player) - 5, clr->nb_player);
	clr->color ? (attron(COLOR_PAIR(NE))) : 0;
	printw(" %-*d %c %s ", clr->width - ft_strlen(clr->name_enemy) - 5
			, clr->nb_enemy, clr->var->enemy, clr->name_enemy);
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

int				print_box(t_clr *clr)
{
	int		j;
	int		i;
	int		sleep;

	print_title(clr, 0, 0);
	i = clr->top - 1;
	sleep = clr->anim ? 800000 : 0;
	while (i++ <= clr->bottom - 1)
	{
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
	return (1);
}

static void		print_char(t_clr *clr, int i, int j, int c)
{
	if (clr->color)
	{
		if (clr->color == 2)
		{
			if (c == '.')
				attron(COLOR_PAIR(get_color(clr->var, i, j, 0)));
			else if (c == clr->var->player || c == clr->var->player + 32)
				attron(COLOR_PAIR(PLAYER));
			else if (c == clr->var->enemy || c == clr->var->enemy + 32)
				attron(COLOR_PAIR(ENEMY));
		}
		else
		{
			if (c == clr->var->player + 32)
				attron(COLOR_PAIR(NP));
			else if (c == clr->var->enemy + 32)
				attron(COLOR_PAIR(NE));
		}
	}
	clr->symbol && clr->color == 2 ? (c = clr->symbol) : 0;
	addch(c);
	attron(COLOR_PAIR(RST));
}

void			print_map_ncurses(t_clr *clr, int i, int j)
{
	int		c;

	while (++i < clr->var->y_map && (j = -1))
	{
		move(clr->top + 5 + i, (COLS - clr->var->x_map) / 2 + 1);
		while (++j < clr->var->x_map)
		{
			c = clr->var->map[i][j];
			if (c != '.')
			{
				if (c == clr->var->player || c == clr->var->player + 32)
					clr->nb_player++;
				else
					clr->nb_enemy++;
			}
			print_char(clr, i, j, c);
		}
	}
	print_score(clr);
}
