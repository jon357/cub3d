/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:49:45 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 13:57:02 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	flood_fill_and_check(t_map_check *map_check,
		char *visitedMap, t_point p, char replacement)
{
	if (p.x < 0 || p.x >= map_check->max_width
		|| p.y < 0 || p.y >= map_check->height)
		return (0);
	if (visitedMap[p.y * map_check->max_width + p.x] == 1
		|| map_check->map[p.y * map_check->max_width + p.x] == '1')
		return (1);
	if (map_check->map[p.y * map_check->max_width + p.x] == ' '
		&& !is_space_surrounded_by_walls(map_check, p))
		return (0);
	visitedMap[p.y * map_check->max_width + p.x] = 1;
	map_check->map[p.y * map_check->max_width + p.x] = replacement;
	return (flood_fill_and_check(map_check, visitedMap,
			(t_point){p.x + 1, p.y}, replacement)
		&& flood_fill_and_check(map_check, visitedMap,
		(t_point){p.x - 1, p.y}, replacement)
		&& flood_fill_and_check(map_check, visitedMap,
		(t_point){p.x, p.y + 1}, replacement)
		&& flood_fill_and_check(map_check, visitedMap,
		(t_point){p.x, p.y - 1}, replacement));
}

static int	find_start_point(t_map_check *map_check, t_point *startPoint)
{
	int	y;
	int	x;

	y = 0;
	while (y < map_check->height)
	{
		x = 0;
		while (x < map_check->max_width)
		{
			if ((map_check->map[y * map_check->max_width + x] == '0'
					|| map_check->map[y * map_check->max_width + x] == '2')
				&& !is_space_surrounded_by_walls(map_check, (t_point){x, y}))
			{
				startPoint->x = x;
				startPoint->y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	initialize_maps(char **copy_map, char **visited_map,
	int maxWidth, int height)
{
	*copy_map = malloc(maxWidth * height);
	*visited_map = ft_calloc(maxWidth * height, sizeof(char));
	if (!(*copy_map) || !(*visited_map))
	{
		free(*copy_map);
		free(*visited_map);
		printf("Erreur d'allocation mémoire.\n");
		return (0);
	}
	return (1);
}

static void	cleanup_and_print_error(char *visited_map, char *copy_map)
{
	free(visited_map);
	free(copy_map);
	printf("Aucun point de départ valide trouvé.\n");
}

int	is_map_closed(char *map, int maxWidth, int height)
{
	char		*copy_map;
	char		*visited_map;
	t_map_check	map_check;
	t_point		start_point;
	int			is_closed;

	map_check.max_width = maxWidth;
	map_check.height = height;
	if (!initialize_maps(&copy_map, &visited_map, maxWidth, height))
		return (0);
	ft_memcpy(copy_map, map, maxWidth * height);
	map_check.map = copy_map;
	if (!find_start_point(&map_check, &start_point))
	{
		cleanup_and_print_error(visited_map, copy_map);
		return (1);
	}
	is_closed = flood_fill_and_check(&map_check, visited_map, start_point, '3');
	free(visited_map);
	free(copy_map);
	return (is_closed);
}
