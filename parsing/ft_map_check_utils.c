/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:44:27 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 13:57:02 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_boundaries(t_point p, t_map_check *map_check)
{
	return (p.x > 0 && p.x < map_check->max_width - 1
		&& p.y > 0 && p.y < map_check->height - 1);
}

int	is_space_surrounded_by_walls(t_map_check *map_check, t_point p)
{
	if (!check_boundaries(p, map_check))
		return (0);
	return (map_check->map[p.y * map_check->max_width + (p.x - 1)] == '1'
		&& map_check->map[p.y * map_check->max_width + (p.x + 1)] == '1'
		&& map_check->map[(p.y - 1) * map_check->max_width + p.x] == '1'
		&& map_check->map[(p.y + 1) * map_check->max_width + p.x] == '1');
}
