/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:25:54 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/23 11:30:21 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (haystack[i + j] && needle[j])
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] != needle[j])
			i++;
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (haystack[i + j] && needle[j])
			i++;
	}
	if (!(needle[j]))
		return ((char *)haystack + i);
	return (NULL);
}
