/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 20:32:01 by hdwarven          #+#    #+#             */
/*   Updated: 2019/02/27 22:12:49 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_all_axis(t_union **my_union, int i, int j)
{
	if (uptr->x_angle)
		rotate_x_axis(my_union, i, j);
	if (uptr->y_angle)
		rotate_y_axis(my_union, i, j);
	if (uptr->z_angle)
		rotate_z_axis(my_union, i, j);
}

void	rotate_x(int key, t_union *my_union)
{
	if (uptr.mode != 'i')
	{
		if (key == 126)
			my_union->x_angle -= 2;
		if (key == 125)
			my_union->x_angle += 2;
		if (uptr.mode != 'i')
			plot_grid(my_union);
	}
}

void	rotate_y(int key, t_union *my_union)
{
	if (uptr.mode != 'i')
	{
		if (key == 123)
			my_union->y_angle -= 2;
		if (key == 124)
			my_union->y_angle += 2;
		if (uptr.mode != 'i')
			plot_grid(my_union);
	}
}

void	rotate_z(int key, t_union *my_union)
{
	if (uptr.mode != 'i')
	{
		if (key == 43)
			my_union->z_angle -= 2;
		if (key == 47)
			my_union->z_angle += 2;
		if (uptr.mode != 'i')
			plot_grid(my_union);
	}
}

void	rotate_x_axis(t_union **my_union, int i, int j)
{
	double	tetta;
	int 	y;
	int		z;

	tetta = uptr->x_angle * M_PI / 180;
	y = (int)((uptr->transform[i][j].y *
			cos(tetta)) + uptr->transform[i][j].z * sin(tetta));
	z = (int)((uptr->transform[i][j].y * (-1) *
			sin(tetta)) + uptr->transform[i][j].z * cos(tetta));
	uptr->transform[i][j].y = y;
	uptr->transform[i][j].z = z;
}

void	rotate_y_axis(t_union **my_union, int i, int j)
{
	double	tetta;
	int 	x;
	int		z;

	tetta = uptr->y_angle * M_PI / 180;
	x = (int)((uptr->transform[i][j].x *
			cos(tetta)) + uptr->transform[i][j].z * sin(tetta));
	z = (int)((uptr->transform[i][j].x * (-1) *
			sin(tetta)) + uptr->transform[i][j].z * cos(tetta));
	uptr->transform[i][j].x = x;
	uptr->transform[i][j].z = z;
}

void	rotate_z_axis(t_union **my_union, int i, int j)
{
	double	tetta;
	int 	x;
	int		y;

	tetta = uptr->z_angle * M_PI / 180;
	x = (int)((uptr->transform[i][j].x *
			cos(tetta)) - uptr->transform[i][j].y * sin(tetta));
	y = (int)((uptr->transform[i][j].x *
			sin(tetta)) + uptr->transform[i][j].y * cos(tetta));
	uptr->transform[i][j].x = x;
	uptr->transform[i][j].y = y;
}