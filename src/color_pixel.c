/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:08:52 by piyu              #+#    #+#             */
/*   Updated: 2025/04/17 03:08:54 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	int_to_rgb(point_t a, uint8_t *rgb)
{
	rgb[0] = a.color >> 24 & 0xFF;
	rgb[1] = a.color >> 16 & 0xFF;
	rgb[2] = a.color >> 8 & 0xFF;
}

uint32_t	color(point_t start, point_t end, double w)
{
	uint8_t		rgb_start[3];
	uint8_t		rgb_end[3];
	uint8_t		rgb[3];
	uint32_t	color;

	int_to_rgb(start, rgb_start);
	int_to_rgb(end, rgb_end);
	rgb[0] = (uint8_t)(rgb_start[0] * (1 - w) + rgb_end[0] * w);
	rgb[1] = (uint8_t)(rgb_start[1] * (1 - w) + rgb_end[1] * w);
	rgb[2] = (uint8_t)(rgb_start[2] * (1 - w) + rgb_end[2] * w);
	color = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255;
	//printf("Color value: 0x%08x\n", color);
	return (color);
}
