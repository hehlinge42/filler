/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:24:57 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/23 11:30:21 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (haystack[i + j] && needle[j] && i + j < len)
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] != needle[j])
			i++;
		while (haystack[i + j] && needle[j] && haystack[i + j] ==
			needle[j] && i + j < len)
			j++;
		if (haystack[i + j] && needle[j] && j < len)
			i++;
	}
	if (!(needle[j]))
		return ((char *)haystack + i);
	return (NULL);
}
