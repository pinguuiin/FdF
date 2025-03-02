#include "fdf.h"

void	free_array(int **arr, int i)
{
	while (i-- > 0)
		free(arr[i]);
	free(arr);
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	fd;
	map_t	map;
	mlx_t	*mlx;
	mlx_image_t	*img;
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
	if (!(mlx = mlx_init(256, 256, "Fdf", true)))
	{
		free_array(map.data, map.h);
		printf("%s", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	if (!img = mlx_new_image(mlx, 128, 128))
	{
		free_array(map.data, map.h);
		mlx_close_window(mlx);
		printf("%s", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}

	mlx_loop_hook(mlx, draw_map, mlx);





	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	{
		free_array(map.data, map.h);
		mlx_close_window(mlx);
		printf("%s", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}

	return (0);
}
