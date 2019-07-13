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

	ft_putendl("oui");
	if (!(var->map = (char **)ft_easy_malloc(&(var->to_free),
		var->y_max * sizeof(char *), 0)))
		return (0);
	ft_putendl("non");
	i = -1;
	while (++i < var->y_max)
	{
		if (!(var->map[i] = (char *)ft_easy_malloc(&(var->to_free),
			var->x_max * sizeof(char), 0)))
			return (0);
	}
	return (1);
}

int		ft_parse_line_map(t_var *var, char *str)
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
		else if (var->turn == 1)
		{
			if (str[i] == 'X')
				var->nb_x++;
			else if (str[i] == 'O')
				var->nb_o++;
		}
	}
	if (str[i] || var->nb_o != 1 || var->nb_x != 1)
		return (0);
	return (1);
}

int		ft_parse_map(t_var *var, char *str)
{
	int		off;
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
		off = 0;
		if (str[0] != i / 100 - '0' || str[1] != (i % 100) / 10 - '0' || str[2]
			!= i % 10 - '0' || str[3] != ' ' || !(ft_parse_line_map(var, str + 4)))
			return (0);
	}
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
	if (!(var->map))
		if (!(ft_alloc_map(var)))
			return (0);
	return (1);
}

int		ft_parse_piece(t_var *var, char *str, int off, int res)
{
	if (gnl(1, &str, 0) <= 0)
		return (0);
	if (ft_strncmp(str + off, "Piece ", ft_strlen("Piece ")))
		return (0);
	off += ft_strlen("Piece ");
	res = 0;
	while (str[off] >= '0' && str[off] <= '9')
		res = res * 10 + str[off++] - '0';
	if (!res || str[off++] != ' ')
		return (0);
	var->x_size_piece = res;
	res = 0;
	while (str[off] >= '0' && str[off] <= '9')
		res = res * 10 + str[off++] - '0';
	if (!res || str[off])
		return (0);
	var->y_size_piece = res;
	return (1);
}

int		ft_parse_input(t_var *var)
{
	char *str;

	str = NULL;
	if (!(ft_easy_malloc(&(var->to_free), 0, INIT_EASY_FREE)))
		return (0);
	if (!(ft_parse_line_plateau(var, &str, 0, 0)))
		return (0);
	if (!(ft_parse_map(var, str)))
		return (0);
	printf("ft_parse_map ok\n");
	return (1);
	if (!(ft_parse_piece(var, str, 0, 0)))
		return (0);
	return (1);
}
