/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 14:13:27 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/08 11:26:48 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*s1_cpy;
	char	*str_cpy;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (!(str = (char*)easymalloc(sizeof(*str) * (len + 1))))
		return (NULL);
	s1_cpy = (char *)s1;
	str_cpy = str;
	while (*s1_cpy)
		*str_cpy++ = *s1_cpy++;
	return (str);
}
