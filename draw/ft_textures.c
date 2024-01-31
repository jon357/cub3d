/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:39:11 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:21 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_texture_line(t_texture_params *params, float y, int textureY)
{
	int	x;
	int	texturewidth;
	int	texturex;
	int	color;

	texturewidth = params->w->s_img.texture_width;
	x = params->start_x;
	while (x < params->end_x)
	{
		if (params->wall_dir == NORTH || params->wall_dir == SOUTH)
			texturex = (int)(params->rx * texturewidth
					/ params->w->s_map.map_s) % texturewidth;
		else
			texturex = (int)(params->ry * texturewidth
					/ params->w->s_map.map_s) % texturewidth;
		if (texturex >= texturewidth)
			texturex = texturewidth - 1;
		color = get_texture_color(params->w,
				params->wall_dir, texturex, textureY);
		put_pixel_img(params->w, x, y, color);
		x++;
	}
}

void	draw_texture(t_texture_params *params)
{
	int		textureheight;
	float	y;
	float	perspectivefactor;
	int		texturey;

	textureheight = params->w->s_img.texture_height;
	y = params->line_off;
	while (y < params->line_off + params->line_h)
	{
		perspectivefactor = (y - params->line_off) / params->line_h;
		texturey = perspectivefactor * textureheight;
		if (texturey >= textureheight)
			texturey = textureheight - 1;
		draw_texture_line(params, y, texturey);
		y++;
	}
}

void	*get_selected_texture(t_structure_main *w, t_WallDirection wallDir)
{
	void	*texture;

	texture = NULL;
	if (w->current_wall_type == '2')
	{
		return (w->s_img.door_texture);
	}
	else if (wallDir == NORTH)
		return (w->s_img.north_texture);
	else if (wallDir == SOUTH)
		return (w->s_img.south_texture);
	else if (wallDir == WEST)
		return (w->s_img.west_texture);
	else if (wallDir == EAST)
		return (w->s_img.east_texture);
	else
	{
		printf("Invalid wall direction.\n");
		exit_error(w);
		return (NULL);
	}
	if (texture == NULL)
		printf("get_selected_texture: selected texture is NULL\n");
	else
		printf("get_selected_texture: selected texture = %p\n", texture);
}

t_texture_data	get_texture_data(void *texture)
{
	t_texture_data	texture_data;

	texture_data.data = mlx_get_data_addr(texture, &texture_data.bpp,
			&texture_data.size_line, &texture_data.endian);
	return (texture_data);
}

int	get_texture_color(t_structure_main *w, t_WallDirection wallDir,
		int textureX, int textureY)
{
	void			*selected_texture;
	t_texture_data	texture_data;
	int				pixel_pos;

	selected_texture = get_selected_texture(w, wallDir);
	if (selected_texture == NULL)
	{
		fprintf(stderr, "No texture selected for color retrieval\n");
		return (0);
	}
	texture_data = get_texture_data(selected_texture);
	pixel_pos = (textureX + textureY * w->s_img.texture_width)
		* (texture_data.bpp / 8);
	return (*(int *)(texture_data.data + pixel_pos));
}
