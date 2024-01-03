#include "cub3d.h"

char map2[] = 
{
	'1', '1', '1', '1', '1', '1', '1', '1',
	'1', '0', '0', '0', '0', '0', '0', '1',
	'1', '0', '0', '0', '0', '1', '0', '1',
	'1', '0', '1', '0', '0', '0', '0', '1',
	'1', '0', '0', '0', '0', '1', '1', '1',
	'1', '0', '0', '0', '0', '0', '0', '1',
	'1', '0', '0', '0', '0', 'N', '0', '1',
	'1', '1', '1', '1', '1', '1', '1', '1',
};
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
	int xo=0;	if (w->s_player.pdx < 0) { xo=-20;}	else { xo=20;}
	int yo=0;	if (w->s_player.pdy < 0) { yo=-20;}	else { yo=20;}
	int	ipx=w->s_player.px/64.0, ipx_add_xo=(w->s_player.px + xo)/64.0, ipx_sub_xo=(w->s_player.px - xo)/64.0;
	int	ipy=w->s_player.py/64.0, ipy_add_yo=(w->s_player.py + yo)/64.0, ipy_sub_yo=(w->s_player.py - yo)/64.0;
	if (key == 119 )
	{
		printf("%d %d \n",ipy*w->s_map.mapX + ipx_add_xo, ipy_add_yo*w->s_map.mapX + ipx);
		if (map2[ipy*w->s_map.mapX + ipx_add_xo]=='0') {w->s_player.px += w->s_player.pdx;}
		if (map2[ipy_add_yo*w->s_map.mapX + ipx]=='0') {w->s_player.py += w->s_player.pdy;}
	}
	else if (key == 100 )
	{
		w->s_player.px += cos(w->s_player.pa + M_PI_2) * 5;
		w->s_player.py += sin(w->s_player.pa + M_PI_2) * 5;
	}
	else if (key == 115 )
	{
		if (map2[ipy*w->s_map.mapX + ipx_sub_xo]=='0') {w->s_player.px -= w->s_player.pdx;}
		if (map2[ipy_sub_yo*w->s_map.mapX + ipx]=='0') {w->s_player.py -= w->s_player.pdy;}
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
		w->s_player.pa -= 3*DR;
		if (w->s_player.pa < 0)
			w->s_player.pa += 2 * PI;
		w->s_player.pdx = cos(w->s_player.pa) * 5;
		w->s_player.pdy = sin(w->s_player.pa) * 5;
	}
	else if (key == 65363)
	{
		w->s_player.pa += 3*DR;
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
	else if (key == 102)
		;
	else
		return (key);
	return (key);
}
