#include "fdf.h"

void	draw_line(mlx_image_t *img, point_t a1, point_t a2)
{
	int	dx;
	int	dy;
	double	k;
	draw_t	draw;

	draw.a1 = a1;
	draw.a2 = a2;
	draw.dx = a2.x - a1.x;
	draw.dy = a2.y - a1.y;
	draw.img = img;
	if (dx == 0 || dy == 0)
	{
		draw_line_hv(draw);
		return ;
	}
	k = (double) (a2.y - a1.y) / (a2.x - a1.x);
	if ((k >= -1 && k <= 1 && dx < 0) || ((k > 1 || k < -1) && dy < 0))
		swap_point(&draw);
	if (k >= -1 && k <= 1)
		draw_line_flat(draw);
	else
		draw_line_steep(draw);
	return ;
}

void	swap_point(draw_t *draw)
{
	point_t	temp;

	temp = draw->a1;
	draw->a1 = draw->a2;
	draw->a2 = temp;
	draw->dx *= -1;
	draw->dy *= -1;
}

// void	draw_pixel(mlx_image_t *img, int x, int y, int color)
// {
// 	uint8_t	*offset;

// 	offset = img->pixels + img->width * y + x * 4;
// 	*offset = color;
// }

/** Draws a line horizontally
 * @param img The mlx image
 * @param a1 The a1ing point
 * @param a2 The a2ing point
 * @param dx Something needed
 * @param dy The other something
 */
void	draw_line_hv(draw_t draw)
{
	int	x;
	int	y;

	if ((draw.dx == 0 && draw.dy < 0) || (draw.dy == 0 && draw.dx < 0))
		swap_point(&draw);
	x = draw.a1.x;
	y = draw.a1.y;
	if (draw.dx == 0)
	{
		while (y <= draw.a2.y)
		{
			mlx_put_pixel(draw.img, x, y, color(draw.a1, draw.a2, y/draw.dy));
			y++;
		}
	}
	else
	{
		while (x <= draw.a1.x)
		{
			mlx_put_pixel(draw.img, x, y, color(draw.a1, draw.a2, x/draw.dx));
			x++;
		}
	}
}

void	draw_line_flat(draw_t draw)
{
	int	x;
	int	y;
	int	step;
	int	D;

	step = 1;
	if (draw.dy < 0)
		step = -1;
	draw.dy *= step;
	D = 2 * draw.dy - draw.dx;
	x = draw.a1.x;
	y = draw.a1.y;
	while (x < draw.a2.x)
	{
		mlx_put_pixel(draw.img, x, y, color(draw.a1, draw.a2, x/draw.dx));
		if (D > 0)
		{
			y += step;
			D += 2 * draw.dy - 2 * draw.dx;
		}
		else
			D += 2 * draw.dy;
		x++;
	}
}

void	draw_line_steep(draw_t draw)
{
	int	x;
	int	y;
	int	step;
	int	D;

	step = 1;
	if (draw.dx < 0)
		step = -1;
	draw.dx *= step;
	D = 2 * draw.dx - draw.dy;
	x = draw.a1.x;
	y = draw.a1.y;
	while (y < draw.a2.y)
	{
		mlx_put_pixel(draw.img, x, y, color(draw.a1, draw.a2, y/draw.dy));
		if (D > 0)
		{
			x += step;
			D += 2 * draw.dx - 2 * draw.dy;
		}
		else
			D += 2 * draw.dx;
		y++;
	}
}
