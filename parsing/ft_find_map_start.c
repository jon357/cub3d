/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_map_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:04:23 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 18:02:53 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	process_color_line(const char *line, t_texture *textures)
{
	if (line[0] == 'F')
		parse_color_line(line + 1, &textures->floor_color);
	else if (line[0] == 'C')
		parse_color_line(line + 1, &textures->ceil_color);
	else
		return (false);
	printf("Couleur reconnue et traitée: '%s'\n", line);
	return (true);
}

bool	handle_colors(int fd, t_texture *textures)
{
	char	line[MAX_LINE_LENGTH];
	int		color_count;
	char	ch;
	int		i;

	color_count = 0;
	i = 0;
	while (color_count < 2 && read(fd, &ch, 1) > 0)
	{
		if (ch != '\n')
		{
			line[i++] = ch;
		}
		else
		{
			line[i] = '\0';
			printf("Ligne lue pour les couleurs: '%s'\n", line);
			if ((line[0] == 'F' || line[0] == 'C')
				&& process_color_line(line, textures))
				color_count++;
			i = 0;
		}
	}
	return (color_count == 2);
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
	}
	return (fd);
}

bool	cleanup_and_close(int fd, char *map_buffer, bool result)
{
	if (map_buffer)
	{
		free(map_buffer);
	}
	close(fd);
	return (result);
}

bool	load_cub_file(const char *filename,
		t_texture *textures, t_structure_map *map_info)
{
	char	*map_buffer;
	int		map_length;
	bool	result;
	int		fd;

	map_buffer = NULL;
	map_length = 0;
	fd = open_file(filename);
	if (fd < 0)
		return (false);
	if (!handle_textures(fd, textures) || !handle_colors(fd, textures))
		return (cleanup_and_close(fd, map_buffer, false));
	if (!handle_map(fd, &map_buffer, &map_length))
	{
		perror("Error reading map");
		return (cleanup_and_close(fd, map_buffer, false));
	}
	if (map_buffer)
		result = parse_map(map_buffer, map_length, map_info);
	else
	{
		printf("No map data found in file.\n");
		result = false;
	}
	return (cleanup_and_close(fd, map_buffer, result));
}
