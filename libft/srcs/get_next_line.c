/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 14:14:33 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/12 17:02:29 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static char		*ft_joinfree(char *s1, char *s2)
{
	char	*new;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
	{
		new = ft_strdup((char *)(s1 ? s1 : s2));
		return (new);
	}
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	if (!(new = (char *)easymalloc(sizeof(*new) * len)))
		return (NULL);
	ft_memset(new, 0, len);
	ft_memmove(new, s1, ft_strlen((char *)s1));
	ft_memmove(new + ft_strlen((char *)s1), s2, ft_strlen((char *)s2));
	return (new);
}

int				read_loop(char **line, int *pos, int fd)
{
	int		check;
	char	buf[BUFF_SIZE + 1];

	ft_memset(buf, '\0', BUFF_SIZE + 1);
	check = BUFF_SIZE;
	while ((*pos = ft_strchr_pos(*line, '\n')) < 0
		&& check == BUFF_SIZE && (check = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!(*line = ft_joinfree(*line, ft_strdup(buf))))
		{
			return (-1);
		}
		*pos = ft_strchr_pos(*line, '\n');
		ft_memset(buf, '\0', BUFF_SIZE + 1);
	}
	if (!*line || !(ft_strlen(*line)))
		return (check);
	return (-2);
}

int				get_next_line(int fd, char **line)
{
	static char			*tab[10] = {NULL};
	int					pos;
	int					ret;

	if (!line || fd < 0 || fd >= 10 || BUFF_SIZE < 1)
		return (-1);
	if (tab[fd] && !(*line = ft_strdup(tab[fd])) && tab[fd][0])
	{
		return (-1);
	}
	*line = NULL;
	if ((ret = read_loop(line, &pos, fd)) != -2)
		return (ret);
	tab[fd] = pos > -1 ? ft_strdup(ft_strchr(*line, '\n') + 1) : 0;
	pos > -1 ? (*line)[pos] = 0 : 1;
	return (!tab[fd] && pos > -1 ? -1 : 1);
}
