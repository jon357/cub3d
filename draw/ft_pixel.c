/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:54:04 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/14 17:54:40 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel_img(t_structure_main *w, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < w->s_win.width && y < w->s_win.height)
	{
		dst = w->s_img.addr + (y * w->s_img.line_len + x * (w->s_img.bpp / 8));
		*(unsigned int *)dst = color;
	}
	else
	{
	}
}

void	draw_square_raw(t_square_params *params)
{
	int	i;
	int	j;
	int	size_x;
	int	size_y;

	i = 0;
	size_x = abs(params->xo - params->x);
	size_y = abs(params->yo - params->y);
	while (i < size_y)
	{
		j = 0;
		while (j < size_x)
		{
			put_pixel_img(params->w, params->x + j,
				params->y + i, params->color);
			j++;
		}
		i++;
	}
}
