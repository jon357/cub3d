/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3d_view_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:00:21 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 13:49:33 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_texture_coords(t_texture_params *tparams,
		t_draw_params *dparams)
{
	if (tparams->wall_dir == NORTH || tparams->wall_dir == SOUTH)
	{
		dparams->texturex = (int)(tparams->rx * dparams->texturewidth
				/ tparams->w->s_map.map_s) % dparams->texturewidth;
	}
	else if (tparams->wall_dir == WEST || tparams->wall_dir == EAST)
	{
		dparams->texturex = (int)(tparams->ry * dparams->texturewidth
				/ tparams->w->s_map.map_s) % dparams->texturewidth;
	}
	if (dparams->texturex >= dparams->texturewidth)
	{
		dparams->texturex = dparams->texturewidth - 1;
	}
}

static void	draw_texture_line(t_ray_params *rparams,
		t_texture_params *tparams, t_draw_params *dparams, int deca)
{
	int		y;
	int		color;
	float	perspectivefactor;

	y = rparams->line_off;
	dparams->i = 0;
	dparams->x = tparams->start_x;
	while (y < rparams->line_off + rparams->line_h)
	{
		perspectivefactor = (float)(y - rparams->line_off) / rparams->line_h;
		dparams->texture_y = perspectivefactor * dparams->textureheight;
		if (dparams->texture_y >= dparams->textureheight)
			dparams->texture_y = dparams->textureheight - 1;
		set_texture_coords(tparams, dparams);
		color = get_texture_color(tparams->w,
				tparams->wall_dir, dparams->texturex, y);
		dparams->a = tparams->line_off - deca / 2;
		dparams->b = tparams->line_h + (deca / 2);
		dparams->c = tparams->line_h;
		dparams->step = (dparams->b - dparams->a) / (double)(dparams->c - 1);
		put_pixel_img(tparams->w, dparams->x,
			(int)(dparams->a + dparams->i * dparams->step), color);
		dparams->i++;
		y++;
	}
}

void	draw_yolo(t_ray_params *rparams, t_texture_params *tparams, int deca)
{
	t_draw_params	dparams;

	dparams.texturewidth = tparams->w->s_img.texture_width;
	dparams.textureheight = tparams->w->s_img.texture_height;
	draw_texture_line(rparams, tparams, &dparams, deca);
}

void	init_line_params(t_line_params *lineparams, t_ray_params *rayParams)
{
	lineparams->w = rayParams->w;
	lineparams->x0 = (int)rayParams->w->s_player.px;
	lineparams->y0 = (int)rayParams->w->s_player.py;
	lineparams->x1 = (int)rayParams->rx;
	lineparams->y1 = (int)rayParams->ry;
	lineparams->color = rayParams->color;
}

void	init_texture_params(t_texture_params *textureparams,
	t_ray_params *rayParams)
{
	textureparams->w = rayParams->w;
	textureparams->line_off = rayParams->line_off;
	textureparams->line_h = rayParams->line_h;
	textureparams->wall_dir = rayParams->wall_dir;
	textureparams->rx = rayParams->rx + rayParams->background_off_setx;
	textureparams->ry = rayParams->ry;
	textureparams->dis_t = rayParams->dis_t;
}
