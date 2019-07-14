/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 11:17:41 by sikpenou          #+#    #+#             */
/*   Updated: 2019/07/11 19:35:45 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_clear_list(t_gnl **begin_list)
{
	t_gnl *tmp;

	if (!(*begin_list))
		return ;
	while (*begin_list)
	{
		tmp = (*begin_list)->next;
		free(*begin_list);
		*begin_list = tmp;
	}
}

void	*ft_stralloc(char *str)
{
	char	*newzone;
	int		size;

	if (!str)
		return (NULL);
	size = ft_strlen((const char *)str);
	if (!(newzone = (char *)malloc(size)))
		return (NULL);
	ft_memcpy(newzone, str, size);
	newzone[size] = 0;
	return (newzone);
}

int		ft_realloc(void ***zone, long curr_size, long to_add)
{
	void	**tmp;
	int		size;

	if (!(tmp = (void **)malloc(sizeof(void *) * curr_size)))
		return (0);
	ft_memset(tmp, 0, curr_size * sizeof(void *));
	size = (int)(*zone[0]);
	ft_putnbr(size);
	if (*zone)
		free(*zone);
	zone = NULL;
	if (!(*zone = (void **)malloc((curr_size + to_add) * sizeof(void *))))
		return (0);
	ft_putendl("coucou2");
	ft_memset(*zone, 0, (curr_size + to_add) * sizeof(void *));
	ft_memcpy(*zone, tmp, curr_size * sizeof(void *));
	free(tmp);
	return (curr_size + to_add);
}

void	*ft_easy_free(void **to_free)
{
	int		size;

	size = (int)to_free[0];
	while (--size)
	{
		if (to_free[size])
			free(to_free[size]);
	}
	if (to_free)
		free(to_free);
	return (NULL);
}

void	*ft_easy_malloc(void ***to_free, int size, int opt)
{
	void	*ptr;

	if (opt == 1)
	{
		if (!(*to_free = (void **)malloc(sizeof(void *))))
			return (NULL);
		*to_free[0] = (void *)1;
		return ((void *)to_free);
	}
	if (!(ptr = (void *)malloc(size + 1)))
		return (ft_easy_free(*to_free));
	ft_bzero(ptr, size + 1);
	ft_putendl("malloc de ptr");
	if (!(ft_realloc(to_free,
		((long)to_free[0] + (long)1), (long)1)))
		return (ft_easy_free(*to_free));
	ft_putendl("realloc de to_free");
	to_free[(int)(to_free[0])++] = ptr;
	return (ptr);
}
