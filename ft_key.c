#include "cub3d.h"

int	*kill_prog(t_structure_main *w)
{
	mlx_destroy_window(w->s_win.mlx, w->s_win.win);
	mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	mlx_destroy_image(w->s_win.mlx, w->s_img.img_player);
	mlx_destroy_image(w->s_win.mlx, w->s_img.img_wall);
	int i = -1;
	while (++i <= 10)
		mlx_destroy_image(w->s_win.mlx, w->s_img.roomadslam[i]);
	
	//while (w->s_map.map[++i])
	//	free(w->s_map.map[i]);
	//free(w->s_map.map);
	mlx_destroy_display(w->s_win.mlx);
	free(w->s_win.mlx);
	exit (0);
	return (0);
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
        w->s_player.px += cos(w->s_player.pa + M_PI_2) * 5;
        w->s_player.py += sin(w->s_player.pa + M_PI_2) * 5;
	}
	else if (key == 115 )
	{
		w->s_player.px -= w->s_player.pdx;
		w->s_player.py -= w->s_player.pdy;
	}
	else if (key == 97)
	{
        w->s_player.px += cos(w->s_player.pa - M_PI_2) * 5;
        w->s_player.py += sin(w->s_player.pa - M_PI_2) * 5;
	}
}

int	deal_key(int key, t_structure_main *w)
{
	//printf("key pressed = %d\n", key);
	if (key == 65307)
		kill_prog(w);
	else if (key == 65361)
	{
		w->s_player.pa -= 0.1;
		w->s_player.pdx = cos(w->s_player.pa) * 5;
		w->s_player.pdy = sin(w->s_player.pa) * 5;
	}
	else if (key == 65363)
	{
		w->s_player.pa += 0.1;
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
	else if (key == 102)
		;
	else
		return (key);
	return (key);
}
