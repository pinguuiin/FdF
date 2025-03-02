#include "fdf.h"
void	draw_grid(point_t *arr, fdf_t fdf)
{
	int	i;
	int	j;
	int	w;
	int h;

	i = 0;
	w = fdf.map.w;
	h = fdf.map.h;
	while (i < h * w)
	{
		if (i % w != w - 1)
			draw_line(fdf.img, arr[i], arr[i + 1]);
		if (i < (h - 1) * w)
			draw_line(fdf.img, arr[i], arr[i + w]);
		i++;
	}
}
