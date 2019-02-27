/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:38:12 by hdwarven          #+#    #+#             */
/*   Updated: 2019/02/27 22:13:49 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_mode(t_union *my_union, char c)
{
	if (uptr.mode != 'i' && c == 'i')
	{
		uptr.mode = c;
		trans_iso(my_union);
	}
	if (uptr.mode != 'f' && c == 'f')
	{
		uptr.mode = c;
		plot_grid(my_union);
	}
}

void	trans_iso(t_union *my_union)
{
	int i;
	int j;

	copy2trans(&my_union);
	i = -1;
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
	*x = (int)((prev_x - prev_y) * (float)cos(0.523599) * uptr.scale);
	*y = (int)((((prev_x + prev_y) * (float)sin(0.523599)) - z) * uptr.scale);
}

void	shift_y(int key, t_union *my_union)
{
	if (uptr.mode != 'i')
	{
		if (key == 13)
			my_union->shift_y += 4;
		if (key == 1)
			my_union->shift_y -= 4;
		if (uptr.mode != 'i')
			plot_grid(my_union);
	}
}

void	shift_x(int key, t_union *my_union)
{
	if (uptr.mode != 'i')
	{
		if (key == 0)
			my_union->shift_x += 4;
		if (key == 2)
			my_union->shift_x -= 4;
		if (uptr.mode != 'i')
			plot_grid(my_union);
	}
}

void	zoom(int key, t_union *my_union)
{
	int old_size;

	old_size = (my_union)->scale;
	if (old_size - uptr.kof == 0 && key == 78)
		uptr.kof = 1;
	if (uptr.scale == 2 && key == 69)
		uptr.kof = 2;
	if ((uptr.scale - uptr.kof > 0) || key == 69)
	{
		if (key == 69)
			(my_union)->scale += uptr.kof;
		else if (key == 78)
			(my_union)->scale -= uptr.kof;
		mlx_string_put(uptr.mlx_ptr, uptr.win_ptr, 120, 120, 0xFF002B, ft_itoa(uptr.scale));
		if (uptr.mode == 'i')
			trans_iso(my_union);
		else
			plot_grid(my_union);
	}
	ft_putnbr(uptr.scale);
	ft_putchar('\n');
}
