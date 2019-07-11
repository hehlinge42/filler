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

int		ft_parse_first_line(t_var *var)
{
	char	*str;
	char	*tmp;
	char	ret;

	ret = 1;
	str = 0;
	if (gnl(1, &str, 0) <= 0)
		ret = 0;
	tmp = str;
	if (ft_strncmp(str, "$$$ exec p", ft_strlen("$$$ exec p")))
		ret = 0;
	str += ft_strlen("$$$ exec p");
	if (!((var->player = str[0]) == '1' || str[0] == '2'))
		ret = 0;
	str++;
	if (ft_strncmp(str, "p1 : [players/", ft_strlen("p1 : [players/")))
		ret = 0;
	str += ft_strlen("p1 : [players/");
	if (ft_strcmp(str, "hehlinge.filler]"))
		ret = 0;
	if (tmp)
		free(tmp);
	return (ret);
}

int		ft_parse_second_line(t_var *var, char *str)
{
	char	ret;
	int		off;
	int		i;

	if (gnl(1, &str, 0) <= 0)
		ret = 0;
	if (ft_strncmp(str, "    ", ft_strlen("    ")))
		ret = 0;
	i = -1;
	while (++i < var->x_max)
		if (str[4 + i] != (i % 10 + '0'))
			ret = 0;
	if (str[4 + i])
		ret = 0;
	var->turn++;
	i = -1;
	while (gnl(1, &str, 0) > 0 && ++i < var->y_max)
	{
		off = 0;
		if (str[0] != i / 100 - 48 || str[1] != (i % 100) / 10 - 48 || str[2]
			!= i % 10 - 48 || str[3] != ' ' || !(check_line(str + 4, var))
			ret = 0;

	}
}

int		ft_parse_input(t_var *var)
{
	char	*str;
	char	ret;
	int		res;
	int		off;

	ret = 1;
	str = 0;
	off = 0;
	if (gnl(1, &str, 0) <= 0)
		ret = 0;
	if (ft_strncmp(str + off, "Plateau ", ft_strlen("Plateau ")))
		ret = 0;
	off += ft_strlen("Plateau ");
	res = 0;
	while (str[off] >= '0' && str[off] <= '9')
		res = res * 10 + str[off++] - '0';
	if (!res && !var->y_max || (var->y_max && res != var->y_max) || str[off++] != ' ')
		ret = 0;
	var->x_max = res;
	res = 0;
	while (str[off] >= '0' && str[off] <= '9')
		res = res * 10 + str[off++] - '0';
	if (!res && !var->x_max || (var->x_max && res != var->x_max) || ft_strcmp(str + off, ":"))
		ret = 0;
	var->x_max = res;
	
	return (!ret ? 0 : parse_second_line(var, str));
}
