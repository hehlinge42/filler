/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:02:58 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/21 13:03:49 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "filler.h"
#include "libft.h"

int		set_ncurses(t_clr *clr)
{
	start_color();
	curs_set(0);
	clr->theme == YIN ? init_pair(PLAYER, COLOR_WHITE, COLOR_WHITE)
		: init_pair(PLAYER, COLOR_CYAN, COLOR_CYAN);
	clr->theme == YIN ? init_pair(NP, COLOR_WHITE, COLOR_BLACK)
		: init_pair(NP, COLOR_CYAN, COLOR_BLACK);
	clr->theme == YIN ? init_pair(ENEMY, COLOR_BLACK, COLOR_BLACK)
		: init_pair(ENEMY, COLOR_RED, COLOR_RED);
	clr->theme == YIN ? init_pair(NE, COLOR_WHITE, COLOR_BLACK)
		: init_pair(NE, COLOR_RED, COLOR_BLACK);
	init_pair(NN, COLOR_WHITE, COLOR_BLACK);
	init_pair(RST, COLOR_WHITE, COLOR_BLACK);
	clr->top = ft_max(LINES / 2 - clr->var->y_map / 2 - 3, 10);
	clr->bottom = clr->top + clr->var->y_map + 7;
	clr->width = ft_max(25, clr->var->x_map / 2 + 4);
	clr->border_l = COLS / 2 - clr->width;
	clr->border_r = COLS / 2 + clr->width;
	if (clr->border_l < 0 || clr->border_r > COLS || clr->top < 0
		|| clr->bottom > LINES)
		ft_printf("window too small, please resize (ctrl + c to quit)\n");
	else
		return (print_box(clr));
	return (0);
}

int		get_speed(t_clr *clr, char *arg)
{
	int		ret;
	char	*c_arg;

	ret = 0;
	c_arg = arg;
	if (!arg)
		clr->state = -2;
	else
	{
		ret = ft_atoi(arg);
		ret < 0 ? (ret = 0) : 0;
		if (arg)
			while (*arg)
			{
				if (*arg > 57 || *arg < 48)
					clr->state = -2;
				arg++;
			}
	}
	if (clr->state == -2)
		ft_printf("bad speed: %s\n\r", c_arg);
	return (ret);
}

void	ft_parse_args(char **av, int ac, t_clr *clr)
{
	while (--ac && *(++av) && !clr->state)
	{
		if (!ft_strcmp(*av, "anim"))
			clr->anim = 1;
		else if (!ft_strcmp(*av, "slow") || !ft_strcmp(*av, "medium"))
			clr->pause = **av == 's' ? SLOW : MEDIUM;
		else if (!ft_strcmp(*av, "fast") || (!ft_strcmp(*av, "speed:")))
			clr->pause = **av == 'f' ? FAST : get_speed(clr, *++av);
		else if (!ft_strcmp(*av, "diamond") || !ft_strcmp(*av, "board"))
			clr->symbol = **av == 'd' ? ACS_DIAMOND : ACS_CKBOARD;
		else if (!ft_strcmp(*av, "degree") || !ft_strcmp(*av, "pi"))
			clr->symbol = **av == 'd' ? ACS_DEGREE : ACS_PI;
		else if (!ft_strcmp(*av, "color") || !ft_strcmp(*av, "color_new"))
			clr->color = (*av)[5] ? 1 : 2;
		else if (!ft_strcmp(*av, "yin") || !ft_strcmp(*av, "classic"))
			clr->theme = **av == 'y' ? YIN : CLASSIC;
		else
			clr->state = -1;
	}
	clr->state == -1 ? ft_printf("\n\rbad argument: '%s'\n\n\roptions:\n\r - an"
		"im;\n\r - color, color_new: color the whole board (new for new pieces "
		"only);\n\r - slow, medium, fast, speed: [your speed (microseconds)]: s"
		"et game speed;\n\r - board, degree, diamond set: board symbol (turns o"
		"n color);\n\r - yin, classic: set color themes (yin starts color, turn"
		"s off symbol).", *av) : 0;
}

int		main(int ac, char **av)
{
	t_clr	clr;

	ft_memset(&clr, 0, sizeof(t_clr));
	if (!(clr.var = (t_var *)malloc(sizeof(t_var))))
		return (0);
	ft_memset(clr.var, 0, sizeof(t_var));
	initscr();
	clr.pause = MEDIUM;
	ft_parse_args(av, ac, &clr);
	clr.theme == YIN ? (clr.symbol = 0) : 0;
	clr.symbol ? (clr.color = 2) : 0;
	clr.theme ? (clr.color = 2) : 0;
	if (!clr.state)
		if (!ft_parse_first_line_color(&clr, clr.var, 10, 0))
			if ((clr.state = -1))
				ft_printf("bad input\n\r");
	clr.state ? 0 : refresh();
	clr.state ? 0 : usleep(3000000);
	ac = -1;
	while (clr.map_allocated == 2 && ++ac < clr.var->y_map)
		free(clr.var->map[ac]);
	clr.map_allocated ? free(clr.var->map) : 0;
	free(clr.var);
	endwin();
	return (0);
}
