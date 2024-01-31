/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 19:15:53 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 17:11:58 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_roomadslam_textures(t_structure_main *w, int *temp)
{
	w->s_img.roomadslam[0] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_02_delay-0.1s.xpm", temp, temp);
	w->s_img.roomadslam[1] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_03_delay-0.1s.xpm", temp, temp);
	w->s_img.roomadslam[2] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_04_delay-0.1s.xpm", temp, temp);
	w->s_img.roomadslam[3] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_05_delay-0.05s.xpm", temp, temp);
	w->s_img.roomadslam[4] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_06_delay-0.05s.xpm", temp, temp);
	w->s_img.roomadslam[5] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_07_delay-0.05s.xpm", temp, temp);
	w->s_img.roomadslam[6] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_08_delay-0.05s.xpm", temp, temp);
	w->s_img.roomadslam[7] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_09_delay-0.05s.xpm", temp, temp);
	w->s_img.roomadslam[8] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_10_delay-0.05s.xpm", temp, temp);
	w->s_img.roomadslam[9] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_11_delay-0.05s.xpm", temp, temp);
	w->s_img.roomadslam[10] = mlx_xpm_file_to_image(w->s_win.mlx,
			"sprite/roomadslam/frame_12_delay-0.05s.xpm", temp, temp);
}

void	load_textures(t_structure_main *w, int *temp)
{
	load_roomadslam_textures(w, temp);
}

void	init_buffer(t_structure_main *w)
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*buffer_addr;

	w->s_img.buffer = mlx_new_image(w->s_win.mlx, w->s_win.width,
			w->s_win.height);
	if (w->s_img.buffer == NULL)
	{
		fprintf(stderr, "Erreur : Échec de mlx_new_image pour le buffer.\n");
		return ;
	}
	buffer_addr = mlx_get_data_addr(w->s_img.buffer, &bpp, &size_line, &endian);
	if (buffer_addr == NULL)
		fprintf(stderr, "Erreur : Impossible d'obtenir l'adresse du buffer.\n");
	else
		printf("Buffer créé avec Largeur: %d, Hauteur: %d\n",
			w->s_win.width, w->s_win.height);
}

void	calculate_map_scale(t_structure_main *w)
{
	int	maps_x;
	int	maps_y;

	maps_x = w->s_win.width / (w->s_map.map_x * 4);
	maps_y = w->s_win.height / (w->s_map.map_y * 2);
	if (maps_x < maps_y)
		w->s_map.map_s = maps_x;
	else
		w->s_map.map_s = maps_y;
}

void	init_windows(t_structure_main *w)
{
	int	temp;

	init_player(w);
	init_mlx_and_window(w);
	load_textures(w, &temp);
	init_buffer(w);
	load_wall_textures(w);
	printf("Window Dimensions: Width = %d, Height = %d\n",
		w->s_win.width, w->s_win.height);
	printf("Texture Dimensions: Width = %d, Height = %d\n",
		w->s_img.texture_width, w->s_img.texture_height);
	gettimeofday(&(w->start_time), NULL);
	w->end_time = w->start_time;
	w->frame_count = 0;
	calculate_map_scale(w);
}
