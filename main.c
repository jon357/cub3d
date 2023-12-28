#include "cub3d.h"

int map[] = 
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 9, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

int	*kill_prog(t_structure_main *w)
{
	mlx_destroy_window(w->s_win.mlx, w->s_win.win);
	mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	mlx_destroy_image(w->s_win.mlx, w->s_img.img_player);
	mlx_destroy_image(w->s_win.mlx, w->s_img.img_wall);
	mlx_destroy_display(w->s_win.mlx);
	free(w->s_win.mlx);
	int i = -1;
	//while (w->s_map.map[++i])
	//	free(w->s_map.map[i]);
	//free(w->s_map.map);
	exit (0);
	return (0);
}

void	put_pixel_img(t_structure_main *w,int x, int y, int color)
{
	//w->s_img.addr = mlx_get_data_addr(w->s_img.img, &(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	char	*dst;

	if (x >= 0 && y >= 0 && x < w->s_win.height && y < w->s_win.width)
	{
		dst = w->s_img.addr + (y * w->s_img.line_len + x * (w->s_img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void	draw_squar_raw(t_structure_main *w,int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_img(w, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_squar(t_structure_main *w,int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_img(w, (x*50) + j, (y*50) + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_structure_main *w)
{

	int	x;
	int y;

	//mlx_clear_window(w->s_win.mlx, w->s_win.win);
	//mlx_put_image_to_window(w->s_win.mlx, w->s_img.buffer, w->s_img.img_player,w->s_player.px, w->s_player.py);
	y = 0;
	while ( y < 8)
	{
		x = 0;
		while ( x < 8)
		{
			if (map[y*8+x] == 1)
				draw_squar(w, x, y, 50, 0x888888);
			x++;
		}
		y++;
	}
	draw_squar_raw(w, w->s_player.px-5, w->s_player.py-5, 10, 0xffff00);
	float j;
	j = -0.5;
	while (j < 0.5)
	{
		float end_x = w->s_player.px + 40 * cos(w->s_player.rp + j);
		float end_y = w->s_player.py + 40 * sin(w->s_player.rp + j);
		for (float i = 0; i <= 20.0; i += 0.01) {
			float current_x = w->s_player.px + i * (end_x - w->s_player.px);
			float current_y = w->s_player.py + i * (end_y - w->s_player.py);
			put_pixel_img(w, current_x, current_y, 0x00ff00);
		}
		j = j + 0.01;
	}
	mlx_put_image_to_window(w->s_win.mlx,w->s_win.win, w->s_img.buffer,0, 0);
}

void test(t_structure_main *w)
{
	int	x;
	int y;

    //////////gettimeofday(&(w->start_time), NULL);
	mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.height, w->s_win.width);
	w->s_img.addr = mlx_get_data_addr(w->s_img.buffer, &(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	draw_map(w);

/*
    // Mesurer le temps à la fin de la frame
    gettimeofday(&(w->end_time), NULL);
    // Calculer le temps écoulé
    double elapsed_time = (w->end_time.tv_sec - w->start_time.tv_sec) + (w->end_time.tv_usec - w->start_time.tv_usec) / 1.0e6;
    // Calculer les FPS
    double fps = 1.0 / elapsed_time;
    // Afficher le compteur de FPS
    printf("FPS: %.2f\n", fps);
    // Incrémenter le nombre total de frames
    w->frame_count++;
*/
	//mlx_mouse_move(w->s_win.mlx, w->s_win.win, w->s_win.height / 2, w->s_win.width / 2);
	//mlx_mouse_get_pos(w->s_win.mlx, w->s_win.win, &x, &y);
	//mlx_pixel_put(w->s_win.mlx, w->s_win.win, w->s_player.px, w->s_player.py, 0x00ff00);
	/*
	if (x != w->s_win.height / 2 && y != w->s_win.width / 2)
		printf("%d %d \n", x - w->s_win.height / 2, y - w->s_win.width / 2);
	mlx_mouse_get_pos(w->s_win.mlx, w->s_win.win, &x, &y);
	if ((x < w->s_win.height && y < w->s_win.width) && (x > 0 && y > 0))
		printf("%d %d \n", x, y);
	else
		printf("\n");
	*/

}

void	move(int key, t_structure_main *w)
{
	if (key == 119 )
	{
		w->s_player.px += w->s_player.pdx;
		w->s_player.py += w->s_player.pdy;
	}
	else if (key == 100 )
	{
        w->s_player.px += cos(w->s_player.rp + M_PI_2) * 5;
        w->s_player.py += sin(w->s_player.rp + M_PI_2) * 5;
	}
	else if (key == 115 )
	{
		w->s_player.px -= w->s_player.pdx;
		w->s_player.py -= w->s_player.pdy;
	}
	else if (key == 97)
	{
        w->s_player.px += cos(w->s_player.rp - M_PI_2) * 5;
        w->s_player.py += sin(w->s_player.rp - M_PI_2) * 5;
	}
}

int	deal_key(int key, t_structure_main *w)
{
	printf("key pressed = %d\n", key);
	if (key == 65307)
		kill_prog(w);
	else if (key == 65361)
	{
		w->s_player.rp -= 0.1;
		w->s_player.pdx = cos(w->s_player.rp) * 5;
		w->s_player.pdy = sin(w->s_player.rp) * 5;
	}
	else if (key == 65363)
	{
		w->s_player.rp += 0.1;
		w->s_player.pdx = cos(w->s_player.rp) * 5;
		w->s_player.pdy = sin(w->s_player.rp) * 5;
	}
	else if (key == 65362)
		;
	else if (key == 65364)
		;
	else if (key == 119 || key == 100 || key == 115 || key == 97) // w, d, s, a
		move(key,w);
	else if (key == 114)
		;
	else if (key == 102)
		;
	else
		return (key);
	return (key);
}

void	init_windows(t_structure_main *w)
{
	int temp;
	w->s_win.height = 500;
	w->s_win.width = 400;
	w->s_win.mlx = mlx_init();
	w->s_win.win = mlx_new_window(w->s_win.mlx, w->s_win.height, w->s_win.width, "WF99");
	w->s_player.px = 200;
	w->s_player.py = 200;
	w->s_player.pdx = cos(w->s_player.rp) * 5;
	w->s_player.pdy = sin(w->s_player.rp) * 5;

	w->s_player.rp = 0;
	w->s_img.img_player = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/player.xpm", &temp,&temp);
	w->s_img.img_wall = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/wall.xpm", &temp,&temp);
	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.height, w->s_win.width);
    // Initialiser le compteur de FPS
    gettimeofday(&(w->start_time), NULL);
    w->end_time = w->start_time;
    w->frame_count = 0;
}

int	main(int argc, char **argv)
{
	t_structure_main	w;
	//int	x;
	//int	y;

	(void)argc;
	(void)argv;
	init_windows(&w);
	//w.s_win.fd = open("test_map", O_RDONLY);
	//get_size(&w);
	//printf("x %d, y %d \n", w.s_win.s_map.height,w.s_win.s_map.width);
	//close(w.s_win.fd);
	//w.s_win.fd = open("test_map", O_RDONLY);
	//split_map(&w);
	//close(w.s_win.fd);
	//print_map(&w);
	//mlx_mouse_move(w.s_win.mlx, w.s_win.win, 0, 0);
	//mlx_mouse_hide(w.s_win.mlx, w.s_win.win);
	//mlx_mouse_get_pos(w.s_win.mlx, w.s_win.win, &x, &y);
	mlx_loop_hook(w.s_win.mlx, (void *)test, &w);
	mlx_key_hook(w.s_win.win, deal_key, &w);
	mlx_hook(w.s_win.win,  17, 0, (void *)kill_prog, &w);
	mlx_loop(w.s_win.mlx);
	return (0);
}