#include "cub3d.h"

int *kill_prog(t_structure_main *w) {
	mlx_destroy_window(w->s_win.mlx, w->s_win.win);
	mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	mlx_destroy_image(w->s_win.mlx, w->s_img.img_player);
	mlx_destroy_image(w->s_win.mlx, w->s_img.img_wall);
	mlx_destroy_image(w->s_win.mlx, w->s_img.pedro_wall);

	mlx_destroy_image(w->s_win.mlx, w->s_img.north_texture);
	mlx_destroy_image(w->s_win.mlx, w->s_img.south_texture);
	mlx_destroy_image(w->s_win.mlx, w->s_img.west_texture);
	mlx_destroy_image(w->s_win.mlx, w->s_img.east_texture);

	// Libérer les images de roomadslam
	int i = -1;
	while (++i <= 10)
		mlx_destroy_image(w->s_win.mlx, w->s_img.roomadslam[i]);

	// Libérer la carte si elle a été allouée
	if (w->s_map.map) {
	 //   printf("rujnienverv\n");
		free(w->s_map.map);
		w->s_map.map = NULL; // Sécurité supplémentaire après la libération
	}

	mlx_destroy_display(w->s_win.mlx);
	//free(w->s_map.map);
	free(w->s_win.mlx);
	exit(0);
	return (0);
}

void move(int key, t_structure_main *w)
{
	if (key == 119 )
	{
		if (w->s_map.map[(int)((w->s_player.py)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + (cos(w->s_player.pa) * w->s_map.mapS))/w->s_map.mapS)]=='0')
			w->s_player.px += cos(w->s_player.pa) * w->s_map.mapS;
		if (w->s_map.map[(int)((w->s_player.py + (sin(w->s_player.pa) * w->s_map.mapS))/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px)/w->s_map.mapS)]=='0')
			w->s_player.py += sin(w->s_player.pa) * w->s_map.mapS;
	}
	else if (key == 100 )
	{	   
		if (w->s_map.map[(int)((w->s_player.py)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + (cos(w->s_player.pa + (PI/2)) * w->s_map.mapS))/w->s_map.mapS)]=='0')
			w->s_player.px += cos(w->s_player.pa + (PI/2)) * w->s_map.mapS;
		if (w->s_map.map[(int)((w->s_player.py + (sin(w->s_player.pa + (PI/2)) * w->s_map.mapS))/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px)/w->s_map.mapS)]=='0')
			w->s_player.py += sin(w->s_player.pa + (PI/2)) * w->s_map.mapS;
	}
	else if (key == 115 )
	{
		if (w->s_map.map[(int)((w->s_player.py)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + (cos(w->s_player.pa + (PI)) * w->s_map.mapS))/w->s_map.mapS)]=='0')
			w->s_player.px += cos(w->s_player.pa + (PI)) * w->s_map.mapS;
		if (w->s_map.map[(int)((w->s_player.py + (sin(w->s_player.pa + (PI)) * w->s_map.mapS))/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px)/w->s_map.mapS)]=='0')
			w->s_player.py += sin(w->s_player.pa + (PI)) * w->s_map.mapS;
	}
	else if (key == 97)
	{
		if (w->s_map.map[(int)((w->s_player.py)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + (cos(w->s_player.pa + (3*(PI/2))) * w->s_map.mapS))/w->s_map.mapS)]=='0')
			w->s_player.px += cos(w->s_player.pa + (3*(PI/2))) * w->s_map.mapS;
		if (w->s_map.map[(int)((w->s_player.py + (sin(w->s_player.pa + (3*(PI/2))) * w->s_map.mapS))/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px)/w->s_map.mapS)]=='0')
			w->s_player.py += sin(w->s_player.pa + (3*(PI/2))) * w->s_map.mapS;
	}
}



int	deal_key(int key, t_structure_main *w)
{
	//printf("key pressed = %d\n", key);
	if (key == 65307)
		kill_prog(w);
	else if (key == 65361)
	{
		w->s_player.pa -= 4*((PI/180));
		if (w->s_player.pa < 0)
			w->s_player.pa += 2 * PI;
		w->s_player.pdx = cos(w->s_player.pa) * 5;
		w->s_player.pdy = sin(w->s_player.pa) * 5;
	}
	else if (key == 65363)
	{
		w->s_player.pa += 4*((PI/180));
		if (w->s_player.pa > 2 * PI)
			w->s_player.pa -= 2 * PI;
		w->s_player.pdx = cos(w->s_player.pa) * 5;
		w->s_player.pdy = sin(w->s_player.pa) * 5;
	}
	else if (key == 65362)
		;
	else if (key == 65364)
		;
	else if (key == 119 || key == 100 || key == 115 || key == 97) // w, d, s, a
		move(key,w);
	else if (key == 114)
		;
	else if (key == 120) //x debug
	{
		int i;
		int j=0;
		printf("%d %d\n",w->s_map.mapX,w->s_map.mapY);
		while (j<w->s_map.mapY)
		{
			printf("%.*s\n",w->s_map.mapX,w->s_map.map + j*w->s_map.mapX);
			j++;
		}
	}
	else if (key == 101) //e door
	{
		if (w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + cos(w->s_player.pa) * 7)/w->s_map.mapS)] == '1')
			w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + cos(w->s_player.pa) * 7)/w->s_map.mapS)] = '2';
		else if (w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + cos(w->s_player.pa) * 7)/w->s_map.mapS)] == '2')
			w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)/w->s_map.mapS) * w->s_map.mapX + (int)((w->s_player.px + cos(w->s_player.pa) * 7)/w->s_map.mapS)] = '1';
	}
	else if (key == 102)
		;
	else
		return (key);
	return (key);
}
