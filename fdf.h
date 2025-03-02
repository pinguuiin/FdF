#ifndef FDF_H
# define FDF_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h> ///
#include <stdlib.h>
#include "MLX42/include/MLX42/MLX42.h"

int	main(int argc, char **argv);
void	parse_map(int fd, map_t *map);
int	ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);

char	*get_next_line(int fd);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_isdigit(int c);

point_t	*array_to_coordinates(map_t map);

typedef struct map_s
{
	int	w;
	int	h;
	int	**data;
}	map_t;

typedef struct point_s
{
	int	x;
	int	y;
	int	z;
	uint32_t	color;
}	point_t;

typedef struct fdf_s
{
	mlx_t	*mlx;
	mlx_image_t	*img;
	map_t	map;
}	fdf_t;

typedef struct draw_s
{
	mlx_image_t	*img;
	point_t	a1;
	point_t	a2;
	int	dx;
	int	dy;
}	draw_t

#endif
