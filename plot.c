/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:04:53 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/07 17:42:33 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_grid(t_union *my_union)
{
	int i;
	int j;

	i = -1;
	image_init(&my_union);
	main_loop(&my_union);
	while (++i < UPTR.grid_size_y)
	{
		j = -1;
		while (++j < UPTR.grid_size_x)
		{
			if ((TR[i][j].x > UPTR.win_x + 500 || TR[i][j].x < -500)
			&& (TR[i][j].y > UPTR.win_y + 500 || TR[i][j].y < -500))
				continue;
			if (i - 1 >= 0)
				plot_line(TR[i][j], TR[i - 1][j], my_union);
			if (j + 1 < UPTR.grid_size_x)
				plot_line(TR[i][j], TR[i][j + 1], my_union);
		}
	}
	image_put(&my_union);
}

int		take_sign(int x)
{
	if (x == 0)
		return (0);
	else
		return (x > 0 ? 1 : -1);
}

void	delta_compare(t_union *my_union)
{
	if (UPTR.line->dx > UPTR.line->dy)
	{
		UPTR.line->inclinex = UPTR.line->signx;
		UPTR.line->incliney = 0;
		UPTR.line->shortline = UPTR.line->dy;
		UPTR.line->longline = UPTR.line->dx;
		UPTR.delta = 'x';
	}
	else
	{
		UPTR.line->inclinex = 0;
		UPTR.line->incliney = UPTR.line->signy;
		UPTR.line->shortline = UPTR.line->dx;
		UPTR.line->longline = UPTR.line->dy;
		UPTR.delta = 'y';
	}
}

void	plot_line(t_point point0, t_point point1, t_union *my_union)
{
	UPTR.line->dx = point1.x - point0.x;
	UPTR.line->dy = point1.y - point0.y;
	UPTR.line->signx = take_sign(UPTR.line->dx);
	UPTR.line->signy = take_sign(UPTR.line->dy);
	UPTR.line->dx = ABS(UPTR.line->dx);
	UPTR.line->dy = ABS(UPTR.line->dy);
	delta_compare(my_union);
	UPTR.ints->i = point0.x;
	UPTR.ints->j = point0.y;
	UPTR.line->error = UPTR.line->longline / 2;
	print_line(point0, point1, my_union);
}

void	print_line(t_point point0, t_point point1, t_union *my_union)
{
	UPTR.line->i = -1;
	while (++UPTR.line->i < UPTR.line->longline)
	{
		UPTR.line->error -= UPTR.line->shortline;
		if (UPTR.line->error < 0)
		{
			UPTR.line->error += UPTR.line->longline;
			UPTR.ints->i += UPTR.line->signx;
			UPTR.ints->j += UPTR.line->signy;
		}
		else
		{
			UPTR.ints->i += UPTR.line->inclinex;
			UPTR.ints->j += UPTR.line->incliney;
		}
		if (UPTR.ints->i >= UPTR.win_x || UPTR.ints->i <= 0 ||
			UPTR.ints->j >= UPTR.win_y || UPTR.ints->j <= 0)
			continue;
		else
			set_pixel(&my_union, point0, point1);
	}
}
