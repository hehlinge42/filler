/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 12:40:21 by hehlinge          #+#    #+#             */
/*   Updated: 2019/08/20 16:10:51 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst		*ft_lstadd_new(t_lst **alst, void *content, int size)
{
	t_lst	*new;

	if (!(new = ft_lstnew(content, size)))
		return (NULL);
	ft_lstadd_back(alst, new);
	return (new);
}
