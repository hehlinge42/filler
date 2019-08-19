/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:51:48 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 11:16:22 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_percent(t_printf *strct, t_buffer *buffer, va_list va)
{
	(void)va;
	if (strct->flag[FLAG_MINUS] == -1)
		ft_print_width(strct, buffer, 1);
	ft_write_buf("%", buffer, 1);
	if (strct->flag[FLAG_MINUS] != -1)
		ft_print_width(strct, buffer, 1);
	return (1);
}
