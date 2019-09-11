/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:30:50 by hehlinge          #+#    #+#             */
/*   Updated: 2019/09/11 16:36:09 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define ERR_FIRST_LINE 1
# define BAD_MAP 2

# include "../libft/includes/libft.h"

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
	int				fd;
}					t_var;

typedef struct		s_clr
{
	char			*name_player;
	char			*name_enemy;
	int				nb_player;
	int				nb_enemy;
	int				pause;
	t_var			*var;
}					t_clr;


int					ft_parse_input(t_var *var);
int					ft_parse_input_color(t_var *var, int nb);
int					ft_init_neutral_points(t_var *var, int i, int j);
void				ft_get_points(t_var *var, t_point *point, t_lst *elem
	, t_lst *tmp);
int					place_piece(void);
int					ft_init_point(t_var *var, int x, int y, char letter);
int					abs(int n);
int					ft_exit(int opt);
void				print_debug(t_var var, char *opt);
void				ft_algo(t_var *var, int count, int opt);
void				print_point(t_point *point, int fd);
void				print_points(t_var var, char *opt);
void				print_map(t_var var, int opt, int nocolor);
void				print_available(t_var var);
void				print_piece(t_var var);
int					ft_get_dist_enemy(t_point *point, t_var *var
	, int square_nb);

#endif
