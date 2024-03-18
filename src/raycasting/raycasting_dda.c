/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:03:16 by fbock             #+#    #+#             */
/*   Updated: 2024/03/18 12:15:48 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	x_smaller_y(t_ray *ray, t_player_pos *pl)
{
	ray->init_dist_x += ray->delta_dist_x;
	pl->map_x += ray->step_dir_x;
	ray->hit_side_bin = 0;
	if (ray->step_dir_x > 0)
		ray->hit_side_color = SOUTH;
	else
		ray->hit_side_color = NORTH;
}

static void	x_bigger_y(t_ray *ray, t_player_pos *pl)
{
	ray->init_dist_y += ray->delta_dist_y;
	pl->map_y += ray->step_dir_y;
	ray->hit_side_bin = 1;
	if (ray->step_dir_y > 0)
		ray->hit_side_color = EAST;
	else
		ray->hit_side_color = WEST;
}

// dda algorithm to detect the next wall, iterating the distance
// from side to side of the map elements till it encounters a wall element
void	dda(t_map *map, t_ray *ray, t_player_pos *pl)
{
	bool	wall;

	wall = false;
	while (!wall)
	{
		if (ray->init_dist_x < ray->init_dist_y)
			x_smaller_y(ray, pl);
		else
			x_bigger_y(ray, pl);
		if (map->map_plan[pl->map_x][pl->map_y] == '1')
			wall = true;
	}
}
