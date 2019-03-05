/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:07:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/04 17:33:38 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	struct_initial(t_union **my_union, char *res)
{
	if ((uptr = (t_union*)malloc(sizeof(t_union) * 1)))
	{
		uptr->win_x = 1920;
		uptr->win_y = 1080;
		uptr->shift_x = 0;
		uptr->shift_y = 0;
		uptr->x_angle = 0;
		uptr->y_angle = 0;
		uptr->kof = 2;
		uptr->z_angle = 0;
		uptr->mode = 'f';
		uptr->mlx_ptr = mlx_init();
		image_init(my_union);
		uptr->win_ptr = mlx_new_window(uptr->mlx_ptr,
				uptr->win_x, uptr->win_y, "fdf");
		if (!grid_valid(&my_union, res, &(uptr->grid_size_x), &(uptr->grid_size_y)))
			exit_(&my_union);
		uptr->scale = calc_scale(my_union);
	}
	else
		exit (0);
}

void	image_init(t_union **my_union)
{
	int	bits;
	int width;
	int flag;

	uptr->image_ptr = mlx_new_image(uptr->mlx_ptr, uptr->win_x, uptr->win_y);
	uptr->image_data = mlx_get_data_addr(uptr->image_ptr, &bits, &width, &flag);
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
	char	buff[1000001];
	char	*res;
	char	*tmp;
	int 	ret;

	res = ft_strdup("");
	while ((ret = read(fd, buff, 1000000)))
	{
		buff[ret] = '\0';
		tmp = res;
		res = ft_strjoin((const char *)res, (const char *)buff);
		ft_strdel(&tmp);
	}
	return (res);
}