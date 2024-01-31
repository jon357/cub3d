/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:09:52 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 16:21:09 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_collision(t_structure_main *w, double future_x,
		double future_y, t_collision_params *coll_params)
{
	int		i;
	int		map_x;
	int		map_y;
	char	map_position;

	i = 0;
	while (i < DX_LENGTH)
	{
		map_x = (int)((future_x + coll_params->dx[i]) / w->s_map.map_s);
		map_y = (int)((future_y + coll_params->dy[i]) / w->s_map.map_s);
		map_position = w->s_map.map[map_y * w->s_map.map_x + map_x];
		if (map_position == '1' || map_position == '2')
			return (0);
		i++;
	}
	return (1);
}

int	can_move_to(t_structure_main *w, double future_x, double future_y)
{
	t_collision_params	coll_params;

	coll_params.dx[0] = 0;
	coll_params.dx[1] = 0;
	coll_params.dx[2] = -COLBUF;
	coll_params.dx[3] = COLBUF;
	coll_params.dx[4] = -COLBUF;
	coll_params.dx[5] = COLBUF;
	coll_params.dx[6] = -COLBUF;
	coll_params.dx[7] = COLBUF;
	coll_params.dy[0] = -COLBUF;
	coll_params.dy[1] = COLBUF;
	coll_params.dy[2] = 0;
	coll_params.dy[3] = 0;
	coll_params.dy[4] = -COLBUF;
	coll_params.dy[5] = -COLBUF;
	coll_params.dy[6] = COLBUF;
	coll_params.dy[7] = COLBUF;
	if (check_collision(w, future_x, future_y, &coll_params) == 0)
		return (0);
	return (1);
}
