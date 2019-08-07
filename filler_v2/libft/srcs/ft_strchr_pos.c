/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:02:41 by sikpenou          #+#    #+#             */
/*   Updated: 2019/07/30 00:15:51 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strchr_pos(char *s, int c)
{
	char	*str;

	if (!s)
		return (-1);
	str = s;
	while (*str)
	{
		if (*str == c)
			return (str - s);
		str++;
	}
	return (c ? -1 : str - s);
}
