#include "filler.h"
#include <stdio.h>

void	ft_print_debug(t_var *var)
{
	int		i;
	t_point	*begin_list;

	i = -1;
	printf("MAP");
	while (++i < var->x_max)
		printf("%s\n", var->map[i]);
	i = -1;
	printf("PIECE");
	while (++i < var->x_size_piece)
		printf("%s\n", var->piece[i]);
	printf("POINTS DE X");
	begin_list = *(var->points_x);
	while (begin_list)
	{
		printf("x = %d\n", begin_list->x);
		printf("y = %d\n\n", begin_list->y);
		begin_list = begin_list->next;
	}
	printf("POINTS DE O");
	begin_list = *(var->points_o);
	while (begin_list)
	{
		printf("x = %d\n", begin_list->x);
		printf("y = %d\n\n", begin_list->y);
		begin_list = begin_list->next;
	}
}
