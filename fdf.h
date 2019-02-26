/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:51:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/02/26 18:15:59 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_FDF_H
# define FDF_FDF_H
# define ABS(x) (x < 0) ? x = -x : x
# define TR (my_union)->transform
# define uptr (*my_union)
# include "mlx.h"
# include <math.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>

typedef struct	s_point
{
	int x;
	int y;
	int z;
	int color;
}				t_point;

typedef struct	s_union
{
	void	*mlx_ptr;
	void	*win_ptr;
	int 	size;
	int		win_x;
	int 	shift_x;
	int 	shift_y;
	int		win_y;
	char	mode;
	int 	grid_size_x;
	int 	grid_size_y;
	t_point	**points;
	t_point	**transform;
}				t_union;

void			reshift(t_union **my_union);
void			resize_coordinates(t_union **my_union, int old_size);
void			shift_coordinates(t_union **my_union);
void			shift_x(int key, t_union *my_union);
void			shift_y(int key, t_union *my_union);
void			copy2trans(t_union **my_union);
void			zoom(int key, t_union *my_union);
void			trans_iso(t_union *my_union);
void			isometric(int *x, int *y, int z, t_union *my_union);
int 			create_matrix(int x, int y, char **coordinates, t_union ***my_union);
void			exit_(t_union *my_union);
int				mouse_press(int key, void *param);
void			plot_grid(t_union *my_union);
int 			mouse_move(int key, void *param);
int				grid_valid(t_union ***my_union, char *grid, int *x, int *y);
int				deal_key(int key, void *param);
int				take_sign(int x);
void			plot_line(int x0, int y0, int  x1, int  y1, t_union *my_union);
char			*take_coordinates(char *argv);
char			*reading(int fd);
void			struct_initial(t_union **my_union, char *res);

#endif
