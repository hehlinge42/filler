/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:24:21 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/11 19:12:45 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	void	*cpy_s;
	int		len;

	if (!(len = n))
		return ;
	cpy_s = s;
	while (cpy_s - s < len)
	{
		*(char *)cpy_s = '\0';
		cpy_s++;
	}
	return ;
}
