/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:09:07 by piyu              #+#    #+#             */
/*   Updated: 2025/04/21 19:19:07 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_grid(void *param)
{
	t_fdf	*fdf;
	int		i;
	int		w;
	int		h;
	int		mouse[2];

	i = 0;
	fdf = (t_fdf *)param;
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
	mlx_get_mouse_pos(fdf->mlx, &mouse[0], &mouse[1]);
	mlx_put_string(fdf->mlx, "3D Wireframe Map", 450, 20);
	mlx_put_string(fdf->mlx, "zoom: scroll  move: arrow keys  elevate: 1/2  \
	rotate: WASD or mouse left  projection: I/O", 20, 980);
}
