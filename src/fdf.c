#include "fdf.h"

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	free_array(int **arr, int i)
{
	while (i-- > 0)
		free(arr[i]);
	free(arr);
}

void	max_min(map_t *map)
{
	int	i;
	int	j;
	int	max;
	int	min;

	max = map->data[0][0];
	min = map->data[0][0];
	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			if (map->data[i][j] > max)
				max = map->data[i][j];
			if (map->data[i][j] < min)
				min = map->data[i][j];
			j++;
		}
		i++;
	}
	map->max = max;
	map->min = min;
}

int	main(int argc, char **argv)
{
	int	fd;
	map_t	map;
	fdf_t	fdf;

	map.data = 0;
	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("File can't be opened.\n");
		return (1);
	}
	parse_map(fd, &map);
	close(fd);
	if (map.data == NULL)
		return (1);
	max_min(&map);

	// TEST
	// printf("h:%i\n", map.height);
	// printf("w:%i\n", map.width);
	// i = 0;
	// while (i < map.height)
	// {
	// 	j = 0;
	// 	while (j < map.width)
	// 	{
	// 		printf("%i", map.data[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }

	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	if (!(fdf.mlx = mlx_init(WIN_W, WIN_H, "Fdf", true)))
	{
		free_array(map.data, map.h);
		printf("%s", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	if (!(fdf.img = mlx_new_image(fdf.mlx, WIN_W, WIN_H)))
	{
		free_array(map.data, map.h);
		printf("%s", mlx_strerror(mlx_errno));
		mlx_close_window(fdf.mlx);
		exit(EXIT_FAILURE);
	}
	fdf.map = map;
	fdf.arr = array_to_coordinates(fdf, ZOOM);
	if (!fdf.arr)
	{
		free_array(map.data, map.h);
		printf("%s", mlx_strerror(mlx_errno));
		mlx_close_window(fdf.mlx);
		exit(EXIT_FAILURE);
	}
	draw_grid(&fdf);
	//mlx_loop_hook(fdf.mlx, draw_grid, &fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, fdf.mlx);

	if (mlx_image_to_window(fdf.mlx, fdf.img, 0, 0) == -1)
	{
		free_array(map.data, map.h);
		free(fdf.arr);
		printf("%s", mlx_strerror(mlx_errno));
		mlx_close_window(fdf.mlx);
		exit(EXIT_FAILURE);
	}
	mlx_loop(fdf.mlx);

	mlx_terminate(fdf.mlx);
	free_array(map.data, map.h);
	free(fdf.arr);
	return (0);
}
