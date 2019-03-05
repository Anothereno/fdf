/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:38:12 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/04 13:20:35 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_mode(t_union *my_union, char c)
{
	if (uptr.mode != c)
		uptr.mode = c;
	uptr.shift_x = 0;
	uptr.shift_y = 0;
	plot_grid(my_union);
}

void	isometric(int i, int j, t_union *my_union)
{
	int prev_x;
	int prev_y;

	prev_x = uptr.transform[i][j].x;
	prev_y = uptr.transform[i][j].y;
	uptr.transform[i][j].x = (int)((prev_x - prev_y) * (float)cos(0.523599) * uptr.scale);
	uptr.transform[i][j].y = (int)((((prev_x + prev_y) * (float)sin(0.523599)) -
			uptr.transform[i][j].z) * uptr.scale);
}


void	shift_y(int key, t_union *my_union)
{
	if (key == 13)
		my_union->shift_y += 4;
	if (key == 1)
		my_union->shift_y -= 4;
	plot_grid(my_union);
}

void	shift_x(int key, t_union *my_union)
{
	if (key == 0)
		my_union->shift_x += 4;
	if (key == 2)
		my_union->shift_x -= 4;
	plot_grid(my_union);
}

void	zoom(int key, t_union *my_union)
{
	int old_size;

	old_size = uptr.scale;
	if (old_size - uptr.kof == 0 && key == 78)
		uptr.kof = 1;
	if (uptr.scale == 2 && key == 69)
		uptr.kof = 2;
	if ((uptr.scale - uptr.kof > 0) || key == 69)
	{
		if (key == 69 && uptr.scale < 800)
			uptr.scale += uptr.kof;
		else if (key == 78)
			uptr.scale -= uptr.kof;
		plot_grid(my_union);
	}
}
