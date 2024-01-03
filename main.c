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

void draw_square_raw(t_structure_main *w, int x, int y, int xo, int yo, int color)
{
	int i;
	int j;
		
	int size_x = abs(xo - x);
	int size_y = abs(yo - y);

	for (i = 0; i < size_y; i++)
	{
		for (j = 0; j < size_x; j++)
		{
			put_pixel_img(w, (x) + j, (y) + i, color);
		}
	}
}

void draw_square(t_structure_main *w, int x, int y, int xo, int yo, int color)
{
	int i;
	int j;
		
	int size_x = abs(xo - x);
	int size_y = abs(yo - y);

	for (i = 0; i < size_y; i++)
	{
		for (j = 0; j < size_x; j++)
		{
			put_pixel_img(w, (x*w->s_map.mapS) + j, (y*w->s_map.mapS) + i, color);
		}
	}
}

void draw_line(t_structure_main *w, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx, sy;

	if (x0 < x1)
		sx = 1;
	else
		sx = -1;

	if (y0 < y1)
		sy = 1;
	else
		sy = -1;

	int err = dx - dy;

	while (1)
	{
		put_pixel_img(w, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

float dist(float ax, float ay, float bx, float by)
{
	return ( sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)));
}

void rescale_image(void *mlx, void *win, void *original_img, int original_width, int original_height, int new_width, int new_height, int px, int py, t_structure_main *w)
{
	// Créez une nouvelle image avec la taille souhaitée
	void *rescaled_img = mlx_new_image(w->s_win.mlx, new_width, new_height);
	if (!rescaled_img)
	{
		// Gestion de l'erreur
		perror("Erreur lors de la création de la nouvelle image");
		return;
	}

	// Obtenez les adresses des données des images
	char *original_data = mlx_get_data_addr(original_img, &(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	char *rescaled_data = mlx_get_data_addr(rescaled_img, &(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));

	// Facteurs de redimensionnement
	float x_ratio = (float)original_width / new_width;
	float y_ratio = (float)original_height / new_height;

	// Parcourez chaque pixel de la nouvelle image
	for (int y = 0; y < new_height; ++y)
	{
		for (int x = 0; x < new_width; ++x)
		{
			// Calculez les coordonnées correspondantes dans l'image d'origine
			int original_x = x_ratio * x;
			int original_y = y_ratio * y;

			// Copiez la couleur du pixel de l'image d'origine vers la nouvelle image
			// Vous devrez ajuster les offsets en fonction de votre format de pixel
			// et de la profondeur des couleurs
			rescaled_data[y * new_width * 4 + x * 4 + 0] = original_data[original_y * original_width * 4 + original_x * 4 + 0];
			rescaled_data[y * new_width * 4 + x * 4 + 1] = original_data[original_y * original_width * 4 + original_x * 4 + 1];
			rescaled_data[y * new_width * 4 + x * 4 + 2] = original_data[original_y * original_width * 4 + original_x * 4 + 2];
			rescaled_data[y * new_width * 4 + x * 4 + 3] = original_data[original_y * original_width * 4 + original_x * 4 + 3];
		}
	}

	// Affichez la nouvelle image
	mlx_put_image_to_window(w->s_win.mlx, w->s_win.win, rescaled_img, px,py);

	// Libérez la mémoire de la nouvelle image (si vous n'en avez plus besoin)
	mlx_destroy_image(w->s_win.mlx, rescaled_img);
}

#include <stdio.h>  // Assurez-vous d'inclure stdio.h pour printf

void drawRays2D(t_structure_main *w) {
	int r, mx, my, mp, dof, color;
	float hrx, hry, ra, xo, yo, aTan, nTan;
	float vrx, vry, disT, rx, ry;
	float	disH = 1000000, disV = 1000000;

	draw_square_raw(w, 530, 0, 530+480, 160, 0xB2FFFF);
	draw_square_raw(w, 530, 160, 530+480, 320, 0x280000);

	ra = w->s_player.pa - DR * 30;
	r = 0;
	while (r < 60)
	{
		//ra += DR;
		while (ra < 0) { ra += 2 * PI; }
		while (ra >= 2 * PI) { ra -= 2 * PI; }

		dof = 0;
		aTan = -1 / tan(ra);
		//printf("Rayon %d: angle initial = %f\n", r, ra);  // Log de début de rayon

		if (ra > PI) {
			hry = (((int)w->s_player.py >> 6) << 6) - 0.0001;
			hrx = (w->s_player.py - hry) * aTan + w->s_player.px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI) {
			hry = (((int)w->s_player.py >> 6) << 6) + 64;
			hrx = (w->s_player.py - hry) * aTan + w->s_player.px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI) {
			hrx = w->s_player.px;
			hry = w->s_player.py;
			dof = 8;
		}
		while (dof < 8) {
			mx = (int)(hrx) >> 6;
			my = (int)(hry) >> 6;
			mp = my * w->s_map.mapX + mx;
			//if (mp < 0)
			//	mp = 0;
			//printf("Vérification de la collision horizontale: hrx = %f, hry = %f, mx = %d, my = %d, mp = %d\n", hrx, hry, mx, my, mp);  // Log de la collision
			if (mp > 0 && mp < w->s_map.mapX * w->s_map.mapY && map[mp] == 1) {
				dof = 8;
				disH = dist(w->s_player.px,w->s_player.py,hrx, hry);
				//printf("Mur touché horizontalement à hrx = %f, hry = %f\n", hrx, hry);  // Log du mur touché
			} else {
				hrx += xo;
				hry += yo;
				dof += 1;
			}
		}
		//draw_line(w, (int)w->s_player.px, (int)w->s_player.py, (int)rx, (int)ry, 0xFF0000);

		dof = 0;
		float nTan = -tan(ra); // Notez le signe négatif, qui est nécessaire pour certains quadrants.
		if (ra > P2 && ra < P3) {
			vrx = (((int)w->s_player.px >> 6) << 6) - 0.0001; // Déplacez vrx à gauche
			vry = (w->s_player.px - vrx) * nTan + w->s_player.py;
			xo = -64;
			yo = -xo * nTan;
		} else if (ra < P2 || ra > P3) {
			vrx = (((int)w->s_player.px >> 6) << 6) + 64; // Déplacez vrx à droite
			vry = (w->s_player.px - vrx) * nTan + w->s_player.py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI) { // Cas spécial pour les angles exacts
			vrx = w->s_player.px;
			vry = w->s_player.py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(vrx) >> 6;
			my = (int)(vry) >> 6;
			mp = my * w->s_map.mapX + mx;
			//printf("Vérification de la collision verticale: vrx = %f, vry = %f, mx = %d, my = %d, mp = %d\n", vrx, vry, mx, my, mp);  // Log de la collision
			if (mp > 0 && mp < w->s_map.mapX * w->s_map.mapY && map[mp] == 1) {
				dof = 8;
				disV = dist(w->s_player.px,w->s_player.py,vrx, vry);
				//printf("Mur touché verticalement à vrx = %f, vry = %f\n", vrx, vry);  // Log du mur touché
			} else {
				vrx += xo;
				vry += yo;
				dof += 1;
			}
		}
		if (disH > disV)
		{
			disT = disV;
			color = 0x00FF00;
			rx = vrx;
			ry = vry;
		}
		else
		{
			disT = disH;
			color = 0xFF0000;
			rx = hrx;
			ry = hry;
		}

		draw_line(w, (int)w->s_player.px, (int)w->s_player.py, (int)rx, (int)ry, color);
		
		float ca = w->s_player.pa-ra;
		if (ca<0)
			ca+=2*PI;
		if (ca>2*PI)
			ca-=2*PI;
		disT=disT*cos(ca);
		float lineH = (w->s_map.mapS*320)/disT;
		float lineO = 160-lineH/2;	
		if (lineH>320)
			lineH=320;
		draw_square_raw(w, r*8+530, lineO, r*8+538, lineH+lineO, color/2);

		r++;
		ra += DR;
		//printf("Fin du rayon %d: rx = %f, ry = %f\n\n", r, rx, ry);  // Log de fin de rayon
	}
}


void	draw_map(t_structure_main *w)
{

	int	x;
	int y;
	int	xo;
	int	yo;
	int color;

	//mlx_clear_window(w->s_win.mlx, w->s_win.win);
	//mlx_put_image_to_window(w->s_win.mlx, w->s_img.buffer, w->s_img.img_player,w->s_player.px, w->s_player.py);
	y = 0;
	while ( y < 8)
	{
		x = 0;
		while ( x < 8)
		{
			if (map[y*8+x] == 1)
				color = 0xFFFFFF;
			else
				color = 0x666666;
			xo = x + w->s_map.mapS;
			yo = y + w->s_map.mapS;
			draw_square(w, x, y, xo-1, yo-1, color);
			x++;
		}
		y++;
	}
}

int jkl = 0;
int yui = 0;

void test2(t_structure_main *w)
{

	mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.height, w->s_win.width);
	w->s_img.addr = mlx_get_data_addr(w->s_img.buffer, &(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	draw_map(w);
	//draw_square_raw(w, w->s_player.px-5, w->s_player.py-5, 10, 0xffff00);
	drawRays2D(w);
	mlx_put_image_to_window(w->s_win.mlx,w->s_win.win, w->s_img.buffer,0, 0);

	rescale_image(w->s_win.mlx,w->s_win.win,w->s_img.roomadslam[jkl],112,112,20,20,w->s_player.px-10, w->s_player.py-10,w);

}

void test(t_structure_main *w)
{
	int	x;
	int y;

	//////////gettimeofday(&(w->start_time), NULL);
	if (yui < 10)
	{
		usleep(1000);
		yui++;
	}
	else
	{
		yui = 0;
		jkl++;
		test2(w);
	}
	if (jkl == 10)
		jkl = 0;
	//mlx_put_image_to_window(w->s_win.mlx,w->s_win.win, w->s_img.roomadslam[jkl],0, 0);


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

void	init_windows(t_structure_main *w)
{
	int temp;
	w->s_win.height = 1400;
	w->s_win.width = 800;
	w->s_win.mlx = mlx_init();
	w->s_win.win = mlx_new_window(w->s_win.mlx, w->s_win.height, w->s_win.width, "WF99");
	w->s_player.px = 200;
	w->s_player.py = 200;
	w->s_player.pa = 0.1;
	w->s_player.pdx = cos(w->s_player.pa) * 5;
	w->s_player.pdy = sin(w->s_player.pa) * 5;

	w->s_img.img_player = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/player.xpm", &temp,&temp);
	w->s_img.img_wall = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/wall.xpm", &temp,&temp);
	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.height, w->s_win.width);
	// Initialiser le compteur de FPS
	gettimeofday(&(w->start_time), NULL);
	w->end_time = w->start_time;
	w->frame_count = 0;

	w->s_map.mapX = 8;
	w->s_map.mapY = 8;
	w->s_map.mapS = 64;

	w->s_img.roomadslam[0] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_02_delay-0.1s.xpm", &temp,&temp);
	w->s_img.roomadslam[1] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_03_delay-0.1s.xpm", &temp,&temp);
	w->s_img.roomadslam[2] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_04_delay-0.1s.xpm", &temp,&temp);
	w->s_img.roomadslam[3] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_05_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[4] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_06_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[5] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_07_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[6] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_08_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[7] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_09_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[8] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_10_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[9] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_11_delay-0.05s.xpm", &temp,&temp);
	w->s_img.roomadslam[10] = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/roomadslam/frame_12_delay-0.05s.xpm", &temp,&temp);

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
