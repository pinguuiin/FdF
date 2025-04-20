/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 23:22:35 by piyu              #+#    #+#             */
/*   Updated: 2025/04/20 02:33:53 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	array_to_xyz(fdf_t *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.h)
	{
		j = 0;
		while (j < fdf->map.w)
		{
			fdf->coord[fdf->map.w * i + j].x3 = (double)j - fdf->map.w / 2.0;
			fdf->coord[fdf->map.w * i + j].y3 = (double)i - fdf->map.h / 2.0;
			fdf->coord[fdf->map.w * i + j].z3 = fdf->map.data[fdf->map.w * i + j];
			j++;
		}
		i++;
	}
}

void	array_to_coordinates(fdf_t *fdf, double zoom, double x_offset, double y_offset)
{
	int	i;

	i = 0;
	while (i < fdf->map.w * fdf->map.h)
	{
		fdf->coord[i].x = (fdf->coord[i].x3 - fdf->coord[i].y3) * cos(M_PI / 6.0) * zoom + x_offset;
		fdf->coord[i].y = ((fdf->coord[i].x3 + fdf->coord[i].y3) * sin(M_PI / 6.0) \
		- fdf->coord[i].z3) * zoom + y_offset;
		fdf->coord[i].color = color_data(i, fdf->map);
		// printf("x:%i\t", fdf->coord[w * i + j].x);
		// printf("y:%i\n", fdf->coord[w * i + j].y);
		i++;
	}
}


