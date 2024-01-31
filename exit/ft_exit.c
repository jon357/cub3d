/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:06:24 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 17:12:14 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_sub_exit_error(t_structure_main *w)
{
	if (w->s_win.mlx)
		mlx_destroy_window(w->s_win.mlx, w->s_win.win);
	if (w->s_img.buffer)
		mlx_destroy_image(w->s_win.mlx, w->s_img.buffer);
	if (w->s_img.north_texture)
		mlx_destroy_image(w->s_win.mlx, w->s_img.north_texture);
	if (w->s_img.south_texture)
		mlx_destroy_image(w->s_win.mlx, w->s_img.south_texture);
	if (w->s_img.west_texture)
		mlx_destroy_image(w->s_win.mlx, w->s_img.west_texture);
	if (w->s_img.east_texture)
		mlx_destroy_image(w->s_win.mlx, w->s_img.east_texture);
	if (w->s_img.door_texture)
		mlx_destroy_image(w->s_win.mlx, w->s_img.door_texture);
	if (w->s_map.map && (w->error != 1))
		free(w->s_map.map);
}

void	exit_error(t_structure_main *w)
{
	int	i;

	ft_sub_exit_error(w);
	i = -1;
	while (++i <= 10)
	{
		if (w->s_img.roomadslam[i])
			mlx_destroy_image(w->s_win.mlx, w->s_img.roomadslam[i]);
	}
	if (w->t->north)
		free(w->t->north);
	if (w->t->south)
		free(w->t->south);
	if (w->t->west)
		free(w->t->west);
	if (w->t->east)
		free(w->t->east);
	if (w->t)
		free(w->t);
	if (w->s_win.mlx)
	{
		mlx_destroy_display(w->s_win.mlx);
		free(w->s_win.mlx);
	}
	exit(1);
}
