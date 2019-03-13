/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:06:04 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/13 18:14:24 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_pixel(t_union **my_union, t_point point0,
		t_point point1)
{
	int point;

	point = (UPTR->ints->i * UPTR->bpp / 8 + (UPTR->sl * UPTR->ints->j));
	set_color(point0, point1, my_union);
	UPTR->image_data[point - 4] = UPTR->color->red;
	UPTR->image_data[point - 3] = UPTR->color->green;
	UPTR->image_data[point - 2] = UPTR->color->blue;
}

void	set2default(t_union **my_union)
{
	int		i;
	int		j;

	i = -1;
	while (++i < UPTR->grid_size_y)
	{
		j = -1;
		while (++j < UPTR->grid_size_x)
		{

			if (UPTR->points[i][j].color == -1)
				UPTR->points[i][j].color =
						calc_color(my_union, i, j);
			UPTR->points[i][j].z -= UPTR->ave;
		}
	}
}

int	calc_color(t_union **my_union, int i, int j)
{
	int		red;
	int		green;
	int		blue;
	double	perc;

	perc = percent(UPTR->min_z, UPTR->max_z,
				   UPTR->points[i][j].z);
	red = take_color((UPTR->min_color >> 16) & 0xFF,
					 (UPTR->max_color >> 16) & 0xFF, perc);
	green = take_color((UPTR->min_color >> 8) & 0xFF,
					   (UPTR->max_color >> 8) & 0xFF, perc);
	blue = take_color(UPTR->min_color & 0xFF,
					  UPTR->max_color & 0xFF, perc);
	UPTR->color->red = red;
	UPTR->color->green = green;
	UPTR->color->blue = blue;
	return ((red << 16) | (green << 8) | blue);
}

void	set_color(t_point point0, t_point point1, t_union **my_union)
{
	int		red;
	int		green;
	int		blue;
	double	perc;

	if (UPTR->delta == 'x')
		perc = percent(point0.x, point1.x, UPTR->ints->i);
	else
		perc = percent(point0.y, point1.y, UPTR->ints->j);
	red = take_color((point0.color >> 16) & 0xFF,
			(point1.color >> 16) & 0xFF, perc);
	green = take_color((point0.color >> 8) & 0xFF,
			(point1.color >> 8) & 0xFF, perc);
	blue = take_color(point0.color & 0xFF,
			point1.color & 0xFF, perc);
	UPTR->color->red = red;
	UPTR->color->green = green;
	UPTR->color->blue = blue;
}

int		take_color(int start, int finish, double perc)
{
	int res;

	res = (int)(((1 - perc) * start) + (perc * finish));
	return (res);
}

double	percent(int start, int finish, int point)
{
	double place;
	double dist;

	place = point - start;
	dist = finish - start;
	if (dist == 0)
		return (1.0);
	return (place / dist);
}
