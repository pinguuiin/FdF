#include "fdf.h"

point_t	*array_to_coordinates(map_t map)
{
	int	i;
	int	j;
	point_t	*coords;

	coords = malloc(map.w * map.h * sizeof(point_t));
	i = 0;
	while (i < map.h)
	{
		j = 0;
		while (j < map.w)
		{
			coords[map.w * i + j].x = j;
			coords[map.w * i + j].y = i;
			coords[map.w * i + j].z = map.data[i][j];
			coords[map.w * i + j].color = color_data(j, i, map);
			j++;
		}
		i++;
	}
}

uint32_t color_data(int x, int y, map_t map)
{
	int	*limit;
	uint8_t	normed_value;
	uint8_t	r;
	uint8_t	g;
	uint8_t b;

	limit = max_min(map);
	if (limit[0] == limit[1])
		return (0xFFFFFF);
	normed_value = normalize(map.data[y][x], limit[0], limit[1]);
	r = normed_value;
	g = 255 - normed_value;
	b = 255 - normed_value;
	return (255 << 24 | r << 16 | g << 8 | b);
}

static int	*max_min(map_t map)
{
	int	i;
	int	j;
	int	max;
	int	min;
	int	limit[2];

	max = map.data[0][0];
	min = map.data[0][0];
	i = 0;
	while (i < map.h)
	{
		j = 0;
		while (j < map.w)
		{
			if (map.data[i][j] > max)
				max = map.data[i][j];
			if (map.data[i][j] < min)
				min = map.data[i][j];
			j++;
		}
		i++;
	}
	limit[0] = max;
	limit[1] = min;
	return (limit);
}

uint8_t	normalize(int value, int max, int min)
{
	uint8_t	normed_value;

	normed_value = (uint8_t) (((double) (value - min) / (max - min)) * 255);
	return (normed_value);
}
