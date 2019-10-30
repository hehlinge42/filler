/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:30:50 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/13 22:56:45 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define ERR_FIRST_LINE 1
# define BAD_MAP 2
# define PLAYER 1
# define NP 2
# define ENEMY 3
# define NE 4
# define NN 5
# define RST 6
# define SLOW 200000
# define MEDIUM 90000
# define FAST 35000
# define YIN 1
# define CLASSIC 2
# include "libft.h"

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
	int				enemy_is_playing;
	char			**map;
	char			**tmp;
	char			**piece;
	t_lst			**pts_player;
	t_lst			**pts_neutral;
}					t_var;

typedef struct		s_clr
{
	int				nb_player;
	int				nb_enemy;
	int				pause;
	int				anim;
	int				symbol;
	int				color;
	int				theme;
	int				state;
	int				map_allocated;
	int				width;
	int				top;
	int				center_line;
	int				bottom;
	int				border_l;
	int				center_col;
	int				border_r;
	char			*name_player;
	char			*name_enemy;
	t_var			*var;
}					t_clr;

int					ft_parse_input(t_var *var);
int					ft_init_neutral_points(t_var *var, int i, int j);
void				ft_get_points(t_var *var, t_point *point, t_lst *elem
	, t_lst *tmp);
int					ft_get_dist_enemy(t_point *point, t_var *var
	, int square_nb);
int					place_piece(void);
int					ft_init_point(t_var *var, int x, int y, char letter);
int					ft_exit(int opt);
void				ft_algo(t_var *var, int count, int opt);
int					ft_parse_input_color(t_var *var);
int					ft_parse_first_line_color(t_clr *clr, t_var *var, int pos
	, int stop);
int					set_ncurses(t_clr *clr);
int					print_box(t_clr *clr);
void				print_title(t_clr *clr, int sleep, int start);
void				print_map_ncurses(t_clr *clr, int i, int j);
void				print_debug(t_var var, char *opt);
void				print_point(t_point *point, int fd);
void				print_points(t_var var, char *opt);
void				print_map(t_var var, int opt, int nocolor);
void				print_available(t_var var);
void				print_piece(t_var var);

#endif
