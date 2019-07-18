/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:21:08 by hehlinge          #+#    #+#             */
/*   Updated: 2019/07/11 19:10:07 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdlib.h>
#include <stdio.h>

int		ft_alloc_map(t_var *var)
{
	int		i;
	t_list	*begin_list;

	if (!(var->map = (char **)malloc(sizeof(char *) * var->y_max)))
		return (0);
	ft_bzero(var->map, sizeof(char *) * var->y_max);
	begin_list = ft_lstnew((void *)var->map, sizeof(char *) * var->y_max);
	var->to_free = &begin_list;
	if (!(var->piece = (char **)malloc(sizeof(char *) * var->y_max)))
		return (0);
	ft_bzero(var->piece, sizeof(char *) * var->y_max);
	ft_lstadd(var->to_free,
		ft_lstnew((void *)var->piece, sizeof(char *) * var->y_max));
	i = -1;
	while (++i < var->y_max)
	{
		if (!(var->map[i] = (char *)malloc(sizeof(char) * (var->x_max + 1))))
			return (0);
		ft_bzero(var->map[i], sizeof(char) * (var->x_max + 1));
		ft_lstadd(var->to_free,
			ft_lstnew((void *)var->map[i], sizeof(char) * (var->x_max + 1)));
		if (!(var->piece[i] = (char *)malloc(sizeof(char) * (var->x_max + 1))))
			return (0);
		ft_bzero(var->piece[i], sizeof(char) * (var->x_max + 1));
		ft_lstadd(var->to_free,
			ft_lstnew((void *)var->piece[i], sizeof(char) * (var->x_max + 1)));
	}
	ft_putendl("Map alloc");
	return (1);
}

int		ft_parse_line_map(t_var *var, char *str, int lin)
{
	int		i;

	i = -1;
	while (++i < var->x_max)
	{
		if (str[i] != '.' && str[i] != 'X' && str[i] != 'O'
			&& str[i] != 'x' && str[i] != 'o')
			return (0);
		else if (var->turn == 1 && (str[i] == 'x' || str[i] == 'o'))
			return (0);
		else if (str[i] == 'x')
		{
			if (!(ft_add_point(var, lin, i, 'X')))
				return (0);
		}
		else if (str[i] == 'o')
		{
			if (!(ft_add_point(var, lin, i, 'O')))
				return (0);
		}
		else if (var->turn == 1)
		{
			if (str[i] == 'X' && var->nb_x == 0)
			{
				if (!(ft_init_point(var, lin, i, 'X')))
					return (0);
				var->nb_x++;
			}
			else if (str[i] == 'O' && var->nb_o == 0)
			{
				if (!(ft_init_point(var, lin, i, 'O')))
					return (0);
				var->nb_o++;
			}
			else if ((str[i] == 'X' && var->nb_x > 0)
				|| (str[i] == 'O' && var->nb_o > 0))
			{
				return (0);
			}
		}
	}
	if (str[i])
		return (0);
	ft_strcpy(var->map[lin], str);
	return (1);
}

int		ft_parse_map(t_var *var, char *str)
{
	int		i;

	if (gnl(1, &str, 0) <= 0)
		return (0);
	if (ft_strncmp(str, "    ", ft_strlen("    ")))
		return (0);
	i = -1;
	while (++i < var->x_max)
		if (str[4 + i] != (i % 10 + '0'))
			return (0);
	if (str[4 + i])
		return (0);
	var->turn++;
	i = -1;
	while (++i < var->y_max && gnl(1, &str, 0) > 0)
	{
		ft_printf("i = %d, y_max = %d\n", i, var->y_max);
		if (str[0] != i / 100 + '0' || str[1] != (i % 100) / 10 + '0' || str[2]
			!= i % 10 + '0' || str[3] != ' ' || !(ft_parse_line_map(var, str + 4, i)))
			return (0);
	}
	ft_printf("sortie de boucle\n");
	if (var->turn == 1 && (var->nb_o != 1 || var->nb_x != 1))
		return (0);
	return (1);
}

int		ft_parse_line_plateau(t_var *var, char **str, int off, int res)
{
	if (gnl(1, str, 0) <= 0)
		return (0);
	if (ft_strncmp(*str + off, "Plateau ", ft_strlen("Plateau ")))
		return (0);
	off += ft_strlen("Plateau ");
	while ((*str)[off] >= '0' && (*str)[off] <= '9')
		res = res * 10 + (*str)[off++] - '0';
	if (!res || (var->y_max && res != var->y_max) || (*str)[off++] != ' ')
		return (0);
	var->y_max = res;
	res = 0;
	while ((*str)[off] >= '0' && (*str)[off] <= '9')
		res = res * 10 + (*str)[off++] - '0';
	if (!res || (var->x_max && res != var->x_max)
		|| ft_strcmp((*str) + off, ":"))
		return (0);
	var->x_max = res;
	return (1);
}

int		ft_parse_first_line_piece(t_var *var, char *str, int off, int res)
{
	if (gnl(1, &str, 0) <= 0)
		return (0);
	ft_putstr("gnl = ");
	ft_putendl(str);
	if (ft_strncmp(str + off, "Piece ", ft_strlen("Piece ")))
		return (0);
	off += ft_strlen("Piece ");
	res = 0;
	while (str[off] >= '0' && str[off] <= '9')
		res = res * 10 + str[off++] - '0';
	if (!res || str[off++] != ' ')
		return (0);
	var->y_size_piece = res;
	res = 0;
	while (str[off] >= '0' && str[off] <= '9')
		res = res * 10 + str[off++] - '0';
	if (!res || ft_strcmp(str + off, ":"))
		return (0);
	var->x_size_piece = res;
	return (1);
}

int		ft_parse_piece(t_var *var, char *str)
{
	int		i;
	int		j;

	i = -1;
	while (++i < var->y_size_piece && gnl(1, &str, 0) > 0)
	{
		j = -1;
		while (++j < var->x_size_piece)
		{
			if (str[j] != '.' && str[j] != '*')
				return (0);
		}
		if (str[j])
			return (0);
		ft_strcpy(var->piece[i], str);
	}
	return (1);
}

int		ft_parse_input(t_var *var)
{
	char *str;

	str = NULL;
	if (!(ft_parse_line_plateau(var, &str, 0, 0)))
		return (0);
	if (!(var->map))
		if (!(ft_alloc_map(var)))
			return (0);
	if (!(ft_parse_map(var, str)))
		return (0);
	if (!(ft_parse_first_line_piece(var, str, 0, 0)))
		return (0);
	if (!(ft_parse_piece(var, str)))
		return (0);
	return (1);
}
