/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 11:08:20 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/03 15:19:44 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strlen(char *str)
{
	char *cpy;

	if (str)
	{
		cpy = str;
		while (*cpy)
			cpy++;
		return (cpy - str);
	}
	return (0);
}

int		abs(int nb)
{
	return (nb < 0 ? -nb : nb);
}
