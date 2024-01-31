/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:08:25 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 17:59:17 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_structure_main *w, int key)
{
	double	future_px;
	double	future_py;

	if (key == 119)
	{
		future_px = w->s_player.px + cos(w->s_player.pa) * w->s_map.map_s;
		future_py = w->s_player.py + sin(w->s_player.pa) * w->s_map.map_s;
		if (can_move_to(w, future_px, future_py))
		{
			w->s_player.px = future_px;
			w->s_player.py = future_py;
		}
	}
}

void	move_backward(t_structure_main *w, int key)
{
	double	future_px;
	double	future_py;

	if (key == 115)
	{
		future_px = w->s_player.px - cos(w->s_player.pa) * w->s_map.map_s;
		future_py = w->s_player.py - sin(w->s_player.pa) * w->s_map.map_s;
		if (can_move_to(w, future_px, future_py))
		{
			w->s_player.px = future_px;
			w->s_player.py = future_py;
		}
	}
}

void	move_right(t_structure_main *w, int key)
{
	double	future_px;
	double	future_py;

	if (key == 100)
	{
		future_px = w->s_player.px + cos(w->s_player.pa
				+ (PI / 2)) * w->s_map.map_s;
		future_py = w->s_player.py + sin(w->s_player.pa
				+ (PI / 2)) * w->s_map.map_s;
		if (can_move_to(w, future_px, future_py))
		{
			w->s_player.px = future_px;
			w->s_player.py = future_py;
		}
	}
}

void	move_left(t_structure_main *w, int key)
{
	double	future_px;
	double	future_py;

	if (key == 97)
	{
		future_px = w->s_player.px + cos(w->s_player.pa
				- (PI / 2)) * w->s_map.map_s;
		future_py = w->s_player.py + sin(w->s_player.pa
				- (PI / 2)) * w->s_map.map_s;
		if (can_move_to(w, future_px, future_py))
		{
			w->s_player.px = future_px;
			w->s_player.py = future_py;
		}
	}
}

void	move(int key, t_structure_main *w)
{
	move_forward(w, key);
	move_backward(w, key);
	move_right(w, key);
	move_left(w, key);
}
