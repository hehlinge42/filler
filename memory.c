/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 11:17:41 by sikpenou          #+#    #+#             */
/*   Updated: 2019/07/10 19:48:55 by sikpenou         ###   ########.fr       */
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	offset;

	offset = 0;
	while (offset < n)
	{
		((char *)dst)[offset] = ((char *)src)[offset];
		offset++;
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	void	*s;
	int		n;

	if (!(n = len))
		return (b);
	s = b;
	while (s - b < n)
	{
		*(unsigned char *)s = (unsigned char)c;
		s++;
	}
	return (b);
}

int		ft_realloc(void **zone, long curr_size, long to_add)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (curr_size))))
		return (0);
	ft_memset(tmp, 0, curr_size);
//	printf("realloc start\nzone : |%s|\ntmp  : |%s|\n", *zone, tmp);
	ft_memcpy(tmp, *zone, curr_size);
//	printf("realloc mid\nzone : |%s|\ntmp  : |%s|\n", *zone, tmp);
	if (*zone)
		free(*zone);
	if (!(*zone = (char *)malloc(sizeof(char) * (curr_size + to_add))))
		return (0);
	ft_memset(*zone, 0, curr_size + to_add);
	ft_memcpy(*zone, tmp, curr_size);
//	printf("realloc end\nzone : |%s|\ntmp  : |%s|\n", *zone, tmp);
	free(tmp);
	fflush(0);
	return (curr_size + to_add);
}
