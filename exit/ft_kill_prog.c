/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill_prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:12:26 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 17:12:26 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	destroy_images_and_window(t_structure_main *w)
{
	int	i;

	i = -1;
	if (w->s_win.mlx)
	{
		mlx_destroy_window(w->s_win.mlx, w->s_win.win);
		mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
		mlx_destroy_image(w->s_win.mlx, w->s_img.north_texture);
		mlx_destroy_image(w->s_win.mlx, w->s_img.south_texture);
		mlx_destroy_image(w->s_win.mlx, w->s_img.west_texture);
		mlx_destroy_image(w->s_win.mlx, w->s_img.east_texture);
		mlx_destroy_image(w->s_win.mlx, w->s_img.door_texture);
		while (++i <= 10)
			mlx_destroy_image(w->s_win.mlx, w->s_img.roomadslam[i]);
	}
}

static void	cleanup_and_exit(t_structure_main *w)
{
	if (w->s_map.map)
	{
		free(w->s_map.map);
		w->s_map.map = NULL;
	}
	if (w->t)
	{
		free(w->t->north);
		free(w->t->south);
		free(w->t->west);
		free(w->t->east);
		free(w->t);
	}
	if (w->s_win.mlx)
	{
		mlx_destroy_display(w->s_win.mlx);
		free(w->s_win.mlx);
	}
	exit(0);
}

int	*kill_prog(t_structure_main *w)
{
	destroy_images_and_window(w);
	cleanup_and_exit(w);
	return (0);
}
