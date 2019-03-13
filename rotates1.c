/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 20:32:01 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/07 16:47:20 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x_axis(t_union **my_union, int i, int j)
{
	double	tetta;
	int		y;
	int		z;

	tetta = UPTR->x_angle * M_PI / 180;
	y = (int)((UPTR->transform[i][j].y *
			cos(tetta)) + UPTR->transform[i][j].z * sin(tetta));
	z = (int)((UPTR->transform[i][j].y * (-1) *
			sin(tetta)) + UPTR->transform[i][j].z * cos(tetta));
	UPTR->transform[i][j].y = y;
	UPTR->transform[i][j].z = z;
}

void	rotate_y_axis(t_union **my_union, int i, int j)
{
	double	tetta;
	int		x;
	int		z;

	tetta = UPTR->y_angle * M_PI / 180;
	x = (int)((UPTR->transform[i][j].x *
			cos(tetta)) + UPTR->transform[i][j].z * sin(tetta));
	z = (int)((UPTR->transform[i][j].x * (-1) *
			sin(tetta)) + UPTR->transform[i][j].z * cos(tetta));
	UPTR->transform[i][j].x = x;
	UPTR->transform[i][j].z = z;
}

void	rotate_z_axis(t_union **my_union, int i, int j)
{
	double	tetta;
	int		x;
	int		y;

	tetta = UPTR->z_angle * M_PI / 180;
	x = (int)((UPTR->transform[i][j].x *
			cos(tetta)) - UPTR->transform[i][j].y * sin(tetta));
	y = (int)((UPTR->transform[i][j].x *
			sin(tetta)) + UPTR->transform[i][j].y * cos(tetta));
	UPTR->transform[i][j].x = x;
	UPTR->transform[i][j].y = y;
}
