/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:47:40 by fbock             #+#    #+#             */
/*   Updated: 2024/03/18 12:03:42 by fbock            ###   ########.fr       */
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
	current_ray.ray_dir_x = p.player_dir_x + p.camera_plane_x
		* current_ray.camera_x_point;
	current_ray.ray_dir_y = p.player_dir_y + p.camera_plane_y
		* current_ray.camera_x_point;
	if (current_ray.ray_dir_x == 0)
		current_ray.ray_dir_x = 0.00001;
	if (current_ray.ray_dir_y == 0)
		current_ray.ray_dir_y = 0.00001;
	current_ray.delta_dist_x = fabs(1 / current_ray.ray_dir_x);
	current_ray.delta_dist_y = fabs(1 / current_ray.ray_dir_y);
	return (current_ray);
}

// calculates the direction of the initial step for the dda
// also calculates the initial distance from the ray point in the first
// square to the first side of a square.
void	calculate_initial_step_and_dist(t_ray *ray, t_player_pos *p)
{
	p->map_x = (int)p->player_pos_x;
	p->map_y = (int)p->player_pos_y;
	if (ray->ray_dir_x < 0)
	{
		ray->step_dir_x = -1;
		ray->init_dist_x = (p->player_pos_x - p->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_dir_x = 1;
		ray->init_dist_x = (p->map_x + 1.0 - p->player_pos_x)
			* ray->delta_dist_x ;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_dir_y = -1;
		ray->init_dist_y = (p->player_pos_y - p->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_dir_y = 1;
		ray->init_dist_y = (p->map_y + 1.0 - p->player_pos_y)
			* ray->delta_dist_y;
	}
}

// calculates the distance from the perpendicular ray between the camera plane
// and the hitpoint in the wall determined by the dda algorithm
void	dist_from_hitpt_to_camera_plane(t_ray *ray)
{
	if (ray->hit_side_bin == 0)
	{
		ray->perpendicular_wall_to_cp_distance = ray->init_dist_x
			- ray->delta_dist_x;
	}
	else
	{
		ray->perpendicular_wall_to_cp_distance = ray->init_dist_y
			- ray->delta_dist_y;
	}
}

// calculate the height of the wall to print to screen from the
// perpendicular distance btw wall hit point and camera plane
// (returned by dist_from_hitpt_to_camera_plane())
t_wall	calculate_wall_height(t_ray *current_ray, int frame_height)
{
	int		wall_height;
	double	dist;
	t_wall	wall;

	dist = current_ray->perpendicular_wall_to_cp_distance;
	if (dist <= 0.001)
		dist = 0.1;
	wall_height = (int)(frame_height / dist);
	wall.wall_bottom_pixel = (-wall_height / 2) + (frame_height / 2);
	if (wall.wall_bottom_pixel < 0)
		wall.wall_bottom_pixel = 0;
	wall.wall_top_pixel = (wall_height / 2) + (frame_height / 2);
	if (wall.wall_top_pixel >= frame_height)
		wall.wall_top_pixel = frame_height - 1;
	return (wall);
}

// main raycasting function that returns an array of walls containing the
// pixel colors for the wall and the height of the wall for drawing with
// the graphics library
t_wall	*raycast_whole_frame(t_player_pos player, t_map parsed_map,
								t_window_frame *gui)
{
	t_wall			*walls;
	t_ray			current_ray;
	int				current_column;
	t_player_pos	buffer;

	current_column = 0;
	walls = malloc(sizeof(t_wall) * gui->width);
	if (!walls)
		return (NULL);
	buffer = player;
	while (current_column < gui->width)
	{
		player = buffer;
		current_ray = calc_ray_direction(current_column, gui->width, player);
		calculate_initial_step_and_dist(&current_ray, &player);
		dda(&parsed_map, &current_ray, &player);
		dist_from_hitpt_to_camera_plane(&current_ray);
		walls[current_column] = calculate_textures(&current_ray, gui);
		current_column++;
	}
	return (walls);
}
