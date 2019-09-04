/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:04:53 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/03 16:24:11 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
**	implement an EXIT macro, and if (EXIT) ft free exits instead of returning
*/

struct									s_gc_list
{
	unsigned	len;
	t_lst		*first;
	t_lst		*last;
}				g_to_free;

__attribute__((constructor)) void		begin(void)
{
	g_to_free.len = 0;
	g_to_free.first = NULL;
	g_to_free.last = NULL;
}

__attribute__((destructor)) void 		end(void)
{
	t_lst	*elem;
	t_lst	*tmp;

	elem = g_to_free.first;
	while (elem)
	{
		g_to_free.len--;
		tmp = elem;
		elem = elem->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

/*
** this function should take a char *opt, use ft_strstr to compare the
** argument to "len", "first" and "last", print relevant data, and still
** return the length
*/
unsigned								get_gc_data(void)
{
	return (g_to_free.len);
}

void									ft_free(void **match)
{
	t_lst		*elem;
	t_lst		*tmp;

	g_to_free.len--;
	elem = g_to_free.first;
	if (match && elem->content == match)
	{
		g_to_free.first = elem->next;
		if (g_to_free.last == elem)
			g_to_free.last = NULL;
		free(elem->content);
		free(elem);
		return ;
	}
	while (match && elem->next && elem->next->content != match)
		elem = elem->next;
	if (match && elem->next)
	{
		tmp = elem->next;
		elem->next = elem->next->next;
		if (g_to_free.last == tmp)
			g_to_free.last = elem;
		free(tmp->content);
		free(tmp);
	}
}

void									*easymalloc(int size)
{
	t_lst	*new_free;

	if (!(new_free = (t_lst *)malloc(sizeof(*new_free))))
		return (0);
	if ((new_free->content = (void *)malloc(size)))
		ft_memset(new_free->content, 0, size);
	new_free->next = NULL;
	if (g_to_free.last)
		g_to_free.last->next = new_free;
	else
		g_to_free.first = new_free;
	g_to_free.last = new_free;
	g_to_free.len++;
	return (new_free->content);
}
