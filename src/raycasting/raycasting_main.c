/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:47:40 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/14 15:23:59 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_ray {
	double	camera_x_point;
	double	ray_dir_x;
	double	ray_dir_y;
} t_ray;

typedef struct s_player_pos {
	double	player_pos_x;
	double	player_pos_y;
	double	player_dir_x;
	double	player_dir_y;
}	t_player_pos;

typedef struct s_ray_steps {
	double delta_dist_x;
	double delta_dist_y;
}	t_ray_steps;

// The ray starts at the position of the player (posX, posY).

// cameraX is the x-coordinate on the camera plane that the current x-coordinate of the screen represents, done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1. Out of this, the direction of the ray can be calculated as was explained earlier: as the sum of the direction vector, and a part of the plane vector. This has to be done both for the x and y coordinate of the vector (since adding two vectors is adding their x-coordinates, and adding their y-coordinates).

//     for(int x = 0; x < w; x++)
//     {
//       //calculate ray position and direction
//       double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
//       double rayDirX = dirX + planeX * cameraX;
//       double rayDirY = dirY + planeY * cameraX;


// Calculate each ray for a single player position and direction
// The ray dir is calculated for each x line of the frame
t_ray	calc_ray_direction(int current_x, int width, t_player_pos p)
{
	t_ray	current_ray;

	current_ray.camera_x_point = 2 * (double)current_x
								/ (double)width - 1;
	current_ray.ray_dir_x = p.player_pos_x + p.player_dir_x
							* current_ray.camera_x_point;
	current_ray.ray_dir_y = p.player_pos_y + p.player_dir_y
							* current_ray.camera_x_point;
	return (current_ray);
}

// draft, not final
t_ray	*calculate_rays(int frame_width, t_player_pos current_player_pos)
{
	int		current_x;
	t_ray	*frame_rays;

	frame_rays = malloc(sizeof(t_ray) * frame_width);
	if (!frame_rays)
		return (NULL);  // catch error later, tbd
	current_x = 0;
	while (current_x < frame_width)
		frame_rays[current_x] = calc_ray_direction(current_x,
								frame_width, current_player_pos);
	return (frame_rays);  // heap, has to be freed!, NULL check needed!
}

// calculates the distance for the ray from one square wall to
// another on x and y axis.
// we can use 1 instead of len of ray dir X/Y, because only the *ratio* between
// delta_dist_x and delta_dist_y matters for the DDA.
t_ray_steps	calc_ray_step_distances(double ray_dir_x, double ray_dir_y)
{
	t_ray_steps	ray_step_distance;

	ray_step_distance.delta_dist_x = fabs(1 / ray_dir_x);
	ray_step_distance.delta_dist_y = fabs(1 / ray_dir_y);
	return (ray_step_distance);
}
