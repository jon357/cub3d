/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:30:59 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 16:07:36 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_texture(t_structure_main *w, char *file_path, void **texture_ptr)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	*texture_ptr = mlx_xpm_file_to_image(w->s_win.mlx,
			file_path, &width, &height);
	if (!(*texture_ptr))
	{
		fprintf(stderr, "Failed to load texture: %s\n", file_path);
		exit_error(w);
	}
	w->s_img.texture_width = width;
	w->s_img.texture_height = height;
}

void	load_wall_textures(t_structure_main *w)
{
	load_texture(w, w->t->north, (void **)&w->s_img.north_texture);
	load_texture(w, w->t->south, (void **)&w->s_img.south_texture);
	load_texture(w, w->t->west, (void **)&w->s_img.west_texture);
	load_texture(w, w->t->east, (void **)&w->s_img.east_texture);
	load_texture(w, "textures/door_close.xpm", (void **)&w->s_img.door_texture);
}
