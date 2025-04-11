#include "fdf.h"

static int	count_length(char *arr)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arr[i] == ' ')
		i++;
	while (arr[i])
	{
		if (arr[i] == ' ')
		{
			len++;
			while(arr[i] == ' ' || arr[i] == '\n')
				i++;
		}
		if (arr[i] != '\0')
		{
			if (arr[i + 1] == '\0')
				len++;
			i++;
		}
	}
	return (len);
}

static void	format_array(char *s, int ***data_p, int *wp, int *hp)
{
	int	i;
	int	j;

	i = 0;
	*data_p = malloc(*hp * sizeof(int *));
	if (*data_p == NULL)
		return ;
	while (i < *hp)
	{
		(*data_p)[i] = malloc(*wp * sizeof(int));
		if ((*data_p)[i] == NULL)
		{
			while (i-- > 0)
				free((*data_p)[i]);
			free(*data_p);
			return ;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (ft_isdigit(*s) || *s == '-')
		{
			(*data_p)[i][j] = ft_atoi(s);
			j++;
			while (*s && *s != ' ' && *s != '\n')
				s++;
			while (*s == ' ' && j == *wp)
				s++;
			if (*s == '\n')
			{
				j = 0;
				i++;
				s++;
			}
		}
	}
}

void	parse_map(int fd, map_t *map)
{
	char	*line;
	char	*data_unform;
	char	*temp;

	map->w = 0;
	map->h = 0;
	data_unform = ft_strdup("");
	while(1)
	{
		if (data_unform == NULL)
			return ;
		line = get_next_line(fd);
		if (line == NULL)
			break;
		if (data_unform[0] == '\0')
			map->w = count_length(line);
		temp = ft_strjoin(data_unform, line);
		free(data_unform);
		free(line);
		data_unform = temp;
		(map->h)++;
	}
	//if *wp == -1
	format_array(data_unform, &(map->data), &(map->w), &(map->h));
	free(data_unform);
}
