/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_background.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:19:39 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 17:08:15 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_sky_ground(t_sky_ground_params *params)
{
	t_square_params	square_params;

	square_params.w = params->w;
	square_params.x = params->background_off_setx;
	square_params.y = params->start_height;
	square_params.xo = params->w->s_win.width + params->background_off_setx;
	square_params.yo = params->end_height;
	square_params.color = params->color;
	draw_square_raw(&square_params);
}

void	draw_background(t_structure_main *w)
{
	int					backgroundoffsetx;
	t_sky_ground_params	sky_params;
	t_sky_ground_params	ground_params;

	backgroundoffsetx = BOV;
	sky_params.w = w;
	sky_params.start_height = 0;
	sky_params.end_height = w->s_win.height / 2;
	sky_params.color = w->t->ceil_color;
	sky_params.background_off_setx = backgroundoffsetx;
	draw_sky_ground(&sky_params);
	ground_params.w = w;
	ground_params.start_height = w->s_win.height / 2;
	ground_params.end_height = w->s_win.height;
	ground_params.color = w->t->floor_color;
	ground_params.background_off_setx = backgroundoffsetx;
	draw_sky_ground(&ground_params);
}

void	draw_black_ground(t_ray_params *params, t_texture_params tparams)
{
	t_square_params	square_params;

	square_params.w = params->w;
	square_params.x = tparams.start_x;
	square_params.y = params->line_off;
	square_params.xo = square_params.x + 1;
	square_params.yo = params->line_off + params->line_h ;
	square_params.color = 0x000000;
	draw_square_raw(&square_params);
}
