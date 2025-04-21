/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:09:03 by piyu              #+#    #+#             */
/*   Updated: 2025/04/21 02:58:59 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint8_t	normalize(double value, double max, double min)
{
	uint8_t	normed_value;

	normed_value = (uint8_t)(((value - min) / (max - min)) * 255);
	return (normed_value);
}

uint32_t	color_data(int i, t_map map, double elev_factor)
{
	uint8_t	normed_value;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	if (map.max == map.min)
		return (0xFFFFFFFF);
	normed_value = normalize(map.data[i] * elev_factor, map.max, map.min);
	r = 70 + normed_value * 0.8;
	g = 30 + normed_value * 0.8;
	b = 205 - normed_value * 0.8;
	return (r << 24 | g << 16 | b << 8 | 255);
}
