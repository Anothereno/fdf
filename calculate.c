/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:42:02 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/07 17:43:11 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		check_edge(t_point transform, t_union *my_union)
{
	if ((transform.x > UPTR.win_x + 1000 || transform.x < -1000)
		&& (transform.y > UPTR.win_y + 1000 || transform.y < -1000))
		return (0);
	return (1);
}

void	main_loop(t_union **my_union)
{
	int i;
	int j;

	i = -1;
	while (++i < UPTR->grid_size_y)
	{
		j = -1;
		while (++j < UPTR->grid_size_x)
		{
			UPTR->transform[i][j] = UPTR->points[i][j];
			if (!check_edge(UPTR->transform[i][j], *my_union))
				continue;
			if (UPTR->mode != 'i')
			{
				sub_coordinates(my_union, i, j);
				rotate_all_axis(my_union, i, j);
			}
			if (UPTR->mode == 'i')
				isometric(i, j, UPTR);
			shift_coordinates(my_union, i, j);
		}
	}
}

void	sub_coordinates(t_union **my_union, int i, int j)
{
	UPTR->transform[i][j].x = UPTR->transform[i][j].x * UPTR->scale
			- ((UPTR->grid_size_x * UPTR->scale) / 2);
	UPTR->transform[i][j].y = UPTR->transform[i][j].y * UPTR->scale
			- ((UPTR->grid_size_y * UPTR->scale) / 2);
	UPTR->transform[i][j].z = UPTR->transform[i][j].z * UPTR->scale;
}

void	shift_coordinates(t_union **my_union, int i, int j)
{
	if (UPTR->mode != 'i')
	{
		UPTR->transform[i][j].x = UPTR->transform[i][j].x
				+ UPTR->win_x / 2 + UPTR->shift_x;
		UPTR->transform[i][j].y = UPTR->transform[i][j].y
				+ UPTR->win_y / 2 + UPTR->shift_y;
	}
	else
	{
		UPTR->transform[i][j].x = UPTR->transform[i][j].x
				+ UPTR->win_x / 2 + UPTR->shift_x;
		UPTR->transform[i][j].y = UPTR->transform[i][j].y
				+ UPTR->win_y / 4 + UPTR->shift_y;
	}
}
