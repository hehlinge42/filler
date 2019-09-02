/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 11:08:20 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/02 15:22:48 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_exit(int opt)
{
	if (opt == ERR_FIRST_LINE)
		ft_printf("exit - bad first line\n");
	else if (opt == BAD_MAP)
		ft_printf("exit - bad map\n");
	else if (opt == FULL_MAP)
		ft_printf("0 0\n");
	return (1);
}

int		abs(int nb)
{
	return (nb < 0 ? -nb : nb);
}
