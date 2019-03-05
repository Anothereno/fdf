/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:07:27 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/05 16:17:18 by hdwarven         ###   ########.fr       */
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

void	clear_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_strdel(&array[i]);
		i++;
	}
	free(array);
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
		{
			ft_putstr("Wrong rows/columns number");
			exit_(**my_union);
		}
	create_matrix(*x, *y, split_array, my_union);
	clear_array(split_array);
	return (1);
}

void	valid_color(char *st, t_point *point, t_union ***my_union)
{
	int		i;
	char	*end;

	i = 1;
	if (st && ft_strlen(st) == 8 && st[0] == '0' && (st[1] == 'x' || st[1] == 'X'))
	{
		while (++i < 8)
		{
			if ((st[i] >= '0' && st[i] <= '9') ||
			(st[i] >= 'a' && st[i] <= 'f') ||
			(st[i] >= 'A' && st[i] <= 'F'))
				continue;
			else
			{
				ft_putstr("Wrong color");
				exit_(**my_union);
			}
		}
		point->color = strtol(st, &end, 16);
	}
	else
	{
		ft_putstr("Wrong color");
		exit_(**my_union);
	}
}

void 	put_point(t_point *point, int i, int j, char *str, t_union ***my_union)
{
	char **tmp;

	tmp = NULL;
	if (ft_strchr(str, ','))
		tmp = ft_strsplit(str, ',');
	point->y = i;
	point->x = j;
	if (!tmp)
	{
		point->z = ft_atoi(str);
		point->color = declare_color(point->z);
		point->true_z = point->z;
	}
	else
	{
		point->z = ft_atoi(tmp[0]);
		valid_color(tmp[1], point, my_union);
		point->true_z = point->z;
		clear_array(tmp);
	}
}

int 	create_matrix(int x, int y, char **split, t_union ***my_union)
{
	t_point **points;
	t_point **transform;
	int		i;
	int		j;
	char 	**substring;

	i = -1;
	points = (t_point **)malloc(sizeof(t_point *) * y);
	transform = (t_point **)malloc(sizeof(t_point *) * y);
	while (++i < y)
	{
		transform[i] = (t_point *)malloc(sizeof(t_point) * x);
		points[i] = (t_point *)malloc(sizeof(t_point) * x);
		j = -1;
		substring = ft_strsplit(split[i], ' ');
		while (++j < x)
			put_point(&points[i][j], i, j, substring[j], my_union);
		clear_array(substring);
	}
	(**my_union)->transform = transform;
	(**my_union)->points = points;
	return (1);
}