/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 12:36:44 by hehlinge          #+#    #+#             */
/*   Updated: 2019/08/03 12:37:13 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

t_lst	*ft_lstnew(void const *content, size_t content_size)
{
	t_lst	*new_elem;

	if (!(new_elem = (t_lst *)easymalloc(sizeof(t_lst))))
		return (NULL);
	if (!content)
	{
		new_elem->content = NULL;
		new_elem->content_size = 0;
	}
	else
	{
		if (!(new_elem->content = (void *)ft_memalloc(sizeof(void)
			* (content_size + 1))))
			return (NULL);
		ft_memcpy(new_elem->content, content, content_size);
		new_elem->content_size = content_size;
	}
	new_elem->next = NULL;
	new_elem->last = new_elem;
	return (new_elem);
}
