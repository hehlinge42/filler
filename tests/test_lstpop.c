/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstpop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:32:42 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/31 15:04:34 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include <stdio.h>

int		main(void)
{
	t_lst	**begin;
	t_lst	*elem;
	t_lst	*tmp;
	char	content[2];
	int		ctr;

	ctr = -1;
	content[1] = 0;
	while (++ctr < 5)
	{
		content[0] = ctr + 48;
		ft_lstadd_new(begin, content, 2);
	}
	ft_lstprint(*begin, 2);
	ctr = -1;
	elem = *begin;
	while (++ctr < 5)
	{
		if (ctr == 0 || ctr == 3 || ctr == 4)
		{
			tmp = elem;
			elem = elem->next;
			ft_lstpop(begin, (void **)tmp, 0);
			ft_lstprint(*begin, 2);
			printf("tmp: %s\n", tmp->content);
		}
		else
			elem = elem->next;
	}
}
