/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:50:03 by sikpenou          #+#    #+#             */
/*   Updated: 2019/04/11 19:12:17 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	void	*s;

	if (!len)
		return (b);
	s = b;
	while ((size_t)(s - b) < len)
	{
		*(unsigned char *)s = (unsigned char)c;
		s++;
	}
	return (b);
}
