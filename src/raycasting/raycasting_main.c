/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:47:40 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/19 12:10:11 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calculate each ray for a single player position and direction
// The ray dir is calculated for each x line of the frame
// calculates the distance for the ray from one square side to
// another on x and y axis.
// we can use 1 instead of len of ray dir X/Y, because only the *ratio* between
// delta_dist_x and delta_dist_y matters for the DDA.
t_ray	calc_ray_direction(int current_x, int width, t_player_pos p)
{
	t_ray	current_ray;

	current_ray.camera_x_point = 2 * (double)current_x
								/ (double)width - 1;
	current_ray.ray_dir_x = p.player_pos_x + p.player_dir_x
							* current_ray.camera_x_point;
	current_ray.ray_dir_y = p.player_pos_y + p.player_dir_y
							* current_ray.camera_x_point;
	current_ray.delta_dist_x = fabs(1 / current_ray.ray_dir_x);
	current_ray.delta_dist_y = fabs(1 / current_ray.ray_dir_y);
	return (current_ray);
}

// calculates the direction of the initial step for the dda
// also calculates the initial distance from the ray point in the first
// square to the first side of a square.
void	calculate_initial_step_and_dist(t_ray *ray, t_player_pos *p)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_dir_x = -1;
		ray->init_dist_x = (p->player_pos_x - p->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_dir_x = 1;
		ray->init_dist_x = (p->map_x + 1.0 - p->player_pos_x) * ray->delta_dist_x ;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_dir_y = -1;
		ray->init_dist_y = (p->player_pos_y - p->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_dir_y = 1;
		ray->init_dist_y = (p->map_y + 1.0 - p->player_pos_y) * ray->delta_dist_y;
	}
}

void	dda(t_map *map, t_ray *ray, t_player_pos *pl)
{
	bool	wall;

	wall = false;
	while (!wall)
	{
		if (ray->init_dist_x < ray->init_dist_y)
		{
			ray->init_dist_x += pl->delta_dist_x;
			pl->map_x += ray->step_dir_x;
			ray->hit_side = 0;  // assign east west if step_dir_x > 0
			if (ray->step_dir_x > 0)
				ray->hit_side_color = EAST  // dir not checked, check later.
			else
				ray->hit_side_color = WEST  // dir not checked, check later.
		}
		else
		{
			ray->init_dist_y += pl->delta_dist_y;
			pl->map_y += ray->step_dir_y;
			ray->hit_side = 1;  // assign south or north if step_dir_y > 0
			if (ray->step_dir_y > 0)
				ray->hit_side_color = SOUTH // dir not checked, check later.
			else
				ray->hit_side_color = NORTH  // dir not checked, check later.
		}
		if (map->map_plan[pl->map_x][pl->map_y] == WALL)  // is this the correct map?
			wall = true;
	}
}

// calculates the distance from the perpendicular ray between the camera plane
// and the hitpoint in the wall determined by the dda algorithm
void	dist_from_hitpt_to_camera_plane(t_ray *ray,	t_player_pos *pl)
{
	if (ray->hit_side == 0)
	{
		ray->perpendicular_wall_to_cp_distance = ray->init_dist_x
											- pl->delta_dist_x;
	}
	else
	{
		ray->perpendicular_wall_to_cp_distance = ray->init_dist_y
											- pl->delta_dist_y;
	}
}

// calculate the height of the wall to print to screen from the
// perpendicular distance btw wall hit point and camera plane
// (returned by dist_from_hitpt_to_camera_plane())
t_wall	calculate_wall_height(t_ray *current_ray, int frame_height)
{
	int		wall_height;
	double	dist;
	t_wall 	wall;

	dist = current_ray->perpendicular_wall_to_cp_distance;
	wall_height = (int)(frame_height / dist);
	wall.wall_bottom_pixel = (-wall_height / 2) + (frame_height / 2);
	if (wall.wall_bottom_pixel < 0)
		wall.wall_bottom_pixel = 0;
	wall.wall_top_pixel = (wall_height / 2) + (frame_height / 2);
	if (wall.wall_top_pixel >= frame_height)
		wall.wall_top_pixel = frame_height - 1;
	return (wall);
}

t_walls	*raycast_whole_frame(int frame_width, int frame_height, t_player_pos player, t_map parsed_map)
{
	t_wall		*walls;
	t_ray		current_ray;
	int			current_column;

	current_column = 0;
	walls = malloc(sizeof(t_wall) * frame_width);
	if (!walls)
		return (NULL);
	while (current_column < frame_width)
	{
		current_ray = calc_ray_direction(current_column, frame_width, player);
		calculate_initial_step_and_dist(&current_ray, &player);
		dda(&parsed_map, &current_ray, &player);
		dist_from_hitpt_to_camera_plane(&current_ray, &player);
		walls[current_column] = calculate_wall_height(&current_ray, frame_height);
		walls[current_column].direction = current_ray->hit_side_color;
		current_column++;
	}
	return (walls);
}

// tbd:
// adding correct side (N,E,S,W)
// textures ?
// collision detection
// moving -> changing coordinates
