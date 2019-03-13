/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:51:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/03/13 17:19:38 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_FDF_H
# define FDF_FDF_H
# define ABS(x) (x < 0) ? x = -x : x
# define MIN(a, b) (a < b) ? a : b
# define TR (my_union)->transform
# define UPTR (*my_union)
# include "mlx.h"
# include <math.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	long int	color;
}				t_point;

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct	s_line
{
	int			dx;
	int			dy;
	int			inclinex;
	int			incliney;
	int			signx;
	int			signy;
	int			error;
	int			longline;
	int			shortline;
	int			i;
}				t_line;

typedef struct	s_int
{
	int			i;
	int			j;
}				t_int;

typedef struct	s_union
{
	void		*image_ptr;
	void		*mlx_ptr;
	char		*image_data;
	void		*win_ptr;
	int			scale;
	int			win_x;
	int			shift_x;
	int 		max_z;
	int			min_z;
	int 		max_color;
	int 		min_color;
	int			kof;
	int			ave;
	int			x_angle;
	int			y_angle;
	char		delta;
	int			z_angle;
	int			shift_y;
	int			win_y;
	int			bpp;
	int			endian;
	int			sl;
	char		mode;
	int			grid_size_x;
	int			grid_size_y;
	t_int		*ints;
	t_line		*line;
	t_color		*color;
	t_point		**points;
	t_point		**transform;
}				t_union;

void			set2default(t_union **my_union);
int				calc_color(t_union **my_union, int i, int j);
void			print_line(t_point point0, t_point point1, t_union *my_union);
void			clear_array(char **array);
void			print_error(const char *msg, t_union *my_union);
void			image_put(t_union **my_union);
void			main_loop(t_union **my_union);
int				take_color(int start, int finish, double perc);
double			percent(int start, int finish, int point);
void			set_pixel(t_union **my_union, t_point point0, t_point point1);
void			image_init(t_union **my_union);
void			set_color(t_point point0, t_point point1, t_union **my_union);
int				calc_scale(t_union **my_union);
void			change_mode(t_union *my_union, char c);
void			sub_coordinates(t_union **my_union, int i, int j);
void			rotate_z_axis(t_union **my_union, int i, int j);
void			rotate_y_axis(t_union **my_union, int i, int j);
void			rotate_y(int key, t_union *my_union);
void			rotate_z(int key, t_union *my_union);
void			rotate_x(int key, t_union *my_union);
void			rotate_x_axis(t_union **my_union, int i, int j);
void			rotate_all_axis(t_union **my_union, int i, int j);
void			shift_coordinates(t_union **my_union, int i, int j);
void			shift_x(int key, t_union *my_union);
void			shift_y(int key, t_union *my_union);
void			zoom(int key, t_union *my_union);
void			isometric(int i, int j, t_union *my_union);
void			create_matrix(int x, int y, char **coordinates,
		t_union ***my_union);
void			exit_(t_union *my_union);
void			plot_grid(t_union *my_union);
int				grid_valid(t_union ***my_union, char *grid, int *x, int *y);
int				deal_key(int key, void *param);
int				take_sign(int x);
void			plot_line(t_point point0, t_point point1, t_union *my_union);
char			*take_coordinates(char *argv);
char			*reading(int fd);
void			struct_initial(t_union **my_union, char *res);

#endif
