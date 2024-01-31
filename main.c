/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:45:52 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 15:47:44 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	setup_and_load_map(int argc, char **argv,
		t_structure_main *w, t_texture *textures)
{
	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		exit_error(w);
		return (0);
	}
	if (!load_cub_file(argv[1], textures, &w->s_map))
	{
		printf("Failed to load the map or map is not closed. Exiting...\n");
		w->error = 1;
		exit_error(w);
		return (0);
	}
	if (w->s_map.map == NULL)
	{
		printf("Failed to load the map.\n");
		return (0);
	}
	return (1);
}

void	init_structure_main(t_structure_main *w)
{
	if (w == NULL)
	{
		return ;
	}
	w->t = (t_texture *)malloc(sizeof(t_texture));
	if (w->t != NULL)
	{
		ft_memset(w->t, 0, sizeof(t_texture));
	}
	ft_memset(&(w->s_win), 0, sizeof(t_structure_windows));
	ft_memset(&(w->s_img), 0, sizeof(t_structure_img));
	ft_memset(&(w->s_map), 0, sizeof(t_structure_map));
	ft_memset(&(w->s_player), 0, sizeof(t_structure_player));
	ft_memset(&(w->sprite), 0, sizeof(t_sprite));
	w->s_img.texture_width = 1280;
	w->s_img.texture_height = 720;
	w->error = 0;
}

int	main(int argc, char **argv)
{
	t_structure_main	w;
	t_global_struct		global_struct;

	init_structure_main(&w);
	global_struct.w = &w;
	global_struct.state.jkl = -1;
	global_struct.state.yui = 0;
	w.s_win.width = WIDTH;
	w.s_win.height = HEIGHT;
	if (!setup_and_load_map(argc, argv, &w, w.t))
		return (1);
	init_windows(&w);
	mlx_loop_hook(w.s_win.mlx, (void *)sleep_mouse, &global_struct);
	mlx_hook(w.s_win.win, 2, 1L << 0, deal_key, &w);
	mlx_hook(w.s_win.win, 17, 0, (void *)kill_prog, &w);
	mlx_loop(w.s_win.mlx);
	if (w.s_map.map)
	{
		free(w.s_map.map);
	}
	if (w.t)
	{
		free(w.t);
	}
	return (0);
}
