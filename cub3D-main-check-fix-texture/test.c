#include <stdio.h>
#include <stdlib.h>
#include "include/mlx.h"

struct s_
{
	void *mlx;
	void *win;
	void *wall;
}s_;

void	key(int key)
{
	printf("_key_ %d\n", key);
	if (key == 65307)
		exit(0);
}


void next_frame()
{

}

int	main(void)
{
	int test;
	int width;
	int height;
	int bits_per_pixel;
	int size_line;
	int endian;

	s_.mlx = mlx_init();
	s_.win = mlx_new_window(s_.mlx, 400, 200, "Test");
	s_.wall = mlx_xpm_file_to_image(s_.mlx, "sprite/pedrop/frame_061_delay-0.03s.xpm", &width, &height);
	if (!s_.wall)
		printf("deded\n");


	char *mlx_data_addr = mlx_get_data_addr(s_.wall, &bits_per_pixel, &size_line, &endian);
	int pos = (10 * size_line + 10 * (bits_per_pixel / 8));
	char *dst = mlx_data_addr + pos;

	printf("-------%s-------\n",dst);

	int i = -1;
	while (++i < 4)
	{
		printf("%d hex__%x\n", i, dst[i]);
//		printf("%d int__%d\n", i, dst[i]);
	}

	int color = 0x10ff99;
	*(unsigned int *)dst = color;
	printf("----%s----\n",dst);

	i = -1;
	while (++i < 4)
	{
		printf("%d hex__%x\n", i, dst[i]);
//		printf("%d int__%d\n", i, dst[i]);
	}

	mlx_put_image_to_window(s_.mlx, s_.win, s_.wall, 0,0);

	mlx_hook(s_.win,  2, 1L<<0, (void *)key, NULL);
	mlx_loop_hook(s_.mlx, (void*)next_frame, NULL);
	mlx_loop(s_.mlx);
	return (0);
}