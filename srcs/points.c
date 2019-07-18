#include "filler.h"
#include <stdlib.h>
#include <stdio.h>

int		ft_init_point(t_var *var, int x, int y, char letter)
{
	t_point	*elem;

	if (!(elem = (t_point *)malloc(sizeof(t_point) * 2)))
		return (0);
	//ft_lstadd(var->to_free, ft_lstnew((void *)elem, sizeof(void *)));
	ft_memset(elem, 0, sizeof(t_point));
	elem->x = x;
	elem->y = y;
	elem->next = NULL;
	if (letter == 'X')
		var->points_x = &elem;
	else if (letter == 'O')
		var->points_o = &elem;
	return (1);
}

int		ft_add_point(t_var *var, int x, int y, char letter)
{
	t_point	*elem;
	if (!(elem = (t_point *)malloc(sizeof(t_point))))
		return (0);
	ft_bzero(elem, sizeof(t_point));
	elem->x = x;
	elem->y = y;
	if (letter == 'X')
	{
		elem->next = *(var->points_x);
		*(var->points_x) = elem;
	}
	else if (letter == 'O')
	{
		elem->next = *(var->points_o);
		*(var->points_o) = elem;
	}
	return (1);
}
