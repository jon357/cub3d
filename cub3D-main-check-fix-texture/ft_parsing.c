#include "cub3d.h"

char* read_map(const char* filename, int* length) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("Error opening file");
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	*length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *buffer = malloc(*length + 1);
	if (!buffer) {
		perror("Error allocating memory for map");
		fclose(file);
		return NULL;
	}

	fread(buffer, 1, *length, file);
	buffer[*length] = '\0';

	fclose(file);
	return buffer;
}

int is_map_closed(char* map, int maxWidth, int height) {
    // Vérifier le bord supérieur et inférieur pour chaque colonne
    for (int x = 0; x < maxWidth; x++) {
        if (map[x] != '1' && map[x] != ' ') {  // Haut
            printf("Open space on top border at (%d,0)\n", x);
            return 0;
        }
        if (map[(height - 1) * maxWidth + x] != '1' && map[(height - 1) * maxWidth + x] != ' ') {  // Bas
            printf("Open space on bottom border at (%d,%d)\n", x, height - 1);
            return 0;
        }
    }

    // Vérifier les bords gauche et droit pour chaque ligne
    for (int y = 0; y < height; y++) {
        int lineLength = 0;  // Longueur réelle de la ligne courante
        for (int x = 0; x < maxWidth && map[y * maxWidth + x] != ' '; x++) {
            lineLength++;
        }

        if (lineLength > 0) {
            if (map[y * maxWidth] != '1') {  // Gauche
                printf("Open space on left border at (0,%d)\n", y);
                return 0;
            }
            if (map[y * maxWidth + lineLength - 1] != '1') {  // Droite
                printf("Open space on right border at (%d,%d)\n", lineLength - 1, y);
                return 0;
            }
        }

        // Vérification de l'intérieur de la carte pour les espaces non enclos
        for (int x = 1; x < lineLength - 1; x++) {
            char c = map[y * maxWidth + x];
            if (c == ' ') {
                if (map[y * maxWidth + (x - 1)] != '1' ||  // Gauche
                    map[y * maxWidth + (x + 1)] != '1' ||  // Droite
                    (y > 0 && map[(y - 1) * maxWidth + x] != '1') ||  // Haut
                    (y < height - 1 && map[(y + 1) * maxWidth + x] != '1')) {  // Bas
                    printf("Space not enclosed by walls at (%d,%d)\n", x, y);
                    return 0;
                }
            }
        }
    }
    return 1;  // Map is closed
}

bool parse_map(const char* filename, t_structure_map *map_info) {
	int length;
	char* buffer = read_map(filename, &length);
	if (!buffer) {
		printf("Failed to read the map file.\n");
		return (false);
	}

	int maxWidth = 0;
	int currentWidth = 0;  // La largeur de la ligne actuelle
	int height = 0;

	for (int i = 0; i < length; i++) {
		if (buffer[i] == '\n') {
			height++;  // Nouvelle ligne, augmenter le compteur de hauteur
			if (currentWidth > maxWidth) {
				maxWidth = currentWidth;  // Mise à jour de la largeur maximale si nécessaire
			}
			currentWidth = 0;  // Réinitialiser la largeur pour la nouvelle ligne
		} else if (buffer[i] != '\r') {  // Ignorer les retours chariot
			currentWidth++;  // Augmenter la largeur de la ligne actuelle
		}
	}

	// Gérer la dernière ligne si elle ne se termine pas par '\n'
	if (currentWidth > 0) {
		height++;
		if (currentWidth > maxWidth) {
			maxWidth = currentWidth;
		}
	}

	// Vérification des dimensions de la carte
	if (maxWidth <= 0 || height <= 0) {
		printf("Invalid map dimensions: maxWidth=%d, height=%d\n", maxWidth, height);
		free(buffer);
		return (false);
	}

	// Allocation de la mémoire pour la carte
	map_info->mapX = maxWidth;
	map_info->mapY = height;
	map_info->map = malloc(maxWidth * height);
	if (!map_info->map) {
		perror("Failed to allocate memory for map");
		free(buffer);
		return (false);
	}

	// Remplir la carte avec des espaces pour gérer les lignes de longueur variable
	for (int i = 0; i < maxWidth * height; i++) {
		map_info->map[i] = ' ';
	}

	// Copie des données de la carte
	int x = 0, y = 0;
	for (int i = 0; i < length; i++) {
		if (buffer[i] == '\n') {
			y++;
			x = 0;
		} else if (buffer[i] != '\r') {  // Ignorer les retours chariot
			if (x < maxWidth) {
				map_info->map[y * maxWidth + x] = buffer[i];
				x++;
			}
		}
	}

	printf("Width: %d, Height: %d, Total length: %d\n", maxWidth, height, length);

	// Vérifier si la carte est fermée
    if (!is_map_closed(map_info->map, maxWidth, height)) {
        printf("Map is not closed!\n");
        free(buffer);
        return false;  // Indique un échec
    } else {
        printf("Map is valid and closed.\n");
    }

    free(buffer);
    return true;  // Indique un succès
}
