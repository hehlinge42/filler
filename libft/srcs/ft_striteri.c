/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 21:08:42 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/11 15:55:15 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char	*cpy_s;

	if (!(cpy_s = s) || !f)
		return ;
	while (*cpy_s)
	{
		(*f)(cpy_s - s, &(*cpy_s));
		cpy_s++;
	}
}
