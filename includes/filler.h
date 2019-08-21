/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:30:50 by hehlinge          #+#    #+#             */
/*   Updated: 2019/08/20 15:48:03 by sikpenou         ###   ########.fr       */
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
	int				available;
}					t_point;

typedef struct		s_var
{
	char			player;
	char			enemy;
	int				x_map;
	int				y_map;
	int				turn;
	int				x_piece;
	int				y_piece;
	int				x_pos;
	int				y_pos;
	char			**map;
	char			**tmp;
	char			**piece;
	t_lst			**pts_player;
	t_lst			**pts_neutral;
}					t_var;

# define PRINTENV printf("%s -- %s -- line %d\n", __FILE__, __func__, __LINE__); fflush(0);

int				ft_parse_input(t_var *var);
int				ft_get_points(t_var *var);
int				place_piece(void);
int				ft_init_point(t_var *var, int x, int y, char letter);
int				abs(int n);
int				is_available(t_var var, int o_x, int o_y);
void			print_debug(t_var var, char *opt);
void			ft_algo(t_var *var);
t_point			*ft_new_point(int x, int y, char c);

# endif
