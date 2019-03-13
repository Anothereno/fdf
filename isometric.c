/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:08:43 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/07 16:44:20 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		iso_scale(t_union *my_union, int scale)
{
	int i;
	int j;
	int flag;

	while (scale > 1)
	{
		i = -1;
		flag = 0;
		UPTR.scale = scale;
		main_loop(&my_union);
		while (++i < UPTR.grid_size_y && !flag)
		{
			j = -1;
			while (++j < UPTR.grid_size_x && !flag)
				if ((TR[i][j].x > UPTR.win_x || TR[i][j].x < 0)
					|| (TR[i][j].y > UPTR.win_y || TR[i][j].y < 0))
					flag++;
		}
		if (!flag)
			return (scale);
		scale--;
	}
	return (scale);
}

void	clear_array(char **array)
{
	int i;

	i = -1;
	while (array[++i] != NULL)
		ft_strdel(&array[i]);
	free(array);
}

int		calc_scale(t_union **my_union)
{
	int div_x;
	int div_y;

	div_x = UPTR->win_x / UPTR->grid_size_x;
	div_y = UPTR->win_y / UPTR->grid_size_y;
	return (iso_scale(*my_union, MIN(div_x, div_y)));
}
