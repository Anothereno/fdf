/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:07:27 by hdwarven          #+#    #+#             */
/*   Updated: 2019/02/27 15:37:27 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int 	calc_scale(t_union **my_union)
{
	int div_x;
	int div_y;

	div_x = uptr->win_x / uptr->grid_size_x;
	div_y = uptr->win_y / uptr->grid_size_y;
	return (MIN(div_x, div_y));
}

int		grid_valid(t_union ***my_union, char *grid, int *x, int *y)
{
	char	**split_array;
	int 	i;

	i = 0;
	*y = (int)ft_count_word(grid, '\n');
	split_array = ft_strsplit(grid, '\n');
	*x = (int)ft_count_word(split_array[0], ' ');
	while (++i < *y)
		if (ft_count_word(split_array[i], ' ') != *x)
			return (0);
	create_matrix(*x, *y, split_array, my_union);
	return (1);
}

void 	put_point(t_point *point, int i, int j, char *str, int size)
{
	char **tmp;

	tmp = NULL;
	if (ft_strchr(str, ','))
		tmp = ft_strsplit(str, ',');
	(point)->y = (float)i;
	(point)->x = (float)j;
	if (!tmp)
	{
		(point)->z = (float)ft_atoi(str);
		(point)->color = 0xFFFFFF;
	}
	else
	{
		(point)->z = (float)ft_atoi(tmp[0]);
		(point)->color = 0xFFFFFF;
	}
}

int 	create_matrix(int x, int y, char **split, t_union ***my_union)
{
	t_point **points;
	t_point **transform;
	int		i;
	int		j;
	char 	**substring;

	i = 0;
	points = (t_point **)malloc(sizeof(t_point *) * y);
	transform = (t_point **)malloc(sizeof(t_point *) * y);
	while (i < y)
	{
		transform[i] = (t_point *)malloc(sizeof(t_point) * x);
		points[i] = (t_point *)malloc(sizeof(t_point) * x);
		i++;
	}
	i = -1;
	while (++i < y)
	{
		j = -1;
		substring = ft_strsplit(split[i], ' ');
		while (++j < x)
			put_point(&points[i][j], i, j, substring[j], (**my_union)->scale);
	}
	(**my_union)->transform = transform;
	(**my_union)->points = points;
	return (1);
}

void	copy2trans(t_union **my_union)
{
	int i;
	int j;

	i = -1;
	while (++i < (*my_union)->grid_size_y)
	{
		j = -1;
		while (++j < (*my_union)->grid_size_x)
			(*my_union)->transform[i][j] = (*my_union)->points[i][j];
	}
}