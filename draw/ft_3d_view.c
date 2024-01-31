/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3d_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:35:53 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 17:05:58 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	calculate_line_height(t_ray_params *rayparams)
{
	rayparams->line_h = (rayparams->tile_size * rayparams->max3d_height)
		/ rayparams->dis_t;
	if (rayparams->line_h > rayparams->max3d_height)
	{
		rayparams->line_h = rayparams->max3d_height;
	}
	rayparams->line_off = ((rayparams->max3d_height - rayparams->line_h) / 2);
}

static void	calculate_deca(t_ray_params *rayparams, float *olineh, int *deca)
{
	*olineh = (rayparams->w->s_map.map_s * rayparams->w->s_win.height)
		/ rayparams->dis_t;
	if (*olineh > rayparams->w->s_win.height)
	{
		*deca = *olineh - rayparams->w->s_win.height;
	}
	else
	{
		*deca = 0;
	}
}

static void	set_rayparams(t_ray_params *rayparams)
{
	rayparams->start3d_height = 0;
	rayparams->max3d_height = rayparams->w->s_win.height
		+ rayparams->start3d_height;
}

static void	set_texture_params(t_ray_params *rayparams,
		t_texture_params *textureparams)
{
	textureparams->start_x = rayparams->r * rayparams->raywidth
		+ rayparams->background_off_setx;
	textureparams->end_x = textureparams->start_x + rayparams->raywidth;
}

void	drawray(t_ray_params *rayparams)
{
	t_line_params		lineparams;
	t_texture_params	textureparams;
	float				olineh;
	int					deca;

	set_rayparams(rayparams);
	calculate_line_height(rayparams);
	rayparams->raywidth = rayparams->w->s_win.width / rayparams->num_rays;
	rayparams->background_off_setx = BOV;
	calculate_deca(rayparams, &olineh, &deca);
	set_texture_params(rayparams, &textureparams);
	init_texture_params(&textureparams, rayparams);
	init_line_params(&lineparams, rayparams);
	draw_line(&lineparams);
	draw_black_ground(rayparams, textureparams);
	if (deca != 0)
	{
		draw_yolo(rayparams, &textureparams, deca);
	}
	else
	{
		draw_texture(&textureparams);
	}
}
