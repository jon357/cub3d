#include "cub3d.h"

void put_pixel_img(t_structure_main *w, int x, int y, int color) {
	char *dst;

	// Correction : x vérifié avec la largeur et y avec la hauteur
	if (x >= 0 && y >= 0 && x < w->s_win.width && y < w->s_win.height) {
		dst = w->s_img.addr + (y * w->s_img.line_len + x * (w->s_img.bpp / 8));
		*(unsigned int *)dst = color;
	} else {
		// Ajout de logs pour les cas où les coordonnées sont hors limites
		//printf("put_pixel_img: pixel hors limites (x: %d, y: %d)\n", x, y);
	}
}

void draw_square_raw(t_structure_main *w, int x, int y, int xo, int yo, int color)
{
	int i;
	int j;

	int size_x = abs(xo - x);
	int size_y = abs(yo - y);
	//printf("draw_square_raw called with x: %d, y: %d, xo: %d, yo: %d\n", x, y, xo, yo);
	//printf("Calculated size_x: %d, size_y: %d\n", size_x, size_y);

	for (i = 0; i < size_y; i++)
	{
		for (j = 0; j < size_x; j++)
		{
			put_pixel_img(w, (x) + j, (y) + i, color);
			//printf("Drawing pixel at x: %d, y: %d\n", (x) + j, (y) + i);
		}
	}
	 //printf("draw_square_raw completed\n");
}

void draw_square(t_structure_main *w, int x, int y, int color) {
	int xo = x * w->s_map.mapS;  // Coordonnée X en pixels
	int yo = y * w->s_map.mapS;  // Coordonnée Y en pixels
	int size = w->s_map.mapS;	// Taille du carré

	// Dessiner le carré en utilisant la taille et les coordonnées calculées
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			put_pixel_img(w, xo + j, yo + i, color);
		}
	}
}



void draw_line(t_structure_main *w, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx, sy;
	//printf("draw_line - x0: %d, y0: %d, x1: %d, y1: %d\n", x0, y0, x1, y1);


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
		//printf("Tracing - x0: %d, y0: %d\n", x0, y0);
	}
	//printf("draw_line completed\n");

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

float correctFisheye(float distance, float ra, float playerAngle) {
	float ca = playerAngle - ra;
	if (ca < 0) ca += 2 * PI;
	if (ca > 2 * PI) ca -= 2 * PI;
	return distance * cos(ca);
}

void calculateVerticalRay(t_structure_main *w, float ra, float *disV, float *vx, float *vy, WallDirection *wallDir) {
	int dof = 0, mx, my, mp;
	float rx, ry, xo, yo;
	int tileSize = w->s_map.mapS;
	*disV = 100000;  // Distance initialement grande
	*wallDir = NONE;
	float nTan = -tan(ra);

	if (ra > P2 && ra < P3) {
		rx = (((int)w->s_player.px / tileSize) * tileSize) - 0.0001;
		ry = (w->s_player.px - rx) * nTan + w->s_player.py;
		xo = -tileSize;
		yo = -xo * nTan;
	} else if (ra < P2 || ra > P3) {
		rx = (((int)w->s_player.px / tileSize) * tileSize) + tileSize;
		ry = (w->s_player.px - rx) * nTan + w->s_player.py;
		xo = tileSize;
		yo = -xo * nTan;
	} else {  // Rayon directement en haut ou en bas
		rx = w->s_player.px;
		ry = w->s_player.py;
		dof = 35;
	}

	while (dof < 35) {
		mx = (int)(rx) / tileSize;
		my = (int)(ry) / tileSize;
		mp = my * w->s_map.mapX + mx;
		if (mp >= 0 && mp < w->s_map.mapX * w->s_map.mapY && w->s_map.map[mp] == '1') {
			dof = 35;
			*vx = rx;
			*vy = ry;
			*disV = dist(w->s_player.px, w->s_player.py, rx, ry);
			  if (ra > P2 && ra < P3) {
				*wallDir = WEST;
			} else {
				*wallDir = EAST;
			}
		} else {
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	//printf("tileSize: %d\n", tileSize);
	//printf("Ray Angle (ra): %f\n", ra);

	//printf("Vertical Ray: Angle = %f, Iteration = %d, rx = %f, ry = %f, disV = %f, wallDir = %d\n", ra, dof, rx, ry, *disV, *wallDir);
	}


void calculateHorizontalRay(t_structure_main *w, float ra, float *disH, float *hx, float *hy, WallDirection *wallDir) {
	int dof = 0, mx, my, mp;
	float rx, ry, xo, yo;
	int tileSize = w->s_map.mapS;
	*disH = 100000;  // Distance initialement grande
	*wallDir = NONE;

	float aTan = -1 / tan(ra);
	if (ra > PI) {
		ry = (((int)w->s_player.py / tileSize) * tileSize) - 0.0001;
		rx = (w->s_player.py - ry) * aTan + w->s_player.px;
		yo = -tileSize;
		xo = -yo * aTan;
	} else if (ra < PI) {
		ry = (((int)w->s_player.py / tileSize) * tileSize) + tileSize;
		rx = (w->s_player.py - ry) * aTan + w->s_player.px;
		yo = tileSize;
		xo = -yo * aTan;
	} else {  // Rayon directement à gauche ou à droite
		rx = w->s_player.px;
		ry = w->s_player.py;
		dof = 35;
	}
	while (dof < 35) {
		mx = (int)(rx) / tileSize;
		my = (int)(ry) / tileSize;
		mp = my * w->s_map.mapX + mx;
		if (mp >= 0 && mp < w->s_map.mapX * w->s_map.mapY && w->s_map.map[mp] == '1') {
			dof = 35;
			*hx = rx;
			*hy = ry;
			*disH = dist(w->s_player.px, w->s_player.py, rx, ry);
			 if (ra > PI) {
				*wallDir = NORTH;
			} else {
				*wallDir = SOUTH;
			}
		} else {
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	//printf("tileSize: %d\n", tileSize);
	//printf("Ray Angle (ra): %f\n", ra);
	//printf("Horizontal Ray: Angle = %f, Iteration = %d, rx = %f, ry = %f, disH = %f, wallDir = %d\n", ra, dof, rx, ry, *disH, *wallDir);

}

void load_wall_textures(t_structure_main *w) {
	// Initialiser la largeur et la hauteur des textures
	int width = 0;
	int height = 0;

	// Charger la texture Nord et vérifier si elle est chargée correctement
	w->s_img.north_texture = mlx_xpm_file_to_image(w->s_win.mlx, "textures/NO.xpm", &width, &height);
	if (!w->s_img.north_texture) {
		fprintf(stderr, "Failed to load North texture.\n");
		exit_error(w);  // Remplacez par votre propre gestion des erreurs
	}

	// Charger la texture Sud et vérifier si elle est chargée correctement
	w->s_img.south_texture = mlx_xpm_file_to_image(w->s_win.mlx, "textures/SO.xpm", &width, &height);
	if (!w->s_img.south_texture) {
		fprintf(stderr, "Failed to load South texture.\n");
		exit_error(w);
	}

	// Charger la texture Ouest et vérifier si elle est chargée correctement
	w->s_img.west_texture = mlx_xpm_file_to_image(w->s_win.mlx, "textures/WE.xpm", &width, &height);
	if (!w->s_img.west_texture) {
		fprintf(stderr, "Failed to load West texture.\n");
		exit_error(w);
	}

	// Charger la texture Est et vérifier si elle est chargée correctement
	w->s_img.east_texture = mlx_xpm_file_to_image(w->s_win.mlx, "textures/EA.xpm", &width, &height);
	if (!w->s_img.east_texture) {
		fprintf(stderr, "Failed to load East texture.\n");
		exit_error(w);
	}

	// Stocker la largeur et la hauteur pour une utilisation ultérieure
	w->s_img.texture_width = width;
	w->s_img.texture_height = height;
	//printf("Texture Width: %d, Texture Height: %d\n", w->s_img.texture_width, w->s_img.texture_height);
	//printf("All wall textures loaded successfully.\n");
}

void exit_error(t_structure_main *w) {
	// Libérer les ressources, fermer la fenêtre, etc.
	// ...
	exit(1);
}

void draw_background(t_structure_main *w) {
	// Vérifier si les valeurs de la fenêtre sont initialisées
	if (w->s_win.height <= 0 || w->s_win.width <= 0) {
		fprintf(stderr, "Erreur: Dimensions de la fenêtre non initialisées ou incorrectes.\n");
		return;
	}

	// Largeur de décalage vers la droite
	int backgroundOffsetX = 0; // Vous pouvez ajuster cette valeur selon votre besoin

	int start3DHeight = 0;
	int end3DHeight = w->s_win.height;
	int half3DHeight = (end3DHeight - start3DHeight) / 2;
	//printf("end3DHeight: %d\n", end3DHeight);

	// Vérifier la cohérence des hauteurs calculées
	if (half3DHeight <= 0) {
		fprintf(stderr, "Erreur: Calcul de la moitié de la hauteur 3D incorrect.\n");
		return;
	}

	int skyEndHeight = start3DHeight + half3DHeight;

	// Dessiner le ciel (sky) avec un décalage vers la droite
	draw_square_raw(w, backgroundOffsetX, start3DHeight, w->s_win.width + backgroundOffsetX, half3DHeight + start3DHeight, 0x766f66);

	// Dessiner le sol (ground) avec un décalage vers la droite
	draw_square_raw(w, backgroundOffsetX, skyEndHeight, w->s_win.width + backgroundOffsetX, w->s_win.height, 0x4f595d);
}


int getTextureColor(t_structure_main *w, WallDirection wallDir, int textureX, int textureY) {
	char *texture_data;
	int bpp, size_line, endian;

	// Sélectionner la texture en fonction de la direction du mur
	void *selected_texture;
	switch (wallDir) {
		case NORTH:
			selected_texture = w->s_img.north_texture;
			break;
		case SOUTH:
			selected_texture = w->s_img.south_texture;
			break;
		case WEST:
			selected_texture = w->s_img.west_texture;
			break;
		case EAST:
			selected_texture = w->s_img.east_texture;
			break;
		default:
			fprintf(stderr, "Invalid wall direction.\n");
			exit_error(w); // Gestion des erreurs
			return 0; // Retourne une couleur par défaut en cas d'erreur
	}

	// Obtenir l'adresse de la texture
	texture_data = mlx_get_data_addr(selected_texture, &bpp, &size_line, &endian);
	//printf("TextureX: %d, TextureY: %d\n", textureX, textureY);
	//printf("BPP: %d, Size Line: %d, Endian: %d\n", bpp, size_line, endian);

	// Calculer la position de la couleur dans la texture
	int pixel_pos = (textureX + (textureY * w->s_img.texture_width)) * (bpp / 8);
	//printf("Pixel Position: %d\n", pixel_pos);

	// Récupérer la couleur de la texture à la position calculée
	int color = *(int *)(texture_data + pixel_pos);
	return color;
}

static void draw_texture(t_structure_main *w, int startX, int endX, float lineOff, float lineH, WallDirection wallDir, float rx, float ry) {
	int textureWidth = w->s_img.texture_width;
	int textureHeight = w->s_img.texture_height;

	for (int y = lineOff; y < lineOff + lineH; y++) {
		// La variable perspectiveFactor permet de mapper la texture en tenant compte de la perspective
		float perspectiveFactor = (float)(y - lineOff) / lineH;
		int textureY = perspectiveFactor * textureHeight;
		if (textureY >= textureHeight) {
			textureY = textureHeight - 1;
		}

		for (int x = startX; x < endX; x++) {
			int x = startX;
			int textureX;
			switch (wallDir) {
				case NORTH:
				case SOUTH:
					// Assurez-vous que rx est normalisé correctement pour le mappage de texture
					textureX = (int)(rx * textureWidth / w->s_map.mapS) % textureWidth;
					break;
				case WEST:
				case EAST:
					// Assurez-vous que ry est normalisé correctement pour le mappage de texture
					textureX = (int)(ry * textureWidth / w->s_map.mapS) % textureWidth;
					break;
			}
			if (textureX >= textureWidth) {
				textureX = textureWidth - 1;
			}
			int color = getTextureColor(w, wallDir, textureX, textureY);
			put_pixel_img(w, x, y, color);
		}
	}
}


static void draw_yolo(t_structure_main *w, int startX, int endX, float lineOff, float lineH, WallDirection wallDir, float rx, float ry, int merde) {
	int textureWidth = w->s_img.texture_width;
	int textureHeight = w->s_img.texture_height;

	int iii = 0;
	for (int y = lineOff; y < lineOff + lineH; y++) {
		// La variable perspectiveFactor permet de mapper la texture en tenant compte de la perspective
		float perspectiveFactor = (float)(y - lineOff) / lineH;
		int textureY = perspectiveFactor * (textureHeight );
		if (textureY >= textureHeight) {
			textureY = textureHeight - 1;
		}

		//for (int x = startX; x < endX; x++) {
			int x = startX;
			int textureX;
			switch (wallDir) {
				case NORTH:
				case SOUTH:
					// Assurez-vous que rx est normalisé correctement pour le mappage de texture
					textureX = (int)(rx * textureWidth / w->s_map.mapS) % textureWidth;
					break;
				case WEST:
				case EAST:
					// Assurez-vous que ry est normalisé correctement pour le mappage de texture
					textureX = (int)(ry * textureWidth / w->s_map.mapS) % textureWidth;
					break;
			}
			if (textureX >= textureWidth) {
				textureX = textureWidth - 1;
			}
			//printf("%f %f\n",lineOff, lineOff/lineH);
		
		
			int color = getTextureColor(w, wallDir, textureX, y);
		
		
		//	BLOCK OK MEH
		//	float ww = ((720+merde)/lineH);
		//	//printf("%d %d %d\n", t ,td, merde);
		//	put_pixel_img(w, x, (int)(iii*ww)-merde/2, color);	
		//	iii++;
			
			int t=y+merde/2;
			int td=y-merde/2;
			float ww = ((720+merde)/lineH);

			int a = lineOff-merde/2;
			int b = lineH+(merde/2);
			int c = lineH;
			double step = (b - a)/(double)(c - 1);
			//printf("%d %d %d\n", t ,td, merde);
			put_pixel_img(w, x, (int)(a + iii * step), color);
			iii++;
		//}
	}
}




void drawRay(t_structure_main *w, int r, float rx, float ry, float disT, WallDirection wallDir, int numRays, int color) {
	int tileSize = w->s_map.mapS;
	int start3DHeight = 0; // Début en haut de la fenêtre
	int max3DHeight = w->s_win.height + start3DHeight;

	// Assurez-vous que la fenêtre 3D ne dépasse pas la hauteur du background
	/*if (max3DHeight > w->s_win.height) {
		max3DHeight = w->s_win.height;
	}*/

	float lineH = (tileSize * max3DHeight) / disT;
	lineH = lineH > max3DHeight ? max3DHeight : lineH;
	float lineOff = ((max3DHeight - lineH) / 2);
//	printf("drawRay - rx: %f, ry: %f\n", rx, ry);

	float OlineH = (w->s_map.mapS*720)/disT;
	//if (OlineH>320) OlineH=320;
	float OlineOff = 160-OlineH/2;	

	// Décalage horizontal de l'arrière-plan

	// Calculer les coordonnées de début et de fin du rayon ajustées pour le décalage
	int rayWidth = w->s_win.width / numRays;

	int startX = r * rayWidth;
	int endX = startX + rayWidth;

	// Ajouter le décalage horizontal à toutes les coordonnées X
	//printf("lineH: %f, lineOff: %f, rayWidth: %d\n", lineH, lineOff, rayWidth);


	// Ajouter des instructions de débogage pour afficher les valeurs de startX et endX
	//printf("Ray %d - startX: %d, endX: %d\n", r, startX, endX);
//	printf("drawRay - rx: %f, ry: %f\n", rx, ry);
	// Dessiner le rayon
	draw_line(w, (int)w->s_player.px, (int)w->s_player.py, (int)rx, (int)ry, color);

	int merde;
	int merde2;
	if (OlineH > 720)
		merde = OlineH - 720;
	else
		merde = 0;
	// Dessiner la texture ajustée pour le décalage
//	printf("m=%d OH=%f h=%f f=%f Of=%f\n", merde, OlineH, lineH, lineOff, OlineOff);
	color = 0x000000;
	draw_square_raw(w, r*rayWidth, lineOff, r*rayWidth+rayWidth, lineH+lineOff, color);
	if (merde != 0)
		draw_yolo(w, startX, endX, lineOff, lineH, wallDir, rx, ry, merde);
	else
		draw_texture(w, startX, endX, lineOff, lineH, wallDir, rx, ry);

}

void drawRays2D(t_structure_main *w) {
	int r, color, my, mx, dof, yo, xo, mp;
	float ra, disH, disV, disT, hx, hy, vx, vy, ry, rx;
	WallDirection hWallDir, vWallDir;
	int tileSize = w->s_map.mapS;
	int numRays = 1280;
	float FOV = 60 * (PI / 180);
	float DR = FOV / numRays;

	printf ("%f\n\n\n\n\n\n\n\n\n\n",DR);
	// Ajouter des logs pour vérifier les valeurs
	//printf("numRays: %d\n", numRays);
	//printf("FOV: %f\n", FOV);
	//printf("DR: %f\n", DR);

	draw_background(w);
	draw_map(w);

	ra = w->s_player.pa - (FOV / 2);
	for (r = 0; r < numRays; r++) {
		ra = fmod(ra + 2 * PI, 2 * PI);  // Maintenir ra dans l'intervalle [0, 2*PI]

		calculateHorizontalRay(w, ra, &disH, &hx, &hy, &hWallDir);
		calculateVerticalRay(w, ra, &disV, &vx, &vy, &vWallDir);

		disT = (disH < disV) ? disH : disV;
		color = (disH < disV) ? 0xFF0000 : 0x00FF00;
		WallDirection wallDir = (disH < disV) ? hWallDir : vWallDir;

		disT = correctFisheye(disT, ra, w->s_player.pa);


		// Ajouter des logs pour déboguer
		//printf("Ray ID: %d\n", r);
		//printf("Ray Angle: %f\n", ra);
		//printf("Shortest Distance: %f\n", disT);
		//printf("Wall Direction: %d\n", wallDir);
//
//
		ra += DR; 
		if (disH > disV)	{rx = vx;	ry = vy;	disT = disV;	color = 0x00FF00;}
		if (disH < disV)	{rx = hx;	ry = hy;	disT = disH;	color = 0xFF0000;}

		draw_line(w, (int)w->s_player.px, (int)w->s_player.py, (int)rx, (int)ry, color);
		
		float ca = w->s_player.pa-ra;
		if (ca<0) ca+=2*PI;
		if (ca>2*PI) ca-=2*PI;
		disT=disT*cos(ca);
		float lineH = (w->s_map.mapS*w->s_win.height)/disT;
		if (lineH>320) lineH=320;
		float lineOff = (160-lineH)/2;	
		drawRay(w, r, (disH < disV) ? hx : vx, (disH < disV) ? hy : vy, disT, wallDir, numRays, color);
	}
}




void draw_map(t_structure_main *w) {
	if (!w->s_map.map) {
		printf("Erreur: La carte n'a pas été chargée correctement.\n");
		return;
	}

	//printf("Drawing map of size: %d x %d\n", w->s_map.mapX, w->s_map.mapY);

	for (int y = 0; y < w->s_map.mapY; y++) {
		int lineLength = 0; // Longueur réelle de la ligne
		while (lineLength < w->s_map.mapX && w->s_map.map[y * w->s_map.mapX + lineLength] != '\n' && w->s_map.map[y * w->s_map.mapX + lineLength] != '\0') {
			lineLength++;
		}

		for (int x = 0; x < lineLength; x++) {
			int index = y * w->s_map.mapX + x;
			if (index >= w->s_map.mapX * w->s_map.mapY) {
				fprintf(stderr, "Erreur: Tentative d'accès hors limites de la carte à l'indice %d.\n", index);
				continue;
			}

		int color;
		float alpha; // Définissez la transparence ici (0.0 pour totalement transparent, 1.0 pour totalement opaque)

		switch (w->s_map.map[index]) {
		case '1':
		color = 0xFFFFFF;
		break;
		case '0':
		color = 0x000000;
		break;
		default:
		color = 0x000000;
		break;
}

			//printf("Drawing square at (x: %d, y: %d) with color: 0x%06X\n", x, y, color);

			draw_square(w, x, y, color);
		}
	}
}


int jkl = -1;
int yui = 0;

void test2(t_structure_main *w) {
	mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.width, w->s_win.height);
	w->s_img.addr = mlx_get_data_addr(w->s_img.buffer, &(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	draw_map(w);
	drawRays2D(w);

	//drawRays2D(w);

	mlx_put_image_to_window(w->s_win.mlx, w->s_win.win, w->s_img.buffer, 0, 0);

	int new_sprite_width = w->s_map.mapS;
	int new_sprite_height = w->s_map.mapS;
	int sprite_x = w->s_player.px - new_sprite_width / 2;
	int sprite_y = w->s_player.py - new_sprite_height / 2;

	// Log des valeurs pour le débogage
	/*printf("Sprite (x, y): (%d, %d), Size (w, h): (%d, %d), MapS: %d\n",
		   sprite_x, sprite_y, new_sprite_width, new_sprite_height, w->s_map.mapS);*/

	// Redimensionner et dessiner le sprite du personnage
	rescale_image(w->s_win.mlx, w->s_win.win, w->s_img.roomadslam[jkl],
				  112, 112, new_sprite_width, new_sprite_height, sprite_x, sprite_y, w);
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
		//mlx_mouse_move(w->s_win.mlx, w->s_win.win, w->s_win.height/2, w->s_win.width/2);
		mlx_mouse_get_pos(w->s_win.mlx, w->s_win.win, &x, &y);
		if ((x > 0 && x < w->s_win.width) && (y > 0 && y < w->s_win.height))
			{
				if (x < w->s_win.width/2-40)
					deal_key(65361,w);
				else if (x > w->s_win.width/2+40)
					deal_key(65363,w);
			}
	}
	if (jkl == 10)
		jkl = -1;
}

void	init_windows(t_structure_main *w)
{
	int temp;
	w->s_win.width = 1280;
	w->s_win.height = 720;

	w->s_win.mlx = mlx_init();
	if (w->s_win.mlx == NULL) {
	fprintf(stderr, "Erreur : Échec de mlx_init.\n");
	return; // Ajoutez un retour ou une gestion d'erreur appropriée
	}
	w->s_win.win = mlx_new_window(w->s_win.mlx, w->s_win.width, w->s_win.height, "Cub3D");
	if (w->s_win.win == NULL) {
	fprintf(stderr, "Erreur : Échec de mlx_new_window.\n");
	return; // Ajoutez un retour ou une gestion d'erreur appropriée
	}
	w->s_player.px = 10;
	w->s_player.py = 10;
	w->s_player.pa = 0.1;
	w->s_player.pdx = cos(w->s_player.pa) * 5;
	w->s_player.pdy = sin(w->s_player.pa) * 5;
	load_wall_textures(w);
	// Après le chargement des textures
	printf("Window Dimensions: Width = %d, Height = %d\n", w->s_win.width, w->s_win.height);
	printf("Texture Dimensions: Width = %d, Height = %d\n", w->s_img.texture_width, w->s_img.texture_height);


	w->s_img.img_player = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/player.xpm", &temp,&temp);
	w->s_img.img_wall = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/wall.xpm", &temp,&temp);
	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.width, w->s_win.height);

	// Vérifiez ensuite que ces dimensions correspondent à la taille de la fenêtre
	if (w->s_img.buffer == NULL) {
	fprintf(stderr, "Erreur : Échec de mlx_new_image pour le buffer.\n");
	return; // Gestion d'erreur appropriée
	} else {
		// Vérification des dimensions du buffer
		int bpp, size_line, endian;
		char *buffer_addr = mlx_get_data_addr(w->s_img.buffer, &bpp, &size_line, &endian);
		if (buffer_addr == NULL) {
			fprintf(stderr, "Erreur : Impossible d'obtenir l'adresse du buffer.\n");
		} else {
			fprintf(stdout, "Buffer créé avec Largeur: %d, Hauteur: %d\n", w->s_win.width, w->s_win.height);
			fprintf(stdout, "BPP (bits per pixel) : %d, Size line : %d, Endian : %d\n", bpp, size_line, endian);
		}
	}

	// Initialiser le compteur de FPS
	gettimeofday(&(w->start_time), NULL);
	w->end_time = w->start_time;
	w->frame_count = 0;

	int mapS_x = w->s_win.width / (w->s_map.mapX * 4);
	int mapS_y = w->s_win.height / (w->s_map.mapY * 2);
	w->s_map.mapS = (mapS_x < mapS_y) ? mapS_x : mapS_y;


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

	w->s_img.pedro_wall = mlx_xpm_file_to_image(w->s_win.mlx, "sprite/pedrop/frame_061_delay-0.03s.xpm", &temp,&temp);
	//if (!w->s_img.pedro_wall)
	//	printf("nop\n");

}

int main(int argc, char **argv) {
	t_structure_main w;

	// Vérifier si un nom de fichier a été fourni
	if (argc < 2) {
		printf("Usage: %s <path to map file>\n", argv[0]);
		return 1;
	}

	// Parser la carte
	//parse_map(argv[1], &w.s_map);
	   if (!parse_map(argv[1], &w.s_map)) {
		printf("Failed to load the map or map is not closed. Exiting...\n");
		return 1;  // Quitter avec un code d'erreur
	}

	// Vérifier si la carte a été chargée correctement
	if (w.s_map.map == NULL) {
		printf("Failed to load the map.\n");
		return 1;
	}

	// Initialiser la fenêtre et d'autres composants
	init_windows(&w);

	// Configurer les hooks et entrer dans la boucle principale
	mlx_loop_hook(w.s_win.mlx, (void *)test, &w);
	mlx_hook(w.s_win.win, 2, 1L<<0, deal_key, &w);
	mlx_hook(w.s_win.win,  17, 0, (void *)kill_prog, &w);
	mlx_loop(w.s_win.mlx);

	// Libérer la carte une fois que vous avez terminé
	return 0;
}
