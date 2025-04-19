/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:08:41 by piyu              #+#    #+#             */
/*   Updated: 2025/04/19 18:59:49 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	swap_point(draw_t *f)
{
	point_t	temp;

	temp = f->a1;
	f->a1 = f->a2;
	f->a2 = temp;
	f->dx *= -1;
	f->dy *= -1;
}

// /** above_midraws a line horizontally
//  * @param img The mlx image
//  * @param a1 The a1ing point
//  * @param a2 The a2ing point
//  * @param dx Something needed
//  * @param dy The other something
//  */
static inline void	draw_line_hv(draw_t f)
{
	if ((f.dx == 0 && f.dy < 0) || (f.dy == 0 && f.dx < 0))
		swap_point(&f);
	f.x = (int)f.a1.x;
	f.y = (int)f.a1.y;
	if (f.dx == 0 && f.dy != 0)
	{
		while (f.y <= f.a2.y)
		{
			if ((f.x >= 0 && f.x < WIN_W) && (f.y >= 0 && f.y < WIN_H))
				mlx_put_pixel(f.img, f.x, f.y, color(f.a1, f.a2, \
					(f.y - f.a1.y) / f.dy));
			f.y++;
		}
	}
	else if (f.dy == 0 && f.dx != 0)
	{
		while (f.x <= f.a2.x)
		{
			if ((f.x >= 0 && f.x < WIN_W) && (f.y >= 0 && f.y < WIN_H))
				mlx_put_pixel(f.img, f.x, f.y, color(f.a1, f.a2, \
					(f.x - f.a1.x) / f.dx));
			f.x++;
		}
	}
}

static inline void	draw_line_flat(draw_t f)
{
	int		step;
	double	above_mid;

	step = 1;
	if (f.dy < 0)
		step = -1;
	f.dy *= step;
	above_mid = 2 * f.dy - f.dx;
	f.x = (int)f.a1.x;
	f.y = (int)f.a1.y;
	while (f.x <= f.a2.x)
	{
		if ((f.x >= 0 && f.x < WIN_W) && (f.y >= 0 && f.y < WIN_H))
			mlx_put_pixel(f.img, f.x, f.y, color(f.a1, f.a2, \
				(f.x - f.a1.x) / f.dx));
		if (above_mid > 0)
		{
			f.y += step;
			above_mid -= 2 * f.dx;
		}
		above_mid += 2 * f.dy;
		f.x++;
	}
}

static inline void	draw_line_steep(draw_t f)
{
	int		step;
	double	above_mid;

	step = 1;
	if (f.dx < 0)
		step = -1;
	f.dx *= step;
	above_mid = 2 * f.dx - f.dy;
	f.x = (int)f.a1.x;
	f.y = (int)f.a1.y;
	while (f.y <= f.a2.y)
	{
		if ((f.x >= 0 && f.x < WIN_W) && (f.y >= 0 && f.y < WIN_H))
			mlx_put_pixel(f.img, f.x, f.y, color(f.a1, f.a2, \
				(f.y - f.a1.y) / f.dy));
		if (above_mid > 0)
		{
			f.x += step;
			above_mid -= 2 * f.dy;
		}
		above_mid += 2 * f.dx;
		f.y++;
	}
}

void	draw_line(mlx_image_t *img, point_t a1, point_t a2)
{
	double	k;
	draw_t	f;

	f.a1 = a1;
	f.a2 = a2;
	f.dx = a2.x - a1.x;
	f.dy = a2.y - a1.y;
	f.img = img;
	if (f.dx == 0 || f.dy == 0)
	{
		draw_line_hv(f);
		return ;
	}
	k = (a2.y - a1.y) / (a2.x - a1.x);
	if ((k >= -1 && k <= 1 && f.dx < 0) || ((k > 1 || k < -1) && f.dy < 0))
		swap_point(&f);
	if (k >= -1 && k <= 1)
		draw_line_flat(f);
	else
		draw_line_steep(f);
	return ;
}
