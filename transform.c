/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:38:12 by hdwarven          #+#    #+#             */
/*   Updated: 2019/02/26 19:45:47 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	trans_iso(t_union *my_union)
{
	int i;
	int j;

	copy2trans(&my_union);
	i = -1;
	my_union->mode = 'i';
	while (++i < my_union->grid_size_y)
	{
		j = -1;
		while (++j < my_union->grid_size_x)
			isometric(&(my_union->transform[i][j].x), &(my_union->transform[i][j].y),
					  my_union->transform[i][j].z, my_union);
	}
	plot_grid(my_union);
}

void	isometric(int *x, int *y, int z, t_union *my_union)
{
	int prev_x;
	int prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (int)((prev_x - prev_y) * (float)cos(0.523599));
	*y = (int)(((prev_x + prev_y) * (float)sin(0.523599)) - z);
}

void	shift_y(int key, t_union *my_union)
{
	reshift(&my_union);
	if (key == 1)
		my_union->shift_y += 10;
	if (key == 13)
		my_union->shift_y -= 10;
	plot_grid(my_union);
}

void	shift_x(int key, t_union *my_union)
{
	reshift(&my_union);
	if (key == 2)
		my_union->shift_x += 10;
	if (key == 0)
		my_union->shift_x -= 10;
	plot_grid(my_union);
}

void	zoom(int key, t_union *my_union)
{
	int old_size;

	old_size = (my_union)->size;
	if (old_size - 10 || key != 78)
	{
		if (key == 69)
			(my_union)->size += 10;
		else if (key == 78)
			(my_union)->size -= 10;
		ft_putnbr(my_union->size);
		ft_putchar('\n');
		resize_coordinates(&my_union, old_size);
		if (uptr.mode == 'i')
			trans_iso(my_union);
		else
		{
			reshift(&my_union);
			plot_grid(my_union);
		}
	}
}

void	rotate_x(int key, t_union *my_union)
{

}