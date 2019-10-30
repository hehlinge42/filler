/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 21:10:00 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/11 15:52:48 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f) (char))
{
	char			*chain_to;
	const char		*chain_from;

	if (!s || !f)
		return (NULL);
	if (!(chain_from = s))
		return (NULL);
	if (!(chain_to = (char *)ft_memalloc(ft_strlen((char *)s) + 1)))
		return (NULL);
	while (*chain_from)
	{
		chain_to[chain_from - s] = (*f)(*chain_from);
		chain_from++;
	}
	return (chain_to);
}
