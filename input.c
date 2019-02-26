/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:07:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/02/23 16:32:33 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	struct_initial(t_union **my_union, char *res)
{
	if (((*my_union) = (t_union*)malloc(sizeof(t_union) * 1)))
	{
		(*my_union)->size = 50;
		(*my_union)->win_x = 1920;
		uptr->shift_x = 10;
		uptr->shift_y = 10;
		(*my_union)->win_y = 1080;
		(*my_union)->mlx_ptr = mlx_init();
		(*my_union)->win_ptr = mlx_new_window((*my_union)->mlx_ptr,
				(*my_union)->win_x, (*my_union)->win_y, "fdf");
		if (!grid_valid(&my_union, res, &((*my_union)->grid_size_x), &((*my_union)->grid_size_y)))
			exit_(&my_union);
		copy2trans(my_union);
	}
	else
		exit (0);
}

char 	*take_coordinates(char *argv)
{
	int		fd;

	if ((fd = open(argv, O_RDONLY)) < 3)
	{
		ft_putstr("Can't open the file\n");
		exit(0);
	}
	else
		return (reading(fd));
}

char 	*reading(int fd)
{
	char	buff[33];
	char	*res;
	char	*tmp;
	int 	ret;

	res = ft_strdup("");
	while ((ret = read(fd, buff, 32)))
	{
		buff[ret] = '\0';
		tmp = res;
		res = ft_strjoin((const char *)res, (const char *)buff);
		ft_strdel(&tmp);
	}
	return (res);
}