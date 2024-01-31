/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_player_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:54:51 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 16:59:15 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	process_player_char(char current_char, t_player_info *player_info)
{
	if (is_player_char(current_char))
	{
		if (check_for_multiple_players(*(player_info->found_player)))
		{
			*(player_info->found_player) = true;
			update_player_info(player_info->map, player_info->line_number,
				player_info->column_number, current_char);
		}
		else
		{
			return (false);
		}
	}
	return (true);
}

bool	find_player(const char *map_content, int length, t_structure_map *map)
{
	int				i;
	bool			found_player;
	t_player_info	player_info;

	i = 0;
	initialize_variables(&i, &player_info.line_number,
		&player_info.column_number, &found_player);
	player_info.map = map;
	player_info.found_player = &found_player;
	while (i < length)
	{
		if (!process_player_char(map_content[i], &player_info))
			return (false);
		calculate_map(map);
		update_position(map_content[i],
			&player_info.line_number, &player_info.column_number);
		i++;
	}
	if (!found_player)
		return (false);
	return (true);
}
