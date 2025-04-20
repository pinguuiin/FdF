/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:05:56 by piyu              #+#    #+#             */
/*   Updated: 2025/04/20 03:38:48 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(fdf_t *fdf, double rad)
{
	int		i;
	double	temp;

	i = 0;
	while (i < fdf->map.w * fdf->map.h)
	{
		temp = fdf->coord[i].y3;
		fdf->coord[i].y3 = fdf->coord[i].y3 * cos(rad) - fdf->coord[i].z3 * sin(rad);
		fdf->coord[i].z3 = fdf->coord[i].z3 * cos(rad) + temp * sin(rad);
		i++;
	}
}

void	rotate_y(fdf_t *fdf, double rad)
{
	int		i;
	double	temp;

	i = 0;
	while (i < fdf->map.w * fdf->map.h)
	{
		temp = fdf->coord[i].x3;
		fdf->coord[i].x3 = fdf->coord[i].x3 * cos(rad) + fdf->coord[i].z3 * sin(rad);
		fdf->coord[i].z3 = fdf->coord[i].z3 * cos(rad) - temp * sin(rad);
		i++;
	}
}

void	rotate_z(fdf_t *fdf, double rad)
{
	int		i;
	double	temp;

	i = 0;
	while (i < fdf->map.w * fdf->map.h)
	{
		temp = fdf->coord[i].x3;
		fdf->coord[i].x3 = fdf->coord[i].x3 * cos(rad) - fdf->coord[i].y3 * sin(rad);
		fdf->coord[i].y3 = fdf->coord[i].y3 * cos(rad) + temp * sin(rad);
		i++;
	}
}

void	rotate(mlx_key_data_t keydata, fdf_t *fdf)
{
	double	offset_vertex[2];

	fdf->zoom = fdf->zoom_cumulation;
	offset_vertex[0] = fdf->coord[0].x - (fdf->coord[0].x3 - fdf->coord[0].y3) * cos(M_PI / 6.0) * fdf->zoom;
	offset_vertex[1] = fdf->coord[0].y - ((fdf->coord[0].x3 + fdf->coord[0].y3) * sin(M_PI / 6.0) \
	- fdf->coord[0].z3) * fdf->zoom;
	if (keydata.key == MLX_KEY_A)
		rotate_z(fdf, 0.5);
	if (keydata.key == MLX_KEY_D)
		rotate_z(fdf, -0.5);
	if (keydata.key == MLX_KEY_W)
	{
		rotate_x(fdf, 0.25);
		rotate_y(fdf, -0.25);
	}
	if (keydata.key == MLX_KEY_S)
	{
		rotate_x(fdf, -0.25);
		rotate_y(fdf, 0.25);
	}
	array_to_coordinates(fdf, fdf->zoom, offset_vertex[0], offset_vertex[1]);
}
