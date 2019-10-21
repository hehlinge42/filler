/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:36:48 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/26 16:08:09 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	char	*dst_cpy;
	char	*src_cpy;

	dst_cpy = (char *)dst;
	src_cpy = (char *)src;
	while (*src_cpy)
	{
		*dst_cpy++ = *src_cpy++;
	}
	*dst_cpy = 0;
	return (dst);
}
