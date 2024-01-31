/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_player_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:57:38 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 16:50:06 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_variables(int *i, int *line_number,
	int *column_number, bool *found_player)
{
	*i = 0;
	*line_number = 0;
	*column_number = 0;
	*found_player = false;
}

bool	check_for_player(char current_char, bool *found_player)
{
	if (current_char == 'N' || current_char == 'S'
		|| current_char == 'E' || current_char == 'W')
	{
		if (*found_player)
		{
			printf("Multiple player start positions found. Invalid map.\n");
			return (false);
		}
		*found_player = true;
	}
	return (true);
}

void	update_player_info(t_structure_map *map_info,
	int line_number, int column_number, char player_direction)
{
	map_info->player_x = column_number * map_info->map_s + map_info->map_s / 2;
	map_info->player_y = line_number * map_info->map_s + map_info->map_s / 2;
	map_info->player_direction = player_direction;
	printf("Player found: x = %f, y = %f, direction = %c\n", map_info->player_x,
		map_info->player_y, map_info->player_direction);
}

void	update_position(char current_char,
	int *line_number, int *column_number)
{
	if (current_char == '\n')
	{
		(*line_number)++;
		*column_number = 0;
	}
	else
	{
		(*column_number)++;
	}
}

bool	check_for_multiple_players(bool found_player)
{
	if (found_player)
	{
		printf("Multiple player start positions found. Invalid map.\n");
		return (false);
	}
	return (true);
}
