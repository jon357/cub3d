/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vertical_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:03:21 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 17:22:00 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initverticalray(t_ray_calc_params *params)
{
	float	ntan;
	int		tilesize;

	ntan = -tan(params->ra);
	tilesize = params->w->s_map.map_s;
	handle_ra_vertical(params, ntan, tilesize);
}

void	update_vertical_ray_params(t_ray_calc_params *params, int mx, int my)
{
	int		mp;
	char	map_pos;

	mp = my * params->w->s_map.map_x + mx;
	if (mp >= 0 && mp < params->w->s_map.map_x * params->w->s_map.map_y)
	{
		map_pos = params->w->s_map.map[mp];
		if (map_pos == '1' || map_pos == '2')
		{
			params->dof = DOF;
			*params->dis_ray = dist(params->w->s_player.px,
					params->w->s_player.py,
					*params->rx, *params->ry);
			if (params->ra > P2 && params->ra < P3)
				*params->wall_dir = WEST;
			else
				*params->wall_dir = EAST;
			if (map_pos == '2')
				params->w->current_wall_type = map_pos;
			else
				params->w->current_wall_type = '1';
		}
	}
}

void	processverticalray(t_ray_calc_params *params)
{
	int	mx;
	int	my;
	int	tilesize;

	tilesize = params->w->s_map.map_s;
	*params->dis_ray = DISRAY;
	while (params->dof < DOF)
	{
		mx = (int)(*params->rx) / tilesize;
		my = (int)(*params->ry) / tilesize;
		update_vertical_ray_params(params, mx, my);
		if (params->dof < DOF)
		{
			*params->rx += params->xo;
			*params->ry += params->yo;
			params->dof++;
		}
	}
}

void	calculateverticalray(t_ray_calc_params *params)
{
	params->xo = 0;
	params->yo = 0;
	params->dof = 0;
	initverticalray(params);
	processverticalray(params);
}
