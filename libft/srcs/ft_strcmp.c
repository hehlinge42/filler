/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:04:42 by hehlinge          #+#    #+#             */
/*   Updated: 2019/04/11 19:19:36 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned const char		*cpy_s1;
	unsigned const char		*cpy_s2;

	cpy_s1 = (unsigned const char *)s1;
	cpy_s2 = (unsigned const char *)s2;
	while (*cpy_s1 == *cpy_s2 && *cpy_s1 != '\0' && *cpy_s2 != '\0')
	{
		cpy_s1++;
		cpy_s2++;
	}
	return (*cpy_s1 - *cpy_s2);
}
