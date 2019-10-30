/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:04:12 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/08 14:15:16 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		read_loop(char buf[100], int fd, int *pos, char **line)
{
	int		ret;

	ret = 100;
	while (*pos == -1 && ret > 0)
	{
		ret = read(fd, buf, 100);
		if (ret <= 0)
		{
			return (0);
		}
		buf[ret] = 0;
		if (ret && !(*line = ft_strjoin_free(*line, buf, 1)))
		{
			return (0);
		}
		*pos = ft_strchr_pos(*line, '\n');
	}
	return (1);
}

int		filler_gnl(int fd, char **line)
{
	static char		*keep = NULL;
	char			buf[101];
	int				pos;

	if (!line)
		return (0);
	ft_free((void **)line);
	*line = NULL;
	if (keep && !(*line = ft_strdup(keep)))
		return (0);
	if (keep)
		ft_free((void **)&keep);
	pos = ft_strchr_pos(*line, '\n');
	if (pos == -1 && !(read_loop(buf, fd, &pos, line)))
		return (0);
	pos > -1 ? (*line)[pos] = 0 : 0;
	if (pos > -1 && !(keep = ft_strdup(*line + pos + 1)))
		return (0);
	return (*line ? 1 : 0);
}
