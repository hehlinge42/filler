/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 12:28:27 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/23 11:30:18 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	nb;
	unsigned int	i;
	int				count;

	count = (n < 0) ? 2 : 1;
	nb = (n < 0) ? -n : n;
	i = 1;
	while (nb / i >= 10)
	{
		count++;
		i *= 10;
	}
	if (!(res = (char *)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	res[count] = '\0';
	while (--count >= 0)
	{
		res[count] = '0' + (nb % 10);
		nb /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
