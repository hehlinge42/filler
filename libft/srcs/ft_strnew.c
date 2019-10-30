/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:12:59 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/06 20:26:33 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)easymalloc(sizeof(*str) * (size + 1))))
		return (NULL);
	ft_memset(str, '\0', size + 1);
	return (str);
}
