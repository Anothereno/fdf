/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:04:53 by hdwarven          #+#    #+#             */
/*   Updated: 2019/02/26 19:45:47 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	main_loop(t_union **my_union)
{
	int i;
	int j;

	i = -1;
	while (++i < uptr->grid_size_y)
	{
		j = -1;
		while (++j < uptr->grid_size_x)
		{

		}
	}
}*/

void	reshift(t_union **my_union)
{
	int i;
	int j;

	i = -1;
	while (++i < uptr->grid_size_y)
	{
		j = -1;
		while (++j < uptr->grid_size_x)
		{
			uptr->transform[i][j].x = uptr->transform[i][j].x
									  - uptr->win_x / 4 - uptr->shift_x;
			uptr->transform[i][j].y = uptr->transform[i][j].y
									  - uptr->win_y / 4 - uptr->shift_y;
		}
	}
}

void	shift_coordinates(t_union **my_union)
{
	int i;
	int j;

	i = -1;
	while (++i < uptr->grid_size_y)
	{
		j = -1;
		while (++j < uptr->grid_size_x)
		{
			uptr->transform[i][j].x = uptr->transform[i][j].x
					+ uptr->win_x / 4 + uptr->shift_x;
			uptr->transform[i][j].y = uptr->transform[i][j].y
					+ uptr->win_y / 4 + uptr->shift_y;
		}
	}
}

void	resize_coordinates(t_union **my_union, int old_size)
{
	int i;
	int j;

	i = -1;
	while (++i < uptr->grid_size_y)
	{
		j = -1;
		while (++j < uptr->grid_size_x)
		{
			uptr->points[i][j].x = uptr->points[i][j].x
					* uptr->size / old_size;
			uptr->points[i][j].y = uptr->points[i][j].y
					* uptr->size / old_size;
			uptr->points[i][j].z = uptr->points[i][j].z
					* uptr->size / old_size;
		}
	}
}

void	plot_grid(t_union *my_union)
{
	int i;
	int j;

	i = -1;
	mlx_clear_window(my_union->mlx_ptr, my_union->win_ptr);
	if (my_union->mode != 'i')
		copy2trans(&my_union);
	shift_coordinates(&my_union);
	while (++i < (my_union)->grid_size_y)
	{
		j = -1;
		while (++j < (my_union)->grid_size_x)
		{
			if (i - 1 >= 0)
				plot_line(TR[i][j].x, TR[i][j].y, TR[i - 1][j].x,
						TR[i - 1][j].y, my_union);
			if (j + 1 < (my_union)->grid_size_x)
				plot_line(TR[i][j].x, TR[i][j].y, TR[i][j + 1].x,
						TR[i][j + 1].y, my_union);
		}
	}
}

int		take_sign(int x)
{
	if (x == 0)
		return (0);
	else
		return (x > 0 ? 1 : -1);
}

void	plot_line(int x0, int y0, int  x1,int  y1, t_union *my_union)
{
	int dx;
	int dy;
	int inclinex;
	int incliney;
	int signx;
	int signy;
	int error;
	int incx;
	int incy;
	int longline;
	int shortline;
	int curx;
	int cury;
	int i;

	dx = x1 - x0;
	dy = y1 - y0;
	signx = take_sign(dx);
	signy = take_sign(dy);
	dx = ABS(dx);
	dy = ABS(dy);
	if (dx > dy)
	{
		inclinex = signx;
		incliney = 0;
		shortline = dy;
		longline = dx;
	}
	else
	{
		inclinex = 0;
		incliney = signy;
		shortline = dx;
		longline = dy;
	}
	curx = x0;
	cury = y0;
	error = longline / 2;
	mlx_pixel_put(my_union->mlx_ptr, my_union->win_ptr, curx, cury, 0xFFFFFF);
	i = -1;
	while (++i < longline)
	{
		error -= shortline;
		if (error < 0)
		{
			error += longline;
			curx += signx;
			cury += signy;
		}
		else
		{
			curx += inclinex;
			cury += incliney;
		}
		mlx_pixel_put(my_union->mlx_ptr, my_union->win_ptr, curx, cury, 0xFFFFFF);
	}
}