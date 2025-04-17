#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# ifndef WIN_W
#  define WIN_W 2048
# endif
# ifndef WIN_H
#  define WIN_H 1024
# endif
# ifndef INIT_ZOOM
#  define INIT_ZOOM 20
# endif

#include "../src/libft/libft.h"
#include "../src/MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h> ///
#include <stdlib.h>
#include <math.h>

typedef struct map_s
{
	int	w;
	int	h;
	int	max;
	int	min;
	int	*data;
}	map_t;

typedef struct point_s
{
	double		x;
	double		y;
	uint32_t	color;
}	point_t;

typedef struct fdf_s
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	map_t		map;
	int			offset[2];
	double		zoom;
	point_t 	*coord;
}	fdf_t;

typedef struct draw_s
{
	mlx_image_t	*img;
	point_t		a1;
	point_t		a2;
	double		dx;
	double		dy;
	int			x;
	int			y;
}	draw_t;

void		message_exit(char *s, int sys_error_flag);
void		free_exit(fdf_t *fdf, char *s, int sys_error_flag);
void		get_max_min(map_t *map);
void		parse_map(int fd, map_t *map);
void		array_to_coordinates(fdf_t *fdf);
void		zoom_coordinates(fdf_t *fdf);
uint32_t	color(point_t start, point_t end, double w);
void		draw_line(mlx_image_t *img, point_t a1, point_t a2);
void		draw_grid(void *param);

#endif
