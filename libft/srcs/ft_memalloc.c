/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:49:38 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/23 15:59:38 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*newzone;

	if (!size)
		return (NULL);
	if (!(newzone = easymalloc(size)))
		return (NULL);
	ft_memset(newzone, '\0', size);
	return (newzone);
}
