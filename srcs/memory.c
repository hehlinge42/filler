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

#include "libftprintf.h"
#include <stdlib.h>

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

int		ft_realloc(void **zone, long curr_size, long to_add)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (curr_size))))
		return (0);
	ft_memset(tmp, 0, curr_size);
	ft_memcpy(tmp, *zone, curr_size);
	if (*zone)
		free(*zone);
	if (!(*zone = (char *)malloc(sizeof(char) * (curr_size + to_add))))
		return (0);
	ft_memset(*zone, 0, curr_size + to_add);
	ft_memcpy(*zone, tmp, curr_size);
	free(tmp);
	return (curr_size + to_add);
}

int		ft_easy_free(void **to_free)
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
	return (0);
}

int		ft_easy_malloc(void	**ptr, void	**to_free, int size, int opt)
{
	if (opt == -1)
	{
		if (!(to_free[0] = (void *)malloc(sizeof(void *) * 2)))
			return (0);
		to_free[0] = (void *)1;
		return (1);
	}
	if (!(to_free[(to_free[0])++] = (void *)malloc(sizeof(void *) * (size + 1))))
		return (ft_easy_free(to_free));
	if (!(ft_realloc(to_free, (long)to_free[0] + (long)1, 1)))
		return (ft_easy_free(to_free));
	return (1);
}
