/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:10:07 by piyu              #+#    #+#             */
/*   Updated: 2025/04/21 02:55:19 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_max_min(t_map *map)
{
	int		i;
	double	max;
	double	min;

	i = 0;
	max = map->data[0];
	min = map->data[0];
	while (i < map->h * map->w)
	{
		if (map->data[i] > max)
			max = map->data[i];
		if (map->data[i] < min)
			min = map->data[i];
		i++;
	}
	map->max = max;
	map->min = min;
}

void	get_center_offset(t_fdf *fdf)
{
	int		i;
	double	x[2];
	double	y[2];

	i = 0;
	x[0] = fdf->coord[0].x;
	x[1] = fdf->coord[0].x;
	y[0] = fdf->coord[0].y;
	y[1] = fdf->coord[0].y;
	while (i < fdf->map.h * fdf->map.w)
	{
		if (fdf->coord[i].x > x[1])
			x[1] = fdf->coord[i].x;
		if (fdf->coord[i].x < x[0])
			x[0] = fdf->coord[i].x;
		if (fdf->coord[i].y > y[1])
			y[1] = fdf->coord[i].y;
		if (fdf->coord[i].y < y[0])
			y[0] = fdf->coord[i].y;
		i++;
	}
	fdf->offset[0] = WIN_W / 2.0 - (x[1] + x[0]) / 2.0;
	fdf->offset[1] = WIN_H / 2.0 - (y[1] + y[0]) / 2.0;
}

void	message_exit(char *s, int sys_error_flag)
{
	if (sys_error_flag == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(EXIT_FAILURE);
}

void	free_exit(t_fdf *fdf, char *s, int sys_error_flag)
{
	if (fdf->map.data)
		free(fdf->map.data);
	if (fdf->coord)
		free(fdf->coord);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	message_exit(s, sys_error_flag);
}
