/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_coordinates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:09:03 by piyu              #+#    #+#             */
/*   Updated: 2025/04/17 03:09:04 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint8_t	normalize(int value, int max, int min)
{
	uint8_t	normed_value;

	normed_value = (uint8_t)(((double)(value - min) / (max - min)) * 255);
	return (normed_value);
}

static uint32_t	color_data(int i, map_t map)
{
	uint8_t	normed_value;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	if (map.max == map.min)
		return (0xFFFFFFFF);
	normed_value = normalize(map.data[i], map.max, map.min);
	r = 70 + normed_value * 0.8;
	g = 30 + normed_value * 0.8;
	b = 205 - normed_value * 0.8;
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	array_to_coordinates(fdf_t *fdf)
{
	int	i;
	int	j;
	int	w;
	int	h;

	w = fdf->map.w;
	h = fdf->map.h;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			fdf->coord[w * i + j].x = (j - i) * cos(M_PI / 6.0) * fdf->zoom + fdf->offset[0];
			fdf->coord[w * i + j].y = ((i + j) * sin(M_PI / 6.0) \
			- fdf->map.data[w * i + j]) * fdf->zoom + fdf->offset[1];
			fdf->coord[w * i + j].color = color_data(w * i + j, fdf->map);
			// printf("x:%i\t", fdf->coord[w * i + j].x);
			// printf("y:%i\n", fdf->coord[w * i + j].y);
			j++;
		}
		i++;
	}
}

void	zoom_coordinates(fdf_t *fdf)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	mlx_get_mouse_pos(fdf->mlx, &x, &y);
	while (i < fdf->map.w * fdf->map.h)
	{
		fdf->coord[i].x = (fdf->coord[i].x - x) * fdf->zoom + x;
		fdf->coord[i].y = (fdf->coord[i].y - y) * fdf->zoom + y;
		// printf("x:%f\t", fdf->coord[i].x);
		// printf("y:%f\n\n", fdf->coord[i].y);
		i++;
	}
}
