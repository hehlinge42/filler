/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:19:02 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/23 11:30:18 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int nbr;

	if (fd >= 0)
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			nbr = -n;
		}
		else
			nbr = n;
		if (nbr < 10)
			ft_putchar_fd(nbr + '0', fd);
		else
		{
			ft_putnbr_fd(nbr / 10, fd);
			ft_putnbr_fd(nbr % 10, fd);
		}
	}
}
