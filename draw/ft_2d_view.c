/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:49:42 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 16:20:39 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	correctfisheye(float distance, float ra, float playerAngle)
{
	float	ca;

	ca = playerAngle - ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	return (distance * cos(ca));
}

void	init_base_params(t_base_params *params, t_structure_main *w)
{
	params->tilesize = w->s_map.map_s;
	params->numrays = NUMRAY;
	params->fo_v = FOVIEW * (PI / 180);
	params->d_r = params->fo_v / params->numrays;
	params->ra = w->s_player.pa - (params->fo_v / 2);
	draw_background(w);
}

void	calculate_ray(t_base_params *base, t_ray_state *state,
		t_ray_calc *calc, t_ray_params *rayparams)
{
	if (state->dis_h < state->dis_v)
	{
		rayparams->dis_t = state->dis_h;
		calc->color = 0xFF0000;
		rayparams->wall_dir = state->hwalldir;
		rayparams->rx = state->hx;
		rayparams->ry = state->hy;
	}
	else
	{
		rayparams->dis_t = state->dis_v;
		calc->color = 0x00FF00;
		rayparams->wall_dir = state->vwalldir;
		rayparams->rx = state->vx;
		rayparams->ry = state->vy;
	}
	rayparams->dis_t = correctfisheye(rayparams->dis_t,
			base->ra, calc->w->s_player.pa);
	rayparams->w = calc->w;
	rayparams->tile_size = base->tilesize;
	rayparams->r = calc->r;
	rayparams->num_rays = base->numrays;
	rayparams->color = calc->color;
}

void	drawrays2d(t_structure_main *w)
{
	t_drawrays2d_params	params;

	init_base_params(&params.base_params, w);
	params.ray_calc.w = w;
	params.ray_calc.r = 0;
	while (params.ray_calc.r++ < params.base_params.numrays)
	{
		params.base_params.ra = fmod(params.base_params.ra + 2 * PI, 2 * PI);
		params.hrayparams = (t_ray_calc_params){w, params.base_params.ra,
			&params.ray_state.dis_h, &params.ray_state.hx,
			&params.ray_state.hy, &params.ray_state.hwalldir};
		params.vrayparams = (t_ray_calc_params){w, params.base_params.ra,
			&params.ray_state.dis_v, &params.ray_state.vx,
			&params.ray_state.vy, &params.ray_state.vwalldir};
		calculatehorizontalray(&params.hrayparams);
		calculateverticalray(&params.vrayparams);
		calculate_ray(&params.base_params, &params.ray_state,
			&params.ray_calc, &params.rayparams);
		drawray(&params.rayparams);
		params.base_params.ra += params.base_params.d_r;
	}
}
