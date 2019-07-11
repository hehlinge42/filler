/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:44:23 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/23 11:30:20 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	if (!n)
		return (0);
	i = 0;
	res = 0;
	while (((unsigned char)s1[i] || (unsigned char)s2[i]) && i < n && res == 0)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			res = ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (res);
}
