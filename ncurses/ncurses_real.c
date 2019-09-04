
#include <curses.h>
#include <unistd.h>
#include "filler.h"
#include "libft.h"

#define PLAYER 1
#define NP 2
#define ENEMY 3
#define NE 4
#define NN 5

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

void	print_map_ncurses(t_var var)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (++i < var.y_map)
	{
		j = -1;
		while (++j < var.x_map)
		{
			if ((c = var.map[i][j]) != '.')
			{
				if (c == var.player || c == var.player + 32)
					attron(COLOR_PAIR(PLAYER));
				else
					attron(COLOR_PAIR(ENEMY));
			}
			else
				attron(COLOR_PAIR(NN));
//				attron(COLOR_PAIR(get_owner(var, i, j)));
			printw("%c", var.map[i][j]);
		}
		printw("\n");
	}
	refresh();
	usleep(300000);
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
	init_pair(NN, COLOR_WHITE, COLOR_BLACK);
	win = newwin(var->y_map + 2, 100 +  var->x_map + 2, 1, 1);
	ft_parse_first_line(var);
	while (ft_parse_input(var))
		print_map_ncurses(*var);
	endwin();
}
