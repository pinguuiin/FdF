/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 03:08:04 by piyu              #+#    #+#             */
/*   Updated: 2025/04/21 19:33:45 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	mouse_rotate(t_fdf *fdf, int dx, int dy)
{
	double	offset_vertex[2];

	fdf->zoom = fdf->zoom_cumulation;
	offset_vertex[0] = fdf->coord[0].x - (fdf->coord[0].x3 \
	- fdf->coord[0].y3) * cos(M_PI / 6.0) * fdf->zoom;
	offset_vertex[1] = fdf->coord[0].y - ((fdf->coord[0].x3 \
	+ fdf->coord[0].y3) * sin(M_PI / 6.0) - fdf->coord[0].z3) * fdf->zoom;
	rotate_z(fdf, -(double)dx / 100.0);
	rotate_x(fdf, -(double)dy / 200.0);
	rotate_y(fdf, (double)dy / 200.0);
	array_to_coordinates(fdf, offset_vertex[0], offset_vertex[1]);
}

void	mouse_track(void *param)
{
	t_fdf	*fdf;
	int		x;
	int		y;

	fdf = (t_fdf *)param;
	if (fdf->proj == 'O')
		return ;
	mlx_get_mouse_pos(fdf->mlx, &x, &y);
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (fdf->prev_mouse == 1)
			mouse_rotate(fdf, x - fdf->prev_x, y - fdf->prev_y);
		mlx_get_mouse_pos(fdf->mlx, &(fdf->prev_x), &(fdf->prev_y));
		fdf->prev_mouse = 1;
	}
	else
		fdf->prev_mouse = 0;
}
