/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:38:12 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/07 17:56:33 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_mode(t_union *my_union, char c)
{
	if (UPTR.mode != c)
		UPTR.mode = c;
	UPTR.shift_x = 0;
	UPTR.shift_y = 0;
	plot_grid(my_union);
}

void	isometric(int i, int j, t_union *my_union)
{
	int prev_x;
	int prev_y;

	prev_x = UPTR.transform[i][j].x;
	prev_y = UPTR.transform[i][j].y;
	UPTR.transform[i][j].x = (int)((prev_x - prev_y) * (float)cos(0.523599)
			* UPTR.scale);
	UPTR.transform[i][j].y = (int)((((prev_x + prev_y) * (float)sin(0.523599)) -
			UPTR.transform[i][j].z) * UPTR.scale);
}

void	shift_y(int key, t_union *my_union)
{
	if (key == 13)
		my_union->shift_y += 15;
	if (key == 1)
		my_union->shift_y -= 15;
	plot_grid(my_union);
}

void	shift_x(int key, t_union *my_union)
{
	if (key == 0)
		my_union->shift_x += 15;
	if (key == 2)
		my_union->shift_x -= 15;
	plot_grid(my_union);
}

void	zoom(int key, t_union *my_union)
{
	int old_size;

	old_size = UPTR.scale;
	if (old_size - UPTR.kof == 0 && key == 78)
		UPTR.kof = 1;
	if (UPTR.scale == 2 && key == 69)
		UPTR.kof = 2;
	if ((UPTR.scale - UPTR.kof > 0) || key == 69)
	{
		if (key == 69 && UPTR.scale < 300)
			UPTR.scale += UPTR.kof;
		else if (key == 78)
			UPTR.scale -= UPTR.kof;
	}
	plot_grid(my_union);
}
