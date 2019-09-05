
#include <curses.h>
#include <unistd.h>

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
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(20, COLOR_CYAN, COLOR_BLACK);
	init_pair(30, COLOR_BLACK, COLOR_CYAN);
	ctr = 1;
	attron(COLOR_PAIR(ctr));
	printw("test %d\n", ctr);
	ctr = 10;
	attron(COLOR_PAIR(ctr));
	printw("test %d\n", ctr);
	ctr = 20;
	attron(COLOR_PAIR(ctr));
	printw("test %d\n", ctr);
	ctr = 30;
	attron(COLOR_PAIR(ctr));
	printw("test %d\n", ctr);
	refresh();
	usleep(700000);
	endwin();
}
