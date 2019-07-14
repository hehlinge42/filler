/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:03:58 by hehlinge          #+#    #+#             */
/*   Updated: 2019/07/11 17:57:08 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "filler.h"
#include "../libft/includes/libft.h"

static void		ft_free(t_gnl **begin_list, t_gnl *elem)
{
	t_gnl	*tmp;

	tmp = *begin_list;
	if (tmp == elem)
	{
		*begin_list = tmp->next;
		free(elem);
		elem = NULL;
		return ;
	}
	while (tmp)
	{
		if (tmp->next == elem)
		{
			tmp->next = tmp->next->next;
			free(elem);
			elem = NULL;
		}
		tmp = tmp->next;
	}
}

static t_gnl	*find_fd(t_gnl **begin_list, int fd)
{
	t_gnl	*elem;
//	int		i;

	elem = *begin_list;
	while (elem)
	{
		if (elem->fd == fd)
			return (elem);
		elem = elem->next;
	}
	if (!(elem = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	ft_bzero(elem, sizeof(elem));
	elem->fd = fd;
//	i = -1;
//	while (elem->buf[++i])
//		elem->buf[i] = 0;
	elem->next = *begin_list;
	*begin_list = elem;
	return (elem);
}

static int			ft_move_buf(char *buf, char *strstr, int opt, t_gnl *begin)
{
	if (!opt)
	{
		ft_memmove(buf, strstr + 1, BUFF_SIZE);
		buf[BUFF_SIZE] = '\0';
		strstr[0] = '\0';
		return (0);
	}
	if (buf)
		free(buf);
	ft_clear_list(&begin);
	return (0);
}

static int		read_buff(char *buf, char **str, int fd)
{
	int		ret;
	char	*tmp;
	char	*strstr;

	if (!(*str = ft_strdup(buf)))
		return (-1);
	strstr = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = *str;
		if (!(*str = ft_strjoin(tmp, buf)))
			return (-1);
		free(tmp);
		if ((strstr = ft_strstr(*str, "\n")))
			break ;
	}
	if (strstr)
		ft_move_buf(buf, strstr, 0, NULL);
	if (!strstr && ret == 0)
	{
		buf[0] = '\0';
		return (-2);
	}
	return (ret);
}

int				gnl(const int fd, char **line, int opt)
{
	static t_gnl	*begin_gnl = NULL;
	char			*tmp;
	t_gnl			*elem;
	int				ret;

	if (opt || fd < 0 || !line || BUFF_SIZE < 0 || !(elem = find_fd(&begin_gnl, fd)))
		return (opt ? ft_move_buf(*line, NULL, opt, begin_gnl) : -1);
	if ((tmp = ft_strstr(elem->buf, "\n")))
	{
		tmp[0] = '\0';
		if (!(*line = ft_strdup(elem->buf)))
			return (-1);
		ft_memmove(elem->buf, tmp + 1, BUFF_SIZE);
		return (1);
	}
	if ((ret = read_buff(elem->buf, line, fd)) == -1)
		return (-1);
	if (ret == -2 && !(*line[0]))
	{
		ft_strdel(line);
		ft_free(&begin_gnl, elem);
		return (0);
	}
	return (1);
}
