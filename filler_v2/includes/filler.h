/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:30:50 by hehlinge          #+#    #+#             */
/*   Updated: 2019/08/03 15:19:37 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define ERR_FIRST_LINE 1
# define BAD_MAP 2
# define FULL_MAP 3

#include "libft.h"

#include <stdio.h>
typedef struct		s_point
{
	int				x;
	int				y;
	char			owner;
	int				x_owner;
	int				y_owner;
	int				dist;
}					t_point;

typedef struct		s_var
{
	char			player;
	int				x_map;
	int				y_map;
	int				turn;
	int				x_piece;
	int				y_piece;
	int				x_pos;
	int				y_pos;
	int				exp_pieces;
	int				nb_x;
	int				nb_o;
	char			**map;
	char			**piece;
	t_lst			**points_x;
	t_lst			**points_o;
	t_lst			**points_n;
}					t_var;

# define PRINTENV printf("%s -- %s -- line %d\n", __FILE__, __func__, __LINE__); fflush(0);

int				ft_parse_input(t_var *var);
int				ft_get_points(t_var *var);
int				place_piece(void);
int				ft_init_point(t_var *var, int x, int y, char letter);
int				abs(int n);
void			print_debug(t_var var, char *opt);

# endif
