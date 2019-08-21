/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:39:05 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/21 18:52:09 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_print_list(t_lst *begin_list, int opt)
{
	int		i;

	i = 0;
	if (!begin_list)
	{
		ft_putstr("--\nempty list\n--\n");
		return (0);
	}
	if (opt == 2)
		ft_putstr("\n--\nlist start\n--\n");
	while (begin_list)
	{
		if (opt == 2)
		{
			ft_putstr("pos ");
			ft_putnbr(i++);
			ft_putstr(": '");
		}
		ft_putstr(begin_list->content);
		begin_list = begin_list->next;
		if (opt != 0)
			ft_putstr(opt == 2 ? "'\n" : "\n");
	}
	ft_putstr(opt == 2 ? "--\nlist end\n--\n\n" : "\n");
	return (0);
}