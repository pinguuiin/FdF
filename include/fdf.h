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
# ifndef ZOOM
#  define ZOOM 3
# endif

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h> ///
#include <stdlib.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"


typedef struct map_s
{
	int	w;
	int	h;
	int	max;
	int	min;
	int	**data;
}	map_t;

typedef struct point_s
{
	int	x;
	int	y;
	uint32_t	color;
}	point_t;

typedef struct fdf_s
{
	mlx_t	*mlx;
	mlx_image_t	*img;
	map_t	map;
	point_t *arr;
}	fdf_t;

typedef struct draw_s
{
	mlx_image_t	*img;
	point_t	a1;
	point_t	a2;
	int	dx;
	int	dy;
}	draw_t;

void	parse_map(int fd, map_t *map);
point_t	*array_to_coordinates(fdf_t fdf, int zoom);
uint32_t	color(point_t start, point_t end, double w);
void	draw_line(mlx_image_t *img, point_t a1, point_t a2);
void	draw_grid(void *param);

#endif
