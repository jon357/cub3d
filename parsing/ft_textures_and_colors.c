/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures_and_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:19:13 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 15:15:52 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	read_map_line(int fd, char *buffer, ssize_t *bytes_read)
{
	*bytes_read = read(fd, buffer, 1023);
	if (*bytes_read <= 0)
		return (false);
	buffer[*bytes_read] = '\0';
	return (true);
}

bool	process_line(char **map_buffer, int *map_length, char *line)
{
	ssize_t	bytes_read;
	size_t	new_total_size;

	bytes_read = ft_strlen(line);
	new_total_size = *map_length + bytes_read + 1;
	*map_buffer = ft_realloc(*map_buffer, new_total_size, *map_length);
	if (!*map_buffer)
	{
		perror("Error reallocating memory for map buffer");
		return (false);
	}
	ft_memcpy(*map_buffer + *map_length, line, bytes_read);
	*map_length += bytes_read;
	(*map_buffer)[*map_length] = '\0';
	return (true);
}

bool	handle_map(int fd, char **map_buffer, int *map_length)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	bool	start_copying;

	start_copying = false;
	*map_length = 0;
	*map_buffer = NULL;
	while (read_map_line(fd, buffer, &bytes_read))
	{
		if (!start_copying && (ft_strchr(buffer, '1')
				|| ft_strchr(buffer, '0')))
			start_copying = true;
		if (start_copying)
			if (!process_line(map_buffer, map_length, buffer))
				return (false);
	}
	return (*map_buffer != NULL);
}

bool	handle_textures(int fd, t_texture *textures)
{
	char	line[MAX_LINE_LENGTH];
	int		bytes_read;
	int		texture_count;
	char	ch;
	int		i;

	texture_count = 0;
	i = 0;
	while (texture_count < 4 && read(fd, &ch, 1) > 0)
	{
		if (ch != '\n')
			line[i++] = ch;
		else
		{
			line[i] = '\0';
			if (is_valid_texture(line))
			{
				parse_texture_line(line, textures);
				texture_count++;
				printf("Texture reconnue et traitée: '%s'\n", line);
			}
			i = 0;
		}
	}
	return (texture_count == 4);
}
