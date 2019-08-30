/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 11:51:11 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/30 14:10:38 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

int		main(int ac, char **av)
{
	char		*ptr1;
	char		*ptr2;
	char		*ptr3;
	char		*ptr4;
	char		*ptr5;

	ptr1 = easymalloc(5);
	ptr2 = easymalloc(5);
	ptr3 = easymalloc(5);
	ptr4 = easymalloc(5);
	ptr5 = malloc(5);
	ft_free((void **)ptr2);
	return (0);
}
