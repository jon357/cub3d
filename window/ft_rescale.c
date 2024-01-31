/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rescale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 21:29:08 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/14 23:10:00 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_res_params(t_rescale_params *params, t_structure_main *w)
{
	if (!params || !w)
	{
		fprintf(stderr,
			"Erreur: paramètres invalides pour initialize_res_params.\n");
		return ;
	}
	params->res = malloc(sizeof(t_res_params));
	if (!params->res)
	{
		perror("Erreur d'allocation mémoire pour t_res_params");
		return ;
	}
	params->res->rescaled_img = mlx_new_image(w->s_win.mlx,
			params->new_width, params->new_height);
	if (!params->res->rescaled_img)
	{
		perror("Erreur lors de la création de la nouvelle image");
		return ;
	}
	params->res->original_data = mlx_get_data_addr(params->original_img,
			&(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	params->res->rescaled_data = mlx_get_data_addr(params->res->rescaled_img,
			&(w->s_img.bpp), &(w->s_img.line_len), &(w->s_img.endian));
	params->res->x_ratio = (float)params->original_width / params->new_width;
	params->res->y_ratio = (float)params->original_height / params->new_height;
}

void	copy_pixel_data(t_res_params *res)
{
	res->rescaled_data[res->pixel_pos_rescaled]
		= res->original_data[res->pixel_pos_original];
	res->rescaled_data[res->pixel_pos_rescaled + 1]
		= res->original_data[res->pixel_pos_original + 1];
	res->rescaled_data[res->pixel_pos_rescaled + 2]
		= res->original_data[res->pixel_pos_original + 2];
	res->rescaled_data[res->pixel_pos_rescaled + 3]
		= res->original_data[res->pixel_pos_original + 3];
}

int	validate_parameters(t_rescale_params *params, t_structure_main *w)
{
	if (!params || !w)
	{
		fprintf(stderr, "Erreur: paramètres invalides.\n");
		return (0);
	}
	return (1);
}

void	rescale_image(t_rescale_params *params, t_structure_main *w)
{
	int	x;
	int	y;

	if (!validate_parameters(params, w))
		return ;
	initialize_res_params(params, w);
	y = 0;
	while (y++ < params->new_height)
	{
		x = 0;
		while (x++ < params->new_width)
		{
			params->res->original_x = (int)(params->res->x_ratio * x);
			params->res->original_y = (int)(params->res->y_ratio * y);
			params->res->pixel_pos_rescaled = (y * params->new_width + x) * 4;
			params->res->pixel_pos_original = (params->res->original_y
					* params->original_width + params->res->original_x) * 4;
			copy_pixel_data(params->res);
		}
	}
	mlx_put_image_to_window(w->s_win.mlx, w->s_win.win,
		params->res->rescaled_img, params->px, params->py);
	mlx_destroy_image(w->s_win.mlx, params->res->rescaled_img);
	free(params->res);
}
