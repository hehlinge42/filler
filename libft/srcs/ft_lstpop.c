/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 19:12:17 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/31 15:01:29 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop(t_lst **begin, void **match, int opt)
{
	t_lst		*elem;
	t_lst		*tmp;

	elem = *begin;
	while (elem)
	{
		if ((void **)elem == match || elem->content == match)
		{
			if (elem == *begin)
				*begin = elem->next;
			else
				tmp->next = elem->next;
			if (opt)
			{
				ft_free((void **)elem->content);
				ft_free((void **)elem);
			}
			return ;
		}
		tmp = elem;
		elem = elem->next;
	}
}
