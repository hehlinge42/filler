
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

int			ft_parse_first_line(t_var *var)
{
	int		pos;
	char	*line;

	while (get_next_line(0, &line) && ft_strncmp(line, "$$$", 3))
		if (!line)
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

void	print_map_ncurses(t_var *var, int i, int j, char c)
{
	while (++i < var->y_map)
	{
		j = -1;
		while (++j < var->x_map)
		{
			if ((c = var->map[i][j]) != '.')
			{
				if (c == var->player || c == var->player + 32)
					attron(COLOR_PAIR(PLAYER));
				else
					attron(COLOR_PAIR(ENEMY));
			}
			else
				attron(COLOR_PAIR(get_faster(var, i, j, 0)));
			printw("%c", var->map[i][j]);
		}
		printw("\n");
	}
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
	init_pair(NN, COLOR_WHITE, COLOR_WHITE);
	init_pair(RST, COLOR_WHITE, COLOR_BLACK);
}

int		main(void)
{
	t_var	*var;

	if (!(var = (t_var *)easymalloc(sizeof(*var))))
		return (0);
	var->fd = open("debug.txt", O_WRONLY | O_CREAT | O_TRUNC, 777);
	set_ncurses();
	newwin(var->y_map + 5, var->x_map + 5, 1, 1);
	ft_parse_first_line(var);
	while (ft_parse_input(var))
	{
		attron(COLOR_PAIR(RST));
		printw("turn %d\n", var->turn);
		print_map_ncurses(var, -1, -1, 0);
		refresh();
		usleep(100000);
		move(0, 0);
	}
	usleep(500000);
	endwin();
	close(var->fd);
}

/*
void	ft_dist(int y, int x, t_point *point, t_var *var)
{
	int		test;

	if (x >= 0 && y >= 0 && x < var->x_map && y < var->y_map
		&& var->map[y][x] != '.' && (test = abs(point->x - x)
		+ abs(point->y - y)) <= point->dist)
	{
		if (test == point->dist && var->map[y][x] != point->owner
			&& var->map[y][x] - 32 != point->owner)
			point->owner = '?';
		else
		{
			point->x_owner = x;
			point->y_owner = y;
			point->dist = test;
			if (var->map[y][x] == var->enemy
				|| var->map[y][x] == var->enemy + 32)
				point->owner = var->enemy;
			else if (var->map[y][x] == var->player
				|| var->map[y][x] == var->player + 32)
				point->owner = var->player;
		}
	}
}

char	ft_get_owner(t_var *var, int y, int x)
{
	int			square_nb;
	t_point		tmp;
	t_point		point;

	point.y = y;
	point.x = x;
	square_nb = 1;
	ft_memset(&tmp, 0, sizeof(tmp));
	point.dist = (var->x_map >= var->y_map) ? var->x_map : var->y_map;
	while (point.dist >= square_nb)
	{
		tmp.y = point.y - square_nb - 1;
		tmp.x = point.x - square_nb - 1;
		while (++(tmp.y) <= point.y + square_nb)
		{
			if (tmp.y == point.y - square_nb
				|| tmp.y == point.y  + square_nb)
			{
				tmp.x = point.x - square_nb - 1;
				while (++(tmp.x) <= point.x  + square_nb)
					ft_dist(tmp.y, tmp.x, &point, var);
			}
			else
			{
				tmp.x = point.x - square_nb;
				ft_dist(tmp.y, tmp.x, &point, var);
				tmp.x = point.x + square_nb;
				ft_dist(tmp.y, tmp.x, &point, var);
			}
		}
		square_nb++;
	}
	if (point.owner == var->player || point.owner == var->player + 32)
		return NP;
	else if (point.owner == var->enemy || point.owner == var->enemy + 32)
		return NE;
	return NN;
}

void	quick_print(t_var var)
{
	int		i;

	dprintf(var.fd, "  ");
	i = -1;
	while (++i < var.x_map)
		dprintf(var.fd, "%d", i % 10);
	dprintf(var.fd, "\n");
	i = -1;
	while (++i < var.y_map)
		dprintf(var.fd, "%d %s\n", i, var.map[i]);
	dprintf(var.fd, "\n");
}
*/

