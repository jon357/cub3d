/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:17:56 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 16:15:56 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	adjust_player_angle(t_structure_main *w, int key)
{
	double	angle_adjustment;

	if (key != 65361 && key != 65363)
		return ;
	angle_adjustment = 4 * (PI / 180);
	if (key == 65361)
	{
		w->s_player.pa -= angle_adjustment;
		if (w->s_player.pa < 0)
			w->s_player.pa += 2 * PI;
	}
	else
	{
		w->s_player.pa += angle_adjustment;
		if (w->s_player.pa > 2 * PI)
			w->s_player.pa -= 2 * PI;
	}
	w->s_player.pdx = cos(w->s_player.pa) * 5;
	w->s_player.pdy = sin(w->s_player.pa) * 5;
}

void	handle_movement_keys(int key, t_structure_main *w)
{
	if (key == 119 || key == 100 || key == 115 || key == 97)
		move(key, w);
}

int	deal_key(int key, t_structure_main *w)
{
	if (key == 65307)
		kill_prog(w);
	else if (key == 65361 || key == 65363)
		adjust_player_angle(w, key);
	else if (key == 65362 || key == 65364 || key == 114 || key == 102)
	{
	}
	else if (key == 101)
	{
		if (w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)
				/ w->s_map.map_s) *w->s_map.map_x + (int)((w->s_player.px
				+ cos(w->s_player.pa) * 7) / w->s_map.map_s)] == '2')
			w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)
					/ w->s_map.map_s) *w->s_map.map_x + (int)((w->s_player.px
						+ cos(w->s_player.pa) * 7) / w->s_map.map_s)] = '3';
		else if (w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)
				/ w->s_map.map_s) *w->s_map.map_x + (int)((w->s_player.px
				+ cos(w->s_player.pa) * 7) / w->s_map.map_s)] == '3')
			w->s_map.map[(int)((w->s_player.py + sin(w->s_player.pa) * 7)
					/ w->s_map.map_s) *w->s_map.map_x + (int)((w->s_player.px
						+ cos(w->s_player.pa) * 7) / w->s_map.map_s)] = '2';
	}
	else
		handle_movement_keys(key, w);
	return (key);
}
