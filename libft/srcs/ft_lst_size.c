/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:43:09 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/08 14:43:10 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lst_size(t_lst *begin_list)
{
	int			len;

	if (!begin_list)
		return (0);
	len = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		len++;
	}
	return (len);
}
