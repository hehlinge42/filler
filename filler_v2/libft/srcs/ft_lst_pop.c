/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 19:12:17 by sikpenou          #+#    #+#             */
/*   Updated: 2019/07/30 19:28:19 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_pop(t_lst **begin, void **match, int pos)
{
	t_lst		*elem;
	t_lst		*tmp;

	elem = *begin;
	while (elem)
	{
		if (elem->content == match)
		{
			if (elem = *begin)
				*begin = elem->next;
			else
				tmp->next = elem->next;
			ft_free(elem->content);
			ft_free(elem);
			return ;
		}
		tmp = elem;
		elem = elem->next;
	}
}
