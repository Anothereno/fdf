/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:07:27 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/13 17:48:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_max_minz(t_union **my_union)
{
	UPTR->ints->i = -1;
	UPTR->max_z = UPTR->points[0][0].z;
	UPTR->min_z = UPTR->points[0][0].z;
	while (++UPTR->ints->i < UPTR->grid_size_y)
	{
		UPTR->ints->j = -1;
		while (++UPTR->ints->j < UPTR->grid_size_x)
		{
			if (UPTR->points[UPTR->ints->i][UPTR->ints->j].z
				> UPTR->max_z)
				UPTR->max_z = UPTR->points[UPTR->ints->i][UPTR->ints->j].z;
			if (UPTR->points[UPTR->ints->i][UPTR->ints->j].z
				< UPTR->min_z)
				UPTR->min_z = UPTR->points[UPTR->ints->i][UPTR->ints->j].z;
		}
	}
	UPTR->ave = (UPTR->max_z + UPTR->min_z) / 2;
}

int		grid_valid(t_union ***my_union, char *grid, int *x, int *y)
{
	char	**split_array;
	int		i;

	i = 0;
	(*UPTR)->line = (t_line*)malloc(sizeof(t_line));
	(*UPTR)->ints = (t_int*)malloc(sizeof(t_int));
	(*UPTR)->color = (t_color*)malloc(sizeof(t_color));
	(*UPTR)->max_color = 0xe600f7;
	(*UPTR)->min_color = 0x039b0a;
	*y = (int)ft_count_word(grid, '\n');
	split_array = ft_strsplit(grid, '\n');
	*x = (int)ft_count_word(split_array[0], ' ');
	while (++i < *y)
		if (ft_count_word(split_array[i], ' ') != *x)
			print_error("Wrong rows/columns number", **my_union);
	create_matrix(*x, *y, split_array, my_union);
	clear_array(split_array);
	set_max_minz(*my_union);
	set2default(*my_union);
	return (1);
}

void	print_error(const char *msg, t_union *my_union)
{
	ft_putstr(msg);
	if (my_union)
		exit_(my_union);
	else
		exit(0);
}

void	valid_color(char *st, t_point *point, t_union ***my_union)
{
	int		i;
	char	*end;

	i = 1;
	if (st && ft_strlen(st) <= 8 && st[0] == '0' &&
		(st[1] == 'x' || st[1] == 'X'))
	{
		while (++i < ft_strlen(st))
		{
			if ((st[i] >= '0' && st[i] <= '9') || (st[i] >= 'a' &&
			st[i] <= 'f') || (st[i] >= 'A' && st[i] <= 'F'))
				continue;
			else
				print_error("Wrong color", **my_union);
		}
		point->color = strtol(st, &end, 16);
	}
	else
		print_error("Wrong color", **my_union);
}

void	put_point(t_point *point, char *str, t_union ***my_union)
{
	char **tmp;

	tmp = NULL;
	if (ft_strchr(str, ','))
		tmp = ft_strsplit(str, ',');
	point->y = (**my_union)->ints->i;
	point->x = (**my_union)->ints->j;
	if (!tmp)
	{
		point->z = ft_atoi(str);
		point->color = -1;
	}
	else
	{
		point->z = ft_atoi(tmp[0]);
		valid_color(tmp[1], point, my_union);
		clear_array(tmp);
	}
}

void	create_matrix(int x, int y, char **split, t_union ***my_union)
{
	t_point **points;
	t_point **transform;
	int		i;
	int		j;
	char	**substring;

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
		{
			(**my_union)->ints->i = i;
			(**my_union)->ints->j = j;
			put_point(&points[i][j], substring[j], my_union);
		}
		clear_array(substring);
	}
	(**my_union)->transform = transform;
	(**my_union)->points = points;
}
