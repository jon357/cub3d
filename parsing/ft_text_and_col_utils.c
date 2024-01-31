/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_text_and_col_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:07:44 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 20:17:23 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	parse_texture_line(const char *line, t_texture *textures)
{
	char	direction[3];
	char	path[MAX_LINE_LENGTH];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != ' ' && line[i] != '\0' && i < 2)
		direction[i++] = line[i];
	direction[i] = '\0';
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	while (line[i] != ' ' && line[i] != '\0' && j < MAX_LINE_LENGTH - 1)
		path[j++] = line[i++];
	path[j] = '\0';
	if (ft_strcmp(direction, "NO") == 0)
		textures->north = ft_strdup(path);
	else if (ft_strcmp(direction, "SO") == 0)
		textures->south = ft_strdup(path);
	else if (ft_strcmp(direction, "WE") == 0)
		textures->west = ft_strdup(path);
	else if (ft_strcmp(direction, "EA") == 0)
		textures->east = ft_strdup(path);
	return (true);
}

bool	parse_number_from_str(const char **str, int *number)
{
	*number = 0;
	while (**str >= '0' && **str <= '9')
	{
		*number = *number * 10 + (**str - '0');
		(*str)++;
	}
	if (**str != ',' && **str != ' ' && **str != '\0')
	{
		return (false);
	}
	return (true);
}

bool	parse_color_line(const char *line, unsigned int *color)
{
	int			r;
	int			g;
	int			b;
	const char	*ptr;

	r = 0;
	g = 0;
	b = 0;
	ptr = line;
	while (*ptr == ' ')
		ptr++;
	if (!parse_number_from_str(&ptr, &r) || *ptr++ != ',')
		return (false);
	while (*ptr == ' ')
		ptr++;
	if (!parse_number_from_str(&ptr, &g) || *ptr++ != ',')
		return (false);
	while (*ptr == ' ')
		ptr++;
	if (!parse_number_from_str(&ptr, &b))
		return (false);
	*color = (r << 16) | (g << 8) | b;
	return (true);
}

bool	is_valid_texture(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0);
}
