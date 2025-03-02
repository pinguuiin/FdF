#include "fdf.h"

uint32_t	color(point_t start, point_t end, double w)
{
	uint8_t	*rgba1;
	uint8_t	*rgba2;
	uint8_t	rgba[4];
	uint32_t	color;

	rgba1 = int_to_rgba(start);
	rgba2 = int_to_rgba(end);
	rgba[0] = (uint8_t) (rgba1[0] * (1 - w) + rgba2[0] * w);
	rgba[1] = (uint8_t) (rgba1[1] * (1 - w) + rgba2[1] * w);
	rgba[2] = (uint8_t) (rgba1[2] * (1 - w) + rgba2[2] * w);
	rgba[3] = (uint8_t) (rgba1[3] * (1 - w) + rgba2[3] * w);
	color = (rgba[0] << 24) | (rgba[1] << 16) | (rgba[2] << 8) | rgba[3];
	return (color);
}

static uint8_t	*int_to_rgba(point_t a)
{
	uint8_t	rgba[4];

	rgba[0] = a.color >> 24 & 0xFF;
	rgba[1] = a.color >> 16 & 0xFF;
	rgba[2] = a.color >> 8 & 0xFF;
	rgba[3] = a.color & 0xFF;
	return (rgba);
}
