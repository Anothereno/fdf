/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:55:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/02/27 22:31:38 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_(t_union *my_union)
{
	free(my_union);
	exit(0);
}

int		deal_key(int key, void *param)
{
	//ft_putnbr(key);
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