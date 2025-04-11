#include "fdf.h"

void	draw_grid(void *param)
{
	const fdf_t *fdf = (fdf_t*)param;
	int	i;
	int	w;
	int h;
	char *str = "Topographic Map in 3D Wireframe Model (made by C)";

	i = 0;
	w = fdf->map.w;
	h = fdf->map.h;
	while (i < h * w)
	{
		if (i % w != w - 1)
			draw_line(fdf->img, fdf->arr[i], fdf->arr[i + 1]);
		if (i < (h - 1) * w)
			draw_line(fdf->img, fdf->arr[i], fdf->arr[i + w]);
		i++;
	}
	mlx_put_string(fdf->mlx, str, fdf->arr[0].x - 170, fdf->arr[i].y + 800);
}
