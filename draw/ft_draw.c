/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:38:28 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 15:47:48 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_structure_main *w, int x, int y, int color)
{
	int	xo;
	int	yo;
	int	size;
	int	i;
	int	j;

	xo = x * w->s_map.map_s;
	yo = y * w->s_map.map_s;
	size = w->s_map.map_s;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_img(w, xo + j, yo + i, color);
			j++;
		}
		i++;
	}
}

static void	init_line_deltas(t_line_deltas *deltas)
{
	(deltas->dx) = abs(deltas->params->x1 - deltas->params->x0);
	(deltas->dy) = abs(deltas->params->y1 - deltas->params->y0);
	(deltas->err) = (deltas->dx) - (deltas->dy);
	if (deltas->params->x0 < deltas->params->x1)
		(deltas->sx) = 1;
	else
		(deltas->sx) = -1;
	if (deltas->params->y0 < deltas->params->y1)
		(deltas->sy) = 1;
	else
		(deltas->sy) = -1;
}

static void	trace_line(t_line_deltas *deltas)
{
	int	e2;

	while (deltas->params->x0 != deltas->params->x1
		|| deltas->params->y0 != deltas->params->y1)
	{
		put_pixel_img(deltas->params->w, deltas->params->x0,
			deltas->params->y0, deltas->params->color);
		e2 = 2 * (deltas->err);
		if (e2 > -((deltas->dy)))
		{
			(deltas->err) -= (deltas->dy);
			deltas->params->x0 += (deltas->sx);
		}
		if (e2 < (deltas->dx))
		{
			(deltas->err) += (deltas->dx);
			deltas->params->y0 += (deltas->sy);
		}
	}
}

void	draw_line(t_line_params *params)
{
	t_line_deltas	deltas;

	deltas.params = params;
	init_line_deltas(&deltas);
	trace_line(&deltas);
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
