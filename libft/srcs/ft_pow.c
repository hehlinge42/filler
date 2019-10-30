/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:58:38 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/06 21:42:46 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long int		ft_pow(long long int nb, long long int pow)
{
	long long int		res;

	res = 1;
	while (pow > 0)
	{
		res = res * nb;
		pow--;
	}
	return (res);
}
