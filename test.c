#include <stdio.h>
#include <stdlib.h>
#include "include/mlx.h"

struct s_
{
	void *mlx;
	void *win;
}s_;

void	sett(int key)
{
	printf("_sett_ %d\n", key);
	if (key == 65307)
		exit(0);
}

void test(int key)
{
	printf("_test_ %d\n", key);
	;
}

void next_frame()
{

	int x;
	int y;
	//mlx_mouse_hide(s_.mlx, s_.win);
	mlx_mouse_get_pos(s_.mlx, s_.win, &x, &y);
	mlx_mouse_move(s_.mlx, s_.win, 200, 100);
	if (y != 100)
		printf("%d %d\n", x, y);
}

int	main(void)
{
	s_.mlx = mlx_init();
	s_.win = mlx_new_window(s_.mlx, 400, 200, "WF99");

	mlx_hook(s_.win,  2, 1L<<0, (void *)sett, NULL);
	mlx_key_hook(s_.win, (void *)test, NULL);
	mlx_loop_hook(s_.mlx, (void*)next_frame, NULL);
	mlx_loop(s_.mlx);
	return (0);
}