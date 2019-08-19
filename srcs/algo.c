#include "filler.h"

void	ft_place_piece(t_var *var, t_point *point)
{
	int		i;
	int		j;

	i = -1;
	while (++i < var->x_piece)
	{
		j = -1;
		while (++j < var->y_piece)
		{
			if (var->piece[j][i] == '*')
			{
				ft_printf("Copy : i = %d, j = %d, point->x = %d, point->y = %d\n",
					i, j, point->x, point->y);
				var->map[j + point->y][i + point->x] = 'T';
				//ft_printf("Char = %c\n", var->map[i + point->x][j + point->y]);
			}
		}
	}
	print_debug(*var, "1");
}

void	ft_simulate(t_var var, t_point *point)
{
	ft_printf("Dans ft_simulate\n");
	ft_place_piece(&var, point);
}

void	ft_algo(t_var *var)
{
	t_lst	*point;

	point = *(var->points_n);
	ft_printf("Dans ft_algo\n");
	while (point)
	{
		if (((t_point *)point->content)->available)
			ft_simulate(*var, (t_point *)point->content);
		point = point->next;
	}
	if (var->player == 'X')
	{
		point = *(var->points_x);
		while (point)
		{
			if (((t_point *)point->content)->available)
				ft_simulate(*var, (t_point *)point->content);
			point = point->next;
		}
	}
	else
	{
		point = *(var->points_x);
		while (point)
		{
			if (((t_point *)point->content)->available)
				ft_simulate(*var, (t_point *)point->content);
			point = point->next;
		}
	}
}
