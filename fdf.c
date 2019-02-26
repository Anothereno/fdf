/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:31:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/02/23 19:00:28 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
	t_union		*my_union;
	char		*coordinates;

	if (argc == 2)
	{
		coordinates = take_coordinates(argv[1]);
		struct_initial(&my_union, coordinates);
		plot_grid(my_union);
		//НЕ УДАЛЯТЬ !!!!! mlx_hook(mlx->win_ptr, 6, 0, mouse_move, 0);
		mlx_key_hook(my_union->win_ptr, deal_key, my_union);
		mlx_mouse_hook(my_union->win_ptr, mouse_press, my_union);
		mlx_loop(my_union->mlx_ptr);
	}
	else
		ft_putstr("Wrong number of arguments\n");
	return (0);
}