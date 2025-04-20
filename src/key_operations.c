/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 03:15:56 by piyu              #+#    #+#             */
/*   Updated: 2025/04/20 04:24:12 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move_coordinates(fdf_t *fdf, int horizontal_incre, int vertical_incre)
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
	if (keydata.key == MLX_KEY_LEFT)
		move_coordinates(fdf, -1, 0);
	if (keydata.key == MLX_KEY_RIGHT)
		move_coordinates(fdf, 1, 0);
	if (keydata.key == MLX_KEY_UP)
		move_coordinates(fdf, 0, -1);
	if (keydata.key == MLX_KEY_DOWN)
		move_coordinates(fdf, 0, 1);
}

void	tune_map(fdf_t *fdf, double incre)
{
	int	i;

	i = 0;
	while (i < fdf->map.w * fdf->map.h)
	{
		fdf->coord[i].z3 *= incre;
		i++;
	}
}

void	tune_elevation(mlx_key_data_t keydata, fdf_t *fdf)
{
	double	offset_vertex[2];

	fdf->zoom = fdf->zoom_cumulation;
	offset_vertex[0] = fdf->coord[0].x - (fdf->coord[0].x3 - fdf->coord[0].y3) * cos(M_PI / 6.0) * fdf->zoom;
	offset_vertex[1] = fdf->coord[0].y - ((fdf->coord[0].x3 + fdf->coord[0].y3) * sin(M_PI / 6.0) \
	- fdf->coord[0].z3) * fdf->zoom;
	if (keydata.key == MLX_KEY_1)
		tune_map(fdf, 0.91);
	else if (keydata.key == MLX_KEY_2)
		tune_map(fdf, 1.10);
	array_to_coordinates(fdf, fdf->zoom, offset_vertex[0], offset_vertex[1]);
}
