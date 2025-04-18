/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_coordinates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:09:03 by piyu              #+#    #+#             */
/*   Updated: 2025/04/18 21:19:09 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint8_t	normalize(double value, double max, double min)
{
	uint8_t	normed_value;

	normed_value = (uint8_t)(((value - min) / (max - min)) * 255);
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

	i = 0;
	while (i < fdf->map.h)
	{
		j = 0;
		while (j < fdf->map.w)
		{
			fdf->coord[fdf->map.w * i + j].x = (j - i) * cos(M_PI / 6.0) * fdf->zoom + fdf->offset[0];
			fdf->coord[fdf->map.w * i + j].y = ((i + j) * sin(M_PI / 6.0) \
			- fdf->map.data[fdf->map.w * i + j]) * fdf->zoom + fdf->offset[1];
			fdf->coord[fdf->map.w * i + j].color = color_data(fdf->map.w * i + j, fdf->map);
			// printf("x:%i\t", fdf->coord[w * i + j].x);
			// printf("y:%i\n", fdf->coord[w * i + j].y);
			j++;
		}
		i++;
	}
}
