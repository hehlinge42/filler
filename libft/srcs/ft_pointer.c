/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:40:00 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 12:29:02 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/ft_printf.h"

int	ft_pointer(t_printf *strct, t_buffer *buffer, va_list va)
{
	strct->flag[FLAG_HASH] = '#';
	strct->length = LENGTH_L;
	strct->flag[FLAG_PLUS] = -1;
	ft_uint(strct, buffer, va);
	return (1);
}
