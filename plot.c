/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:04:53 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/05 15:48:56 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	main_loop(t_union **my_union)
{
	int i;
	int j;

	i = -1;

	while (++i < uptr->grid_size_y)
	{
		j = -1;
		while (++j < uptr->grid_size_x)
		{
			uptr->transform[i][j] = uptr->points[i][j];
			if ((uptr->transform[i][j].x > uptr->win_x + 1000 || uptr->transform[i][j].x < -1000)
				&& (uptr->transform[i][j].y > uptr->win_y + 1000 || uptr->transform[i][j].y < -1000))
				continue;
			if (uptr->mode != 'i')
			{
				sub_coordinates(my_union, i, j);
				rotate_all_axis(my_union, i, j);
			}
			if (uptr->mode == 'i')
				isometric(i, j, uptr);
			shift_coordinates(my_union, i, j);
		}
	}
}

void	sub_coordinates(t_union **my_union, int i, int j)
{
	uptr->transform[i][j].x = uptr->transform[i][j].x * uptr->scale
			- ((uptr->grid_size_x * uptr->scale) / 2);
	uptr->transform[i][j].y = uptr->transform[i][j].y * uptr->scale
			- ((uptr->grid_size_y * uptr->scale) / 2);
	uptr->transform[i][j].z = uptr->transform[i][j].z * uptr->scale;
}

void	shift_coordinates(t_union **my_union, int i, int j)
{
	uptr->transform[i][j].x = uptr->transform[i][j].x
							  + uptr->win_x / 2 + uptr->shift_x;
	uptr->transform[i][j].y = uptr->transform[i][j].y
							  + uptr->win_y / 2 + uptr->shift_y;
}


void	plot_grid(t_union *my_union)
{
	int i;
	int j;

	i = -1;
//	mlx_destroy_image(uptr.mlx_ptr, uptr.image_ptr);
	mlx_clear_window(uptr.mlx_ptr, uptr.win_ptr);
	main_loop(&my_union);
	while (++i < uptr.grid_size_y)
	{
		j = -1;
		while (++j < uptr.grid_size_x)
		{
			if ((TR[i][j].x > uptr.win_x + 500|| TR[i][j].x < -500)
			&& (TR[i][j].y > uptr.win_y + 500|| TR[i][j].y < -500))
				continue;
			if (i - 1 >= 0)
				plot_line(TR[i][j], TR[i - 1][j], my_union);
			if (j + 1 < uptr.grid_size_x)
				plot_line(TR[i][j], TR[i][j + 1], my_union);
		}
	}
//	mlx_put_image_to_window(uptr.mlx_ptr, uptr.win_ptr, uptr.image_ptr, 0, 0);
}

int		take_sign(int x)
{
	if (x == 0)
		return (0);
	else
		return (x > 0 ? 1 : -1);
}

void	plot_line(t_point point0, t_point point1, t_union *my_union)
{
	int 	x0;
	int 	x1;
	int 	y0;
	int 	y1;
	int 	dx;
	int 	dy;
	int		inclinex;
	int 	incliney;
	int		signx;
	int 	signy;
	int 	error;
	int 	incx;
	int 	incy;
	int 	longline;
	int		shortline;
	int 	curx;
	int 	cury;
	int 	i;
	char 	w;

	dx = point1.x - point0.x;
	dy = point1.y - point0.y;
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
		w = 'x';
	}
	else
	{
		inclinex = 0;
		incliney = signy;
		shortline = dx;
		longline = dy;
		w = 'y';
	}
	curx = point0.x;
	cury = point0.y;
	error = longline / 2;
//	mlx_pixel_put(my_union->mlx_ptr, my_union->win_ptr, curx, cury, set_color(point0, point1, ));
	i = -1;
	while (++i < longline)
	{
//		if ((curx > uptr.win_x || curx < 0) && (cury > uptr.win_y || cury < 0))
//			break;
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
		if ((curx <= uptr.win_x && curx >= 0) && (cury <= uptr.win_y && cury >= 0))
//			set_pixel(&my_union, curx, cury);
			mlx_pixel_put(my_union->mlx_ptr, my_union->win_ptr, curx, cury, set_color(point0, point1, curx, cury, w));
	}
}