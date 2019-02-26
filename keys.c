/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:55:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/02/26 16:59:47 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_(t_union *my_union)
{
	free(my_union);
	my_union = NULL;
	exit(0);
}

int		deal_key(int key, void *param)
{
//	ft_putnbr(key);
	if (key == 53)
		exit_((t_union*)param);
	if (key == 34)
		trans_iso((t_union*)param);
	if (key == 78 || key == 69)
		zoom(key, (t_union*)param);
	if (key == 13 || key == 1)
		shift_y(key, (t_union*)param);
	if (key == 0 || key == 2)
		shift_x(key, (t_union*)param);
//	if (key == 123 || key == 124)
//		rotate_x(key, (t_union*)param);
	return (0);
}

int		mouse_move(int key, void *param)
{
	ft_putstr("MOVE\n");
	return (0);
}

int		mouse_press(int key, void *param)
{
	/*if (key == 4)
		zoom('-', (t_union**)param);
	if (key == 5)
		zoom('+', (t_union**)param);
	return (0);*/
}