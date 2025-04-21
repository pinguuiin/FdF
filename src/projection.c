/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 23:22:35 by piyu              #+#    #+#             */
/*   Updated: 2025/04/21 21:39:47 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Convert array data into spatial coordinates */
void	array_to_xyz(t_fdf *fdf)
{
	int	i;
	int	j;
	int	idx;

	i = 0;
	while (i < fdf->map.h)
	{
		j = 0;
		while (j < fdf->map.w)
		{
			idx = fdf->map.w * i + j;
			fdf->coord[idx].x3 = (double)j - fdf->map.w / 2.0;
			fdf->coord[idx].y3 = (double)i - fdf->map.h / 2.0;
			fdf->coord[idx].z3 = fdf->map.data[idx];
			j++;
		}
		i++;
	}
}

/* Orthographic projection with top view */
static void	ortho_top(t_fdf *fdf, double x_offset, double y_offset)
{
	int	i;

	i = 0;
	while (i < fdf->map.w * fdf->map.h)
	{
		fdf->coord[i].x = fdf->coord[i].x3 * fdf->zoom + x_offset;
		fdf->coord[i].y = fdf->coord[i].y3 * fdf->zoom + y_offset;
		fdf->coord[i].color = color_data(i, fdf->map, 1);
		i++;
	}
}

/* Orthographic projection with left side view */
static void	ortho_side(t_fdf *fdf, double x_offset, double y_offset)
{
	int	i;

	i = 0;
	while (i < fdf->map.w * fdf->map.h)
	{
		fdf->coord[i].x = fdf->coord[i].y3 * fdf->zoom + x_offset;
		fdf->coord[i].y = -fdf->coord[i].z3 * fdf->zoom + y_offset;
		fdf->coord[i].color = color_data(i, fdf->map, 1);
		i++;
	}
}

/* Project spatial coordinates to map with isometric projection as default
 * @param fdf The fdf struct which includes everything
 * @param x_offset offset on x axis
 * @param y_offset offset on y axis
 */
void	array_to_coordinates(t_fdf *fdf, double x_offset, double y_offset)
{
	int	i;

	if (fdf->proj == 'I')
	{
		i = 0;
		while (i < fdf->map.w * fdf->map.h)
		{
			fdf->coord[i].x = (fdf->coord[i].x3 - fdf->coord[i].y3) \
			* cos(M_PI / 6.0) * fdf->zoom + x_offset;
			fdf->coord[i].y = ((fdf->coord[i].x3 + fdf->coord[i].y3) \
			* sin(M_PI / 6.0) - fdf->coord[i].z3) * fdf->zoom + y_offset;
			fdf->coord[i].color = color_data(i, fdf->map, fdf->elev_factor);
			i++;
		}
	}
	else if (fdf->proj == 'O' && fdf->ortho_view == 1)
		ortho_top(fdf, x_offset, y_offset);
	else if (fdf->proj == 'O' && fdf->ortho_view == 2)
		ortho_side(fdf, x_offset, y_offset);
}

void	switch_projection(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_I)
	{
		free(fdf->coord);
		initialize_struct(&(fdf->map), fdf, 'I');
	}
	else if (keydata.key == MLX_KEY_O || (fdf->proj == 'O' \
	&& (keydata.key == MLX_KEY_KP_1 || keydata.key == MLX_KEY_KP_2)))
	{
		if (keydata.key == MLX_KEY_O || keydata.key == MLX_KEY_KP_1)
			fdf->ortho_view = 1;
		if (keydata.key == MLX_KEY_KP_2)
			fdf->ortho_view = 2;
		{
			free(fdf->coord);
			initialize_struct(&(fdf->map), fdf, 'O');
		}
	}
}
