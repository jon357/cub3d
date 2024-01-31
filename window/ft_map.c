/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:19:01 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 15:47:34 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_map_line(t_structure_main *w, int y, int lineLength)
{
	int	x;
	int	index;
	int	color;

	x = 0;
	while (x < lineLength)
	{
		index = y * w->s_map.map_x + x;
		if (w->s_map.map[index] == '1')
			color = 0xFFFFFF;
		else if (w->s_map.map[index] == '0')
			color = 0x000000;
		else if (w->s_map.map[index] == '2')
			color = 0xFFFFFF;
		else if (w->s_map.map[index] == '3')
			color = 0x000000;
		else
			color = 0x000000;
		draw_square(w, x, y, color);
		x++;
	}
}

void	draw_map(t_structure_main *w)
{
	int	y;
	int	linelength;

	y = 0;
	if (!w->s_map.map)
	{
		printf("Erreur: La carte n'a pas été chargée correctement.\n");
		return ;
	}
	while (y < w->s_map.map_y)
	{
		linelength = 0;
		while (linelength < w->s_map.map_x
			&& w->s_map.map[y * w->s_map.map_x + linelength]
			!= '\n' && w->s_map.map[y * w->s_map.map_x + linelength] != '\0')
		{
			linelength++;
		}
		draw_map_line(w, y, linelength);
		y++;
	}
}
