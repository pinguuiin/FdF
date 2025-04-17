/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:10:07 by piyu              #+#    #+#             */
/*   Updated: 2025/04/17 03:10:08 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_max_min(map_t *map)
{
	int	i;
	int	max;
	int	min;

	max = map->data[0];
	min = map->data[0];
	i = 0;
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

void	message_exit(char *s, int sys_error_flag)
{
	if (sys_error_flag == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(EXIT_FAILURE);
}

void	free_exit(fdf_t *fdf, char *s, int sys_error_flag)
{
	if (fdf->map.data)
		free(fdf->map.data);
	if (fdf->coord)
		free(fdf->coord);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	message_exit(s, sys_error_flag);
}
