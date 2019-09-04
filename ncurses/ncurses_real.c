
#include <curses.h>
#include <unistd.h>
#include "filler.h"
#include "libft.h"

#define PLAYER 1
#define NP 2
#define ENEMY 3
#define NE 4
#define NN 5

// point est la ref, le point a convertir, et tmp est le point actuel pour
// lequel on regarde si il fait basculer, on le recupere dans une liste
void	ft_dist(t_point *point, t_point *tmp, t_var *var)
{
	int		test;
	int		x;
	int		y;

	x = point->x;
	y = point->y;
	point = tmp;
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
					ft_dist(&tmp, &point, var);
			}
			else
			{
				tmp.x = point.x - square_nb;
				ft_dist(&tmp, &point, var);
				tmp.x = point.x + square_nb;
				ft_dist(&tmp, &point, var);
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

void	print_stuff(int ctr)
{
	attron(COLOR_PAIR((0 + ctr) % 4 + 1));
	printw("test %d\n", ctr);
	attron(COLOR_PAIR((1 + ctr) % 4 + 1));
	printw("test %d\n", ctr);
	attron(COLOR_PAIR((2 + ctr) % 4 + 1));
	printw("test %d\n", ctr);
	attron(COLOR_PAIR((3 + ctr) % 4 + 1));
	printw("test %d\n", ctr);
	refresh();
	usleep(700000);
	move(0, 0);
}

void	print_map_ncurses(t_var *var)
{
	int		i;
	int		j;
	char	c;

	i = -1;
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
				attron(COLOR_PAIR(ft_get_owner(var, i, j)));
			printw("%c", var->map[i][j]);
		}
		printw("\n");
	}
	refresh();
	usleep(100000);
	move(0, 0);
}

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

int		main(void)
{
	WINDOW *win;
	t_var	*var;

	if (!(var = (t_var *)easymalloc(sizeof(*var))))
		return (0);
	initscr();
	start_color();
	init_pair(PLAYER, COLOR_CYAN, COLOR_CYAN);
	init_pair(NP, COLOR_CYAN, COLOR_BLACK);
	init_pair(ENEMY, COLOR_RED, COLOR_RED);
	init_pair(NE, COLOR_RED, COLOR_BLACK);
	init_pair(NN, COLOR_WHITE, COLOR_WHITE);
	win = newwin(var->y_map + 2, 100 +  var->x_map + 2, 1, 1);
	ft_parse_first_line(var);
	while (ft_parse_input(var))
		print_map_ncurses(var);
	endwin();
}
