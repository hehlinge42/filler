/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:28:16 by hehlinge          #+#    #+#             */
/*   Updated: 2019/08/20 18:23:43 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int		ft_parse_first_line(t_var *var)
{
	int		pos;
	char	*line;

	if (!(get_next_line(0, &line)))
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
	ft_free((void **)&line);
	return (1);
}

int		ft_exit(int opt)
{
	if (opt == ERR_FIRST_LINE)
		printf("exit - bad first line\n");
	else if (opt == BAD_MAP)
		printf("exit - bad map\n");
	else if (opt == FULL_MAP)
		printf("0 0\n");
	return (1);
}

int		ft_init_var(t_var *var)
{
	ft_memset(var, 0, sizeof(*var));
	if ((var->pts_player = (t_lst **)easymalloc(sizeof(*var->pts_player)))
		&& (var->pts_neutral = (t_lst **)easymalloc(sizeof(*var->pts_neutral))))
		return (1);
	return (0);
}

int		main(void)
{
	t_var	var;
	int fd;
	
	fd = open("/Users/Hugo/Desktop/42/filler/debug.txt", O_WRONLY|O_APPEND|O_CREAT, 0644);
	if (ft_init_var(&var))
	{
		if (!ft_parse_first_line(&var))
			return (ft_exit(ERR_FIRST_LINE));
		while (1)
		{
			if (!ft_parse_input(&var))
				return (ft_exit(BAD_MAP));
			ft_get_points(&var);
		//	print_debug(var, "1");
			ft_algo(&var);
			printf("%d %d\n", var.y_pos, var.x_pos);
			dprintf(fd, "%d %d\n", var.x_pos, var.y_pos);
		}
	}
	return (1);
}
