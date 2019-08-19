/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:29:15 by sikpenou          #+#    #+#             */
/*   Updated: 2019/07/30 17:35:17 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

int			ft_print_lst(t_lst *begin_list, int opt)
{
	int		i;

	i = 0;
	if (!begin_list)
		return (printf("--\nempty list\n--\n"));
	if (opt == 2)
		printf("\n--\nlist start\n--\n");
	while (begin_list)
	{
		if (opt == 2)
		{
			printf("pos %d: '", i);
			i++;
		}
		printf("%s", begin_list->content);
		begin_list = begin_list->next;
		if (opt != 0)
			printf(opt == 2 ? "'\n" : "\n");
	}
	printf(opt == 2 ? "--\nlist end\n--\n" : "");
	return (printf("\n"));
}

void	ft_memmove(void *dst, void *src, long long int len)
{
	long long int		pos;

	pos = 0;
	if (src < dst)
	{
		while (len)
		{
			*(unsigned char *)(dst + len - 1) = *(unsigned char *)(src + len
				- 1);
			len--;
		}
	}
	else
	{
		while (pos < len)
		{
			*(unsigned char *)(dst + pos) = *(unsigned char *)(src + pos);
			pos++;
		}
	}
}

t_lst		*ft_lstnew(void *content, long long int content_size)
{
	t_lst		*new;

	if (!(new = (t_lst *)easymalloc(sizeof(t_lst))))
		return (0);
	new->next = NULL;
	if (content && !(new->content = (void *)easymalloc(content_size)))
		return (0);
	else
	{
		new->content = NULL;
		new->content_size = 0;
		return (new);
	}
	ft_memmove(new->content, content, content_size);
	new->content_size = content_size;
	return (new);
}

int					ft_lstadd(t_lst **begin_list, t_lst *new_elem)
{
	if (begin_list)
		new_elem->next = *begin_list;
	*begin_list = new_elem;
	return (1);
}
