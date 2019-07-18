#include "filler.h"
#include <stdio.h>

void	ft_print_debug(t_var *var)
{
	int		i;
	t_point	*begin_list;

	i = -1;
	ft_printf("MAP\n");
	while (++i < var->x_max)
		printf("%s\n", var->map[i]);
	i = -1;
	ft_printf("PIECE\n");
	while (++i < var->x_size_piece)
		printf("%s\n", var->piece[i]);
	ft_printf("POINTS DE X\n");
	begin_list = *(var->points_x);
	while (begin_list)
	{
		ft_printf("x = %d\n", begin_list->x);
		ft_printf("y = %d\n\n", begin_list->y);
		begin_list = begin_list->next;
	}
	ft_printf("POINTS DE O\n");
	begin_list = *(var->points_o);
	while (begin_list)
	{
		ft_printf("x = %d\n", begin_list->x);
		ft_printf("y = %d\n\n", begin_list->y);
		begin_list = begin_list->next;
	}
}
