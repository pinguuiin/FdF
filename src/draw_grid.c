/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:09:07 by piyu              #+#    #+#             */
/*   Updated: 2025/04/17 03:09:08 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_grid(void *param)
{
	fdf_t	*fdf;
	int		i;
	int		w;
	int		h;

	i = 0;
	fdf = (fdf_t *)param;
	w = fdf->map.w;
	h = fdf->map.h;
	ft_memset(fdf->img->pixels, 0x00, WIN_H * WIN_W * 4);
	while (i < h * w)
	{
		if (i % w != w - 1)
			draw_line(fdf->img, fdf->coord[i], fdf->coord[i + 1]);
		if (i < (h - 1) * w)
			draw_line(fdf->img, fdf->coord[i], fdf->coord[i + w]);
		i++;
	}
	//mlx_put_string(fdf->mlx, "3D Wireframe Map", fdf->coord[0].x - 170, fdf->coord[i].y + 800);
}
