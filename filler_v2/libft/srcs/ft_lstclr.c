/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:19:17 by hehlinge          #+#    #+#             */
/*   Updated: 2019/07/29 23:34:29 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

void	ft_lstclr(t_lst **begin_list)
{
	t_lst *tmp;

	if (!(*begin_list))
		return ;
	while (*begin_list)
	{
		tmp = (*begin_list)->next;
		ft_free((void **)begin_list);
		*begin_list = tmp;
	}
}
