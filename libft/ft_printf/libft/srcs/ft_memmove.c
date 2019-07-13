/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:17:32 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/23 11:30:18 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*source;
	char	*lasts;
	char	*lastd;

	dest = (char *)dst;
	source = (char *)src;
	if (dest < source)
		ft_memcpy(dest, source, len);
	else
	{
		lasts = source + len - 1;
		lastd = dest + len - 1;
		while (len--)
			*lastd-- = *lasts--;
	}
	return (void *)dest;
}
