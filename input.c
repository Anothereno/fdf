/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:07:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/07 17:44:43 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	struct_initial(t_union **my_union, char *res)
{
	if ((UPTR = (t_union*)malloc(sizeof(t_union) * 1)))
	{
		UPTR->win_x = 1920;
		UPTR->win_y = 1080;
		UPTR->shift_x = 0;
		UPTR->shift_y = 0;
		UPTR->x_angle = 0;
		UPTR->y_angle = 0;
		UPTR->kof = 2;
		UPTR->z_angle = 0;
		UPTR->mode = 'f';
		UPTR->mlx_ptr = mlx_init();
		image_init(my_union);
		UPTR->win_ptr = mlx_new_window(UPTR->mlx_ptr,
				UPTR->win_x, UPTR->win_y, "fdf");
		if (!grid_valid(&my_union, res,
				&(UPTR->grid_size_x), &(UPTR->grid_size_y)))
			exit_(&my_union);
		UPTR->scale = calc_scale(my_union);
	}
	else
		exit(0);
}

void	image_init(t_union **my_union)
{
	UPTR->image_ptr = mlx_new_image(UPTR->mlx_ptr,
			UPTR->win_x, UPTR->win_y);
	UPTR->image_data = mlx_get_data_addr(UPTR->image_ptr,
			&(UPTR->bpp), &(UPTR->sl), &(UPTR->endian));
}

void	image_put(t_union **my_union)
{
	mlx_put_image_to_window(UPTR->mlx_ptr,
			UPTR->win_ptr, UPTR->image_ptr, 0, 0);
	mlx_destroy_image(UPTR->mlx_ptr, UPTR->image_ptr);
}

char	*take_coordinates(char *argv)
{
	int		fd;
	int		fnamelen;

	fnamelen = ft_strlen(argv);
	if ((fd = open(argv, O_RDONLY)) < 3 || argv[fnamelen - 4] != '.' ||
		argv[fnamelen - 3] != 'f' || argv[fnamelen - 2] != 'd' ||
		argv[fnamelen - 1] != 'f')
		print_error("Can't open the file or filename wrong\n", NULL);
	else
		return (reading(fd));
}

char	*reading(int fd)
{
	char	buff[1000001];
	char	*res;
	char	*tmp;
	int		ret;

	res = ft_strdup("");
	if (read(fd, NULL, 0) >= 0)
	{
		while ((ret = read(fd, buff, 1000000)))
		{
			buff[ret] = '\0';
			tmp = res;
			res = ft_strjoin((const char *)res, (const char *)buff);
			ft_strdel(&tmp);
		}
		close(fd);
		return (res);
	}
	else
		print_error("Wrong file\n", NULL);
}
