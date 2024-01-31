/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refresh_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:50:24 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 17:04:53 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rescale_sprite(t_structure_main *w, t_state *state)
{
	t_rescale_params	params;

	params.original_img = w->s_img.roomadslam[state->jkl];
	params.original_width = 112;
	params.original_height = 112;
	params.new_width = w->s_map.map_s * 5;
	params.new_height = w->s_map.map_s * 5;
	params.px = w->s_player.px - w->s_map.map_s / 2 - 5;
	params.py = w->s_player.py - w->s_map.map_s / 2 - 5;
	rescale_image(&params, w);
}

void	refresh_window(t_structure_main *w, t_state *state)
{
	mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.width,
			w->s_win.height);
	w->s_img.addr = mlx_get_data_addr(w->s_img.buffer,
			&(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	draw_map(w);
	drawrays2d(w);
	mlx_put_image_to_window(w->s_win.mlx, w->s_win.win, w->s_img.buffer, 0, 0);
	rescale_sprite(w, state);
}

void	handle_mouse_movement(t_structure_main *w)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(w->s_win.mlx, w->s_win.win, &x, &y);
	if ((x > 0 && x < w->s_win.width) && (y > 0 && y < w->s_win.height))
	{
		if (x < w->s_win.width / 2 - 40)
			deal_key(65361, w);
		else if (x > w->s_win.width / 2 + 40)
			deal_key(65363, w);
	}
}

void	r_window(t_structure_main *w, t_state *state)
{
	refresh_window(w, state);
}

void	sleep_mouse(t_global_struct *global_struct)
{
	if (global_struct->state.yui < 10)
	{
		usleep(1000);
		global_struct->state.yui++;
	}
	else
	{
		global_struct->state.yui = 0;
		global_struct->state.jkl++;
		r_window(global_struct->w, &global_struct->state);
		handle_mouse_movement(global_struct->w);
	}
	if (global_struct->state.jkl == 10)
		global_struct->state.jkl = -1;
}
