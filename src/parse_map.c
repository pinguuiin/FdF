/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:09:57 by piyu              #+#    #+#             */
/*   Updated: 2025/04/18 04:24:28 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_width(char *arr)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arr[i] && arr[i] != '\n')
	{
		while (arr[i] == ' ')
			i++;
		if (arr[i] && arr[i] != ' ' && arr[i] != '\n')
		{
			len++;
			while (arr[i] && arr[i] != ' ' && arr[i] != '\n')
				i++;
		}
	}
	return (len);
}

static void	assign_value(char *s, map_t *map)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (ft_isdigit(*s) || *s == '-')
		{
			map->data[i++] = (double)ft_atoi(s);
			while (*s && *s != ' ' && *s != '\n')
				s++;
		}
		if (*s == '\n')
			s++;
	}
}

static void	format_array(char *s, map_t *map)
{
	if (map->h == 0 || map->w == 0)
	{
		free(s);
		message_exit("Empty map", 0);
	}
	map->data = ft_calloc(map->h * map->w, sizeof(double));
	if (map->data == NULL)
	{
		free(s);
		message_exit("Error allocating memory", 0);
	}
	assign_value(s, map);
	free(s);
}

void	parse_map(int fd, map_t *map)
{
	char	*line;
	char	*buffer;
	char	*temp;

	map->w = 0;
	map->h = 0;
	buffer = ft_strdup("");
	while (1)
	{
		if (buffer == NULL)
			message_exit("Error allocating memory", 0);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (buffer[0] == '\0')
			map->w = count_width(line);
		temp = ft_strjoin(buffer, line);
		free(buffer);
		free(line);
		buffer = temp;
		(map->h)++;
	}
	close(fd);
	format_array(buffer, map);
	get_max_min(map);
}
