/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:55:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/07 18:24:24 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_points(t_union *my_union)
{
	int i;

	i = UPTR.grid_size_y;
	while (--i > 0)
	{
		free(my_union->points[i]);
		free(my_union->transform[i]);
	}
	free(my_union->points);
	free(my_union->transform);
}

void	exit_(t_union *my_union)
{
	free(my_union->ints);
	free(my_union->line);
	free(my_union->color);
	clear_points(my_union);
	free(my_union);
	exit(0);
}

int		deal_key(int key, void *param)
{
	if (key == 53)
		exit_((t_union*)param);
	if (key == 34)
		change_mode((t_union*)param, 'i');
	if (key == 3)
		change_mode((t_union*)param, 'f');
	if (key == 78 || key == 69)
		zoom(key, (t_union*)param);
	if (key == 13 || key == 1)
		shift_y(key, (t_union*)param);
	if (key == 0 || key == 2)
		shift_x(key, (t_union*)param);
	if (key == 125 || key == 126)
		rotate_x(key, (t_union*)param);
	if (key == 123 || key == 124)
		rotate_y(key, (t_union*)param);
	if (key == 43 || key == 47)
		rotate_z(key, (t_union*)param);
	return (0);
}
