/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 14:14:33 by sikpenou          #+#    #+#             */
/*   Updated: 2019/04/24 15:57:05 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_joinfree(char const *s1, char const *s2)
{
	char	*new;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
	{
		new = ft_strdup((char *)(s1 ? s1 : s2));
		free((char *)(s1 ? s1 : s2));
		return (new);
	}
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	if (!(new = (char *)malloc(sizeof(*new) * len)))
		return (NULL);
	ft_memset(new, 0, len);
	ft_memmove(new, s1, ft_strlen((char *)s1));
	ft_memmove(new + ft_strlen((char *)s1), s2, ft_strlen((char *)s2));
	free((char *)s1);
	free((char *)s2);
	return (new);
}

int				get_next_line(int fd, char **line)
{
	static char			*tab[OPEN_MAX] = {NULL};
	char				buf[BUFF_SIZE + 1];
	int					check;
	int					pos;

	if (!line || fd < 0 || fd >= OPEN_MAX || BUFF_SIZE < 1)
		return (-1);
	if (!(*line = ft_strdup(tab[fd])) && tab[fd] && tab[fd][0])
		return (ft_free_ptr(&(tab[fd])) - ft_free_ptr(line) - 1);
	ft_free_ptr(&(tab[fd]));
	ft_memset(buf, '\0', BUFF_SIZE + 1);
	check = BUFF_SIZE;
	while ((pos = ft_strchr_pos(*line, '\n')) < 0
		&& check == BUFF_SIZE && (check = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!(*line = ft_joinfree(*line, ft_strdup(buf))))
			return (ft_free_ptr(line) - 1);
		pos = ft_strchr_pos(*line, '\n');
		ft_memset(buf, '\0', BUFF_SIZE + 1);
	}
	if (!*line || !(ft_strlen(*line)))
		return (check - ft_free_ptr(line));
	tab[fd] = pos > -1 ? ft_strdup(ft_strchr(*line, '\n') + 1) : 0;
	pos > -1 ? (*line)[pos] = 0 : 1;
	return (!tab[fd] && pos > -1 ? ft_free_ptr(line) - 1 : 1);
}
