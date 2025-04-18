/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 03:15:56 by piyu              #+#    #+#             */
/*   Updated: 2025/04/18 23:04:53 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_coordinates(fdf_t *fdf, int horizontal_incre, int vertical_incre)
{
	int	i;

	i = 0;
	while (i < fdf->map.w * fdf->map.h)
	{
		fdf->coord[i].x += horizontal_incre * 20;
		fdf->coord[i].y += vertical_incre * 20;
		i++;
	}
}

void	move(mlx_key_data_t keydata, fdf_t *fdf)
{
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		move_coordinates(fdf, -1, 0);
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		move_coordinates(fdf, 1, 0);
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		move_coordinates(fdf, 0, -1);
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		move_coordinates(fdf, 0, 1);
}

void	tune_map(map_t *map, double incre)
{
	int	i;

	i = 0;
	while (i < map->w * map->h)
	{
		map->data[i] *= incre;
		i++;
	}
}

void	tune_elevation(mlx_key_data_t keydata, fdf_t *fdf)
{
	if (keydata.key == MLX_KEY_1)
		tune_map(&(fdf->map), 0.91);
	else if (keydata.key == MLX_KEY_2)
		tune_map(&(fdf->map), 1.10);
	fdf->zoom = fdf->zoom_cumulation;
	get_coordinate_offset(fdf);
	fdf->offset[0] = fdf->offset_init[0] - fdf->offset[0];
	fdf->offset[1] = fdf->offset_init[1] - fdf->offset[1];
	array_to_coordinates(fdf);
}
