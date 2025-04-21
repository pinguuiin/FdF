/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 02:55:59 by piyu              #+#    #+#             */
/*   Updated: 2025/04/21 19:38:56 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# ifndef WIN_W
#  define WIN_W 1024
# endif
# ifndef WIN_H
#  define WIN_H 1024
# endif
# ifndef INIT_ZOOM
#  define INIT_ZOOM 20
# endif

# include "../src/libft/libft.h"
# include "../src/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_map
{
	int		w;
	int		h;
	double	max;
	double	min;
	double	*data;
}	t_map;

typedef struct s_point
{
	double		x3;
	double		y3;
	double		z3;
	double		x;
	double		y;
	uint32_t	color;
}	t_point;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		map;
	double		offset[2];
	double		zoom;
	double		zoom_cumulation;
	double		elev_factor;
	t_point		*coord;
	char		proj;
	int			ortho_view;
	int			prev_mouse;
	int			prev_x;
	int			prev_y;
}	t_fdf;

typedef struct s_draw
{
	mlx_image_t	*img;
	t_point		a1;
	t_point		a2;
	double		dx;
	double		dy;
	int			x;
	int			y;
}	t_draw;

uint32_t	color_data(int i, t_map map, double elev_factor);
uint32_t	color(t_point start, t_point end, double w);
void		draw_grid(void *param);
void		draw_line(mlx_image_t *img, t_point a1, t_point a2);
void		move(mlx_key_data_t keydata, t_fdf *fdf);
void		tune_elevation(mlx_key_data_t keydata, t_fdf *fdf);
void		initialize_struct(t_map *map, t_fdf *fdf, char proj);
void		mouse_track(void *param);
void		parse_map(int fd, t_map *map);
void		array_to_xyz(t_fdf *fdf);
void		array_to_coordinates(t_fdf *fdf, double x_offset, double y_offset);
void		switch_projection(mlx_key_data_t keydata, t_fdf *fdf);
void		rotate_x(t_fdf *fdf, double rad);
void		rotate_y(t_fdf *fdf, double rad);
void		rotate_z(t_fdf *fdf, double rad);
void		rotate(mlx_key_data_t keydata, t_fdf *fdf);
void		get_max_min(t_map *map);
void		get_center_offset(t_fdf *fdf);
void		message_exit(char *s, int sys_error_flag);
void		free_exit(t_fdf *fdf, char *s, int sys_error_flag);

#endif
