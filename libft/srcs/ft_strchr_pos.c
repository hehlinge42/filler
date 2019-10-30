/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:02:41 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/03 17:54:41 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strchr_pos(char *s, int c)
{
	char	*str;

	if (!(str = s))
	{
		return (-1);
	}
	while (*str)
	{
		if (*str == c)
			return (str - s);
		str++;
	}
	return (c ? -1 : str - s);
}
