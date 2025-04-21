/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 03:15:56 by piyu              #+#    #+#             */
/*   Updated: 2025/04/21 20:23:11 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move_coordinates(t_fdf *fdf, int h_incre, int v_incre)
{
	int	i;

	i = 0;
	while (i < fdf->map.w * fdf->map.h)
	{
		fdf->coord[i].x += h_incre * 20;
		fdf->coord[i].y += v_incre * 20;
		i++;
	}
}

void	move(mlx_key_data_t keydata, t_fdf *fdf)
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

static void	tune_map(t_fdf *fdf, double factor)
{
	int	i;

	i = 0;
	if (fdf->elev_factor > 30 && factor > 1)
		return ;
	if (fdf->elev_factor < 0.001 && factor < 1)
		return ;
	while (i < fdf->map.w * fdf->map.h)
	{
		fdf->coord[i].z3 *= factor;
		i++;
	}
	fdf->elev_factor *= factor;
}

void	tune_elevation(mlx_key_data_t keydata, t_fdf *fdf)
{
	double	offset_vertex[2];

	if (fdf->proj == 'O')
		return ;
	fdf->zoom = fdf->zoom_cumulation;
	offset_vertex[0] = fdf->coord[0].x - (fdf->coord[0].x3 \
	- fdf->coord[0].y3) * cos(M_PI / 6.0) * fdf->zoom;
	offset_vertex[1] = fdf->coord[0].y - ((fdf->coord[0].x3 \
	+ fdf->coord[0].y3) * sin(M_PI / 6.0) - fdf->coord[0].z3) * fdf->zoom;
	if (keydata.key == MLX_KEY_1)
		tune_map(fdf, 0.91);
	else if (keydata.key == MLX_KEY_2)
		tune_map(fdf, 1.10);
	array_to_coordinates(fdf, offset_vertex[0], offset_vertex[1]);
}
