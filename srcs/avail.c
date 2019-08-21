/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avail.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:44:50 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/21 17:26:44 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h" 

int			is_available(t_var var, int o_x, int o_y)
{
	int		count;
	int		x;
	int		y;

	count = 0;
	y = 0;
	while (count < 2 && y < var.y_piece && y + o_y < var.y_map)
	{
		x = 0;
		while (count < 2 && x < var.x_piece && x + o_x < var.x_map)
		{
			if (var.piece[y][x] != '.' && (x + o_x >= var.x_map || y + o_y
					>= var.y_map || var.map[o_y + y][o_x + x] == var.enemy
						|| var.map[o_y + y][o_x + x] == var.enemy + 32))
				count = 2;
			else if (var.piece[y][x] == '*'
				&& (var.map[o_y + y][o_x + x] == var.player
					|| var.map[o_y + y][o_x + x] == var.player + 32))
				count++;
			x++;
		}
		y++;
	}
	if (x + o_x >= var.x_map || y + o_y >= var.y_map)
		count = 2;
	return (count == 1 ? 1 : 0);
}
