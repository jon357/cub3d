#include <stdio.h>
#include <stdlib.h>
#include "include/mlx.h"

int	close(int key)
{
	printf("_close_ %d\n", key);
	return (0);
}

void test(int key)
{
	printf("_test_ %d\n", key);
	;
}

int	main(void)
{
	void *mlx;
	void *win;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 200, "WF99");

	mlx_hook(win,  2, 1L<<0, close, NULL);
	mlx_key_hook(win, (void *)test, NULL);
	mlx_loop(mlx);
	return (0);
}