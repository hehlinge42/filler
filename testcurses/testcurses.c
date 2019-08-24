
#include <curses.h>
#include <unistd.h>

/*
int		build_attribs(t_var var, char *owners, WINDOW *win)
{
	int			y;
	int			x;
	int			attr;

	y = -1;
	while (++y < var.y_map)
	{
		x = -1;
		while (++x < var.x_map)
		{
			var.map[y][x] == '.' ? (attr = map[x * y + x]) : (attr = map[y][x]);
			attron(COLOR_PAIR(attr));
			printw(map[y][x]);
			attroff(attr);
		}
		printw("\n");
	}
	refresh();
	usleep(300000);
}

int		get_owner(t_var var, WINDOW *win)
{
	t_lst		elem;
	int			size;
	char		*owners;

	size = var.y_map * var.x_map;
	if (!(map = (struct s_map)easymalloc(sizeof(struct s_map) * size + 1)))
		return (0);
	map[size] = 0;
	elem = var.pts_neutral;
	while (elem)
	{
		map[elem->content->x * elem->content->y] = elem->content->owner + 32;
		elem = elem->next;
	}
	build_attribs(var, owners, win);
}

//pseudo main filler utilisant ncurses
int		main(int ac, char **av)
{
	WINDOW		win;
	t_var		var;

	init_var(var);
	initscr();
	win = newwin(var.y_map, var.x_map + 1, 0, 0);
	start_color();
	init_pair(var.player, COLOR_CYAN, COLOR_CYAN);
	init_pair(var.player + 32, COLOR_CYAN, COLOR_BLACK);
	init_pair(var.enemy, COLOR_RED, COLOR_RED);
	init_pair(var.enemy + 32, COLOR_RED, COLOR_BLACK);
	while (1)
	{
		parser();
		algo();
		get_owner(var, win);
	}
	endwin();
}
*/

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

int		main(int ac, char **av)
{
	WINDOW *win;
	int		ctr;

	initscr();
	start_color();
	win = newwin(10, 10, 0, 0);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_CYAN);
	ctr = -1;
	while (++ctr < 4)
		print_stuff(ctr);
	endwin();
}
