/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:09:12 by piyu              #+#    #+#             */
/*   Updated: 2025/04/21 21:30:53 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize_struct(t_map *map, t_fdf *fdf, char proj)
{
	fdf->map = *map;
	fdf->proj = proj;
	fdf->zoom = INIT_ZOOM;
	fdf->zoom_cumulation = INIT_ZOOM;
	fdf->elev_factor = 1;
	fdf->coord = ft_calloc(map->w * map->h, sizeof(t_point));
	if (fdf->coord == NULL)
		free_exit(fdf, "Error allocating array", 0);
	array_to_xyz(fdf);
	array_to_coordinates(fdf, 0, 0);
	get_center_offset(fdf);
	array_to_coordinates(fdf, fdf->offset[0], fdf->offset[1]);
}

static void	initialize_mlx(t_fdf *fdf)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	fdf->mlx = mlx_init(WIN_W, WIN_H, "Fdf", true);
	if (!fdf->mlx)
		free_exit(fdf, "Instance initializing failed", 0);
	fdf->img = mlx_new_image(fdf->mlx, WIN_W, WIN_H);
	if (!fdf->img)
		free_exit(fdf, "Creating new image buffer failed", 0);
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) == -1)
		free_exit(fdf, "Drawing image on the window failed", 0);
}

static void	zooming(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;
	int		i;
	int		x;
	int		y;

	i = 0;
	(void)xdelta;
	fdf = (t_fdf *)param;
	if (fdf->zoom_cumulation > 150 && ydelta > 0)
		return ;
	if (fdf->zoom_cumulation < 0.01 && ydelta < 0)
		return ;
	if (ydelta > 0)
		fdf->zoom = 1.10;
	else if (ydelta < 0)
		fdf->zoom = 0.91;
	mlx_get_mouse_pos(fdf->mlx, &x, &y);
	while (i < fdf->map.w * fdf->map.h)
	{
		fdf->coord[i].x = (fdf->coord[i].x - x) * fdf->zoom + x;
		fdf->coord[i].y = (fdf->coord[i].y - y) * fdf->zoom + y;
		i++;
	}
	fdf->zoom_cumulation *= fdf->zoom;
}

static void	key_operations(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
	else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT \
	||keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
		move(keydata, fdf);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_A \
	||keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D)
		rotate(keydata, fdf);
	else if (keydata.key == MLX_KEY_1 || keydata.key == MLX_KEY_2)
		tune_elevation(keydata, fdf);
	else if (keydata.key == MLX_KEY_I || keydata.key == MLX_KEY_O \
	|| keydata.key == MLX_KEY_KP_1 || keydata.key == MLX_KEY_KP_2)
		switch_projection(keydata, fdf);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	map;
	t_fdf	fdf;

	if (argc != 2)
		message_exit("Invalid input. Example: ./fdf map.fdf", 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		message_exit("Error", 1);
	fdf.mlx = NULL;
	fdf.img = NULL;
	parse_map(fd, &map);
	initialize_struct(&map, &fdf, 'I');
	initialize_mlx(&fdf);
	mlx_scroll_hook(fdf.mlx, zooming, &fdf);
	mlx_key_hook(fdf.mlx, key_operations, &fdf);
	mlx_loop_hook(fdf.mlx, mouse_track, &fdf);
	mlx_loop_hook(fdf.mlx, draw_grid, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free(fdf.coord);
	free(fdf.map.data);
	return (0);
}
