/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:30:50 by hehlinge          #+#    #+#             */
/*   Updated: 2019/07/11 19:10:09 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define INIT_EASY_FREE 1
# define ERR_FIRST_LINE 1
# define BAD_MAP 2
# define FULL_MAP 3

# include "../libft/includes/libft.h"

typedef struct	s_var
{
	char	player;
	char	**map;
	char	**piece;
	int		x_max;
	int		y_max;
	int		x_size_piece;
	int		y_size_piece;
	int		x;
	int		y;
	int		exp_pieces;
	int		turn;
	int		nb_x;
	int		nb_o;
	void	**to_free;
}				t_var;

int				gnl(const int fd, char **line, int opt);
int				ft_parse_input(t_var *var);
int				place_piece(void);
void			ft_clear_list(t_gnl **begin_list);
void			*ft_easy_malloc(void ***to_free, int size, int opt);

# endif
