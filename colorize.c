/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:06:04 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/05 17:24:16 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_pixel(t_union **my_union, int x, int y)
{
	int point;

	point = (x + (4 * uptr->win_x * y));
	uptr->image_data[point] = 255;
	uptr->image_data[point + 1] = 255;
	uptr->image_data[point + 2] = 255;
	uptr->image_data[point + 3] = 0;
}

int 	declare_color(int z)
{
	int red;
	int green;
	int blue;
	int res;

	if (z >= 0)
	{
		red = z % 45 * 15;//(z % 16 + 1) * (z % 100 + 1);
		green = 10;//(z % 4 + 1) * (z % 15 + 1);
		blue = 30;//(z % 4 + 1) * (z % 15 + 1);
	}
	else
	{
		red = 10;
		green = 10;
		blue = (-z) % 45 * 15;
	}
	res = (red << 16) | (green << 8) | blue;
	return (res);
}

int		set_color(t_point point0, t_point point1, int curx, int cury, char w)
{
	int		red;
	int		green;
	int		blue;
	double	perc;
	int 	res;

	if (w == 'x')
		perc = percent(point0.x, point1.x, curx);
	else
		perc = percent(point0.y, point1.y, cury);
	red = take_color((point0.color >> 16) & 0xFF,
			(point1.color >> 16) & 0xFF, perc);
	green = take_color((point0.color >> 8) & 0xFF,
					 (point1.color >> 8) & 0xFF, perc);
	blue = take_color(point0.color & 0xFF,
					 point1.color & 0xFF, perc);
	res = (red << 16) | (green << 8) | blue;
	return (res);
}

int 	take_color(int start, int finish, double perc)
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

