/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:31:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/07 16:06:43 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_union		*my_union;
	char		*coordinates;

	my_union = NULL;
	if (argc == 2)
	{
		coordinates = take_coordinates(argv[1]);
		struct_initial(&my_union, coordinates);
		plot_grid(my_union);
		mlx_hook(my_union->win_ptr, 2, 5, deal_key, my_union);
		mlx_loop(my_union->mlx_ptr);
	}
	else
		print_error("Wrong number of arguments\n", my_union);
	return (0);
}
