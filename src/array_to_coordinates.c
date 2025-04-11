#include "fdf.h"

static uint8_t	normalize(int value, int max, int min)
{
	uint8_t	normed_value;

	normed_value = (uint8_t) (((double) (value - min) / (max - min)) * 255);
	return (normed_value);
}

static uint32_t color_data(int x, int y, map_t map)
{
	uint8_t	normed_value;
	uint8_t	r;
	uint8_t	g;
	uint8_t b;

	if (map.max == map.min)
		return (0xFFFFFFFF);
	normed_value = normalize(map.data[y][x], map.max, map.min);
	r = 70 + normed_value * 0.8;
	g = 30 + normed_value * 0.8;
	b = 205 - normed_value * 0.8;
	return (r << 24 | g << 16 | b << 8 | 255);
}

point_t	*array_to_coordinates(fdf_t fdf, int zoom)
{
	int		i;
	int		j;
	point_t	*coords;

	coords = malloc(fdf.map.w * fdf.map.h * sizeof(point_t));
	if (!coords)
		return (NULL);
	i = 0;
	while (i < fdf.map.h)
	{
		j = 0;
		while (j < fdf.map.w)
		{
			coords[fdf.map.w * i + j].x = (j - i) * cos(0.523599) * zoom + \
			(WIN_W - fdf.map.w * zoom) / 2 + 200;
			coords[fdf.map.w * i + j].y = ((i + j) * sin(0.523599) - fdf.map.data[i][j]) * zoom \
			+ (WIN_H - fdf.map.h * zoom) / 2;
			coords[fdf.map.w * i + j].color = color_data(j, i, fdf.map);

			printf("x:%i\t", coords[fdf.map.w * i + j].x);
			printf("y:%i\n", coords[fdf.map.w * i + j].y);
			j++;
		}
		i++;
	}
	return(coords);
}
