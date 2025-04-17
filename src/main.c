/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:09:12 by piyu              #+#    #+#             */
/*   Updated: 2025/04/17 03:09:14 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	escape_func(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	initialize_struct(map_t *map, fdf_t *fdf)
{
	fdf->map = *map;
	fdf->zoom = INIT_ZOOM;
	fdf->offset[0] = (WIN_W - map->w * fdf->zoom) / 2;
	fdf->offset[1] = (WIN_H - (map->h + map->max - map->min) * fdf->zoom) / 2;
	fdf->coord = ft_calloc(map->w * map->h, sizeof(point_t));
	if (fdf->coord == NULL)
		free_exit(fdf, "Error allocating array", 0);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	fdf->mlx = mlx_init(WIN_W, WIN_H, "Fdf", true);
	if (!fdf->mlx)
		free_exit(fdf, "Instance initializing failed", 0);
	fdf->img = mlx_new_image(fdf->mlx, WIN_W, WIN_H);
	if (!fdf->img)
		free_exit(fdf, "Creating new image buffer failed", 0);
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) == -1)
		free_exit(fdf, "Drawing image on the window failed", 0);
	array_to_coordinates(fdf);
}

void	zooming(double xdelta, double ydelta, void *param)
{
	fdf_t	*fdf;

	(void)xdelta;
	fdf = (fdf_t *)param;
	if (ydelta > 0)
		fdf->zoom = 1.10;
	else if (ydelta < 0)
		fdf->zoom = 0.91;
	zoom_coordinates(fdf);
}

int	main(int argc, char **argv)
{
	int		fd;
	map_t	map;
	fdf_t	fdf;

	if (argc != 2)
		message_exit("Invalid input. Example: ./fdf map.fdf", 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		message_exit("Error", 1);
	parse_map(fd, &map);
	initialize_struct(&map, &fdf);
	//draw_grid(&fdf);
	mlx_loop_hook(fdf.mlx, escape_func, fdf.mlx);
	mlx_loop_hook(fdf.mlx, draw_grid, &fdf);
	mlx_scroll_hook(fdf.mlx, zooming, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free(fdf.coord);
	free(fdf.map.data);
	return (0);
}
