/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:25:29 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/23 11:30:21 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		count;
	int		i;
	int		beg;
	int		end;

	count = ft_word_count(s, c);
	if (!s || !(res = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	res[count] = NULL;
	i = -1;
	end = -1;
	while (++i < count)
	{
		beg = end;
		while (s[++beg] && s[beg] == c)
			;
		end = beg - 1;
		while (s[++end] && s[end] != c)
			;
		res[i] = ft_strnew(end - beg);
		ft_strncpy(res[i], s + beg, (size_t)end - beg);
	}
	return (res);
}
