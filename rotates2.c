/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:46:48 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/07 17:54:34 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_all_axis(t_union **my_union, int i, int j)
{
	if (UPTR->x_angle)
		rotate_x_axis(my_union, i, j);
	if (UPTR->y_angle)
		rotate_y_axis(my_union, i, j);
	if (UPTR->z_angle)
		rotate_z_axis(my_union, i, j);
}

void	rotate_x(int key, t_union *my_union)
{
	if (UPTR.mode != 'i')
	{
		if (key == 126)
			my_union->x_angle -= 5;
		if (key == 125)
			my_union->x_angle += 5;
		if (UPTR.mode != 'i')
			plot_grid(my_union);
	}
}

void	rotate_y(int key, t_union *my_union)
{
	if (UPTR.mode != 'i')
	{
		if (key == 123)
			my_union->y_angle -= 5;
		if (key == 124)
			my_union->y_angle += 5;
		if (UPTR.mode != 'i')
			plot_grid(my_union);
	}
}

void	rotate_z(int key, t_union *my_union)
{
	if (UPTR.mode != 'i')
	{
		if (key == 43)
			my_union->z_angle -= 5;
		if (key == 47)
			my_union->z_angle += 5;
		if (UPTR.mode != 'i')
			plot_grid(my_union);
	}
}
