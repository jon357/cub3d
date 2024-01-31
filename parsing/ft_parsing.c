/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:46 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 19:51:28 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	init_map_info(t_structure_map *map_info, int maxWidth, int height)
{
	map_info->map_x = maxWidth;
	map_info->map_y = height;
	map_info->s_win.width = WIDTH;
	map_info->s_win.height = HEIGHT;
	map_info->map = malloc(maxWidth * height);
	if (!map_info->map)
	{
		perror("Failed to allocate memory for map");
		return (false);
	}
	fill_map_space(map_info, maxWidth, height);
	return (true);
}

bool	copy_map_data_and_check(t_map_params *params)
{
	copy_map_data(params);
	if (!is_map_closed(params->map_info->map,
			*params->max_width, *params->height))
	{
		printf("Map is not closed!\n");
		free(params->map_info->map);
		return (false);
	}
	return (true);
}

void	calculate_map(t_structure_map *map_info)
{
	float	maps_x;
	float	maps_y;

	maps_x = (float)map_info->s_win.width / (map_info->map_x * 4);
	maps_y = (float)map_info->s_win.height / (map_info->map_y * 2);
	if (maps_x < maps_y)
	{
		map_info->map_s = (int)maps_x;
	}
	else
	{
		map_info->map_s = (int)maps_y;
	}
	if (map_info->map_s == 0)
	{
		map_info->map_s = 1;
	}
}

bool	parse_map(const char *map_content, int length,
	t_structure_map *map_info)
{
	t_map_params	map_params;
	int				max_width;
	int				height;

	max_width = 0;
	height = 0;
	map_params.map_info = map_info;
	map_params.buffer = map_content;
	map_params.length = length;
	map_params.max_width = &max_width;
	map_params.height = &height;
	get_map_dimensions(&map_params);
	if (max_width <= 0 || height <= 0)
	{
		printf("Invalid map dimensions\n");
		return (false);
	}
	if (!init_map_info(map_info, max_width, height))
		return (false);
	if (!find_player(map_content, length, map_info))
		return (false);
	return (copy_map_data_and_check(&map_params));
}
