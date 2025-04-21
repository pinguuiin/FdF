/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:41:36 by piyu              #+#    #+#             */
/*   Updated: 2025/04/21 21:07:28 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*next_line_check(char *line, char *buf)
{
	char	*temp;

	if (!line)
		temp = ft_substr(buf, 0, ft_strlen(buf));
	else
	{
		temp = ft_strjoin(line, buf);
		free(line);
	}
	if (temp == NULL)
		return (NULL);
	if (ft_strchr(temp, '\n'))
	{
		line = ft_substr(temp, 0, ft_strchr(temp, '\n') - temp + 1);
		ft_memmove(buf, ft_strchr(buf, '\n') + 1, \
		ft_strlen(ft_strchr(buf, '\n') + 1) + 1);
	}
	else
	{
		line = ft_substr(temp, 0, ft_strlen(temp));
		ft_memmove(buf, buf + ft_strlen(buf), \
		BUFFER_SIZE - ft_strlen(buf) + 1);
	}
	free(temp);
	return (line);
}

static char	*read_and_check(int fd, char *buf, char *line)
{
	ssize_t	byteread;

	while (1)
	{
		byteread = read(fd, buf, BUFFER_SIZE);
		if (byteread == 0)
			return (line);
		if (byteread == -1)
		{
			if (line)
				free(line);
			return (NULL);
		}
		buf[byteread] = '\0';
		line = next_line_check(line, buf);
		if (!line || ft_strchr(line, '\n'))
			return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (buf[0])
	{
		line = next_line_check(line, buf);
		if (!line || ft_strchr(line, '\n'))
			return (line);
	}
	line = read_and_check(fd, buf, line);
	return (line);
}
