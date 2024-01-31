/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_horizontal_ray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:53:47 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 17:12:54 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_ra_equal_pi(t_ray_calc_params *params)
{
	*params->rx = params->w->s_player.px;
	*params->ry = params->w->s_player.py;
	params->dof = DOF;
}

void	inithorizontalray(t_ray_calc_params *params)
{
	float	atan;
	int		tilesize;

	atan = -1 / tan(params->ra);
	tilesize = params->w->s_map.map_s;
	if (params->ra != PI)
		handle_ra_not_equal_pi(params, atan, tilesize);
	else
		handle_ra_equal_pi(params);
}

void	update_ray_params(t_ray_calc_params *params, int mx, int my)
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
					params->w->s_player.py, *params->rx, *params->ry);
			if (params->ra > PI)
				*params->wall_dir = NORTH;
			else
				*params->wall_dir = SOUTH;
			if (map_pos == '2')
				params->w->current_wall_type = map_pos;
			else
				params->w->current_wall_type = '1';
		}
	}
}

void	processhorizontalray(t_ray_calc_params *params)
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
		update_ray_params(params, mx, my);
		if (params->dof < DOF)
		{
			*params->rx += params->xo;
			*params->ry += params->yo;
			params->dof++;
		}
	}
}

void	calculatehorizontalray(t_ray_calc_params *params)
{
	params->xo = 0;
	params->yo = 0;
	params->dof = 0;
	inithorizontalray(params);
	processhorizontalray(params);
}
