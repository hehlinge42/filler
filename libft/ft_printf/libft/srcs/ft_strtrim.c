/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:26:19 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/23 11:30:21 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	size_t	count;
	char	*res;

	i = -1;
	count = 0;
	if (!s)
		return (NULL);
	while (s[++i] == ' ' || s[i] == '\t' || s[i] == '\n')
		;
	while (s[++i])
		count++;
	while (--i > 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		count--;
	if (!(res = ft_strnew(count + 1)))
		return (NULL);
	return (ft_strncpy(res, s + i - count, count + 1));
}
