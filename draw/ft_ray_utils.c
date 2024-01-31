/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:25:39 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/14 18:41:22 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_ra_vertical(t_ray_calc_params *params, float nTan, int tileSize)
{
	if (params->ra > P2 && params->ra < P3)
	{
		*params->rx = (((int)params->w->s_player.px / tileSize)
				* tileSize) - 0.0001;
		params->xo = -tileSize;
	}
	else if (params->ra < P2 || params->ra > P3)
	{
		*params->rx = (((int)params->w->s_player.px / tileSize)
				* tileSize) + tileSize;
		params->xo = tileSize;
	}
	else
	{
		*params->rx = params->w->s_player.px;
		*params->ry = params->w->s_player.py;
		params->dof = DOF;
		return ;
	}
	*params->ry = (params->w->s_player.px - *params->rx)
		* nTan + params->w->s_player.py;
	params->yo = -params->xo * nTan;
}

void	handle_ra_not_equal_pi(t_ray_calc_params *params,
			float atan, int tilesize)
{
	if (params->ra > PI)
	{
		*params->ry = (((int)params->w->s_player.py / tilesize)
				* tilesize) - 0.0001;
		params->yo = -tilesize;
	}
	else
	{
		*params->ry = (((int)params->w->s_player.py / tilesize)
				* tilesize) + tilesize;
		params->yo = tilesize;
	}
	*params->rx = (params->w->s_player.py - *params->ry)
		* atan + params->w->s_player.px;
	params->xo = -params->yo * atan;
}
