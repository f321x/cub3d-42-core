/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:47:40 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/15 13:02:04 by ***REMOVED***            ###   ########.fr       */
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
	int		map_x;
	int		map_y;
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

// calculates the distance for the ray from one square side to
// another on x and y axis.
// we can use 1 instead of len of ray dir X/Y, because only the *ratio* between
// delta_dist_x and delta_dist_y matters for the DDA.
t_ray_steps	calc_ray_step_distances(t_ray ray)
{
	t_ray_steps	ray_step_distance;

	ray_step_distance.delta_dist_x = fabs(1 / ray_dir_x);
	ray_step_distance.delta_dist_y = fabs(1 / ray_dir_y);
	return (ray_step_distance);
}

// the doubles are the distance from the point to the first side of a square
// the ints are the direction of the first step
typedef struct s_init_step {
	double	init_dist_x;
	double	init_dist_y;
	int		step_dir_x;
	int		step_dir_y;
}	t_init_step;

// calculates the direction of the initial step for the dda
// also calculates the initial distance from the ray point in the first
// square to the first side of a square.
t_init_step	calculate_initial_step_and_dist(t_ray ray, t_ray_steps steps,
											t_player_pos p)
{
	t_init_step	init_dda_step;

	if (ray.ray_dir_x < 0)
	{
		init_dda_step.step_dir_x = -1;
		init_dda_step.init_dist_x = (p.player_pos_x - p.map_x) * ray.delta_dist_x;
	}
	else
	{
		init_dda_step.step_dir_x = 1;
		init_dda_step.init_dist_x = (p.map_x + 1.0 - p.player_pos_x) * ray.delta_dist_x ;
	}
	if (ray.ray_dir_y < 0)
	{
		init_dda_step.step_dir_y = -1;
		init_dda_step.init_dist_y = (p.player_pos_y - p.map_y) * ray.delta_dist_y;
	}
	else
	{
		init_dda_step.step_dir_y = 1;
		init_dda_step.init_dist_y = (p.map_y + 1.0 - p.player_pos_y) * ray.delta_dist_y;
	}
	return (init_dda_step);
}

void	dda(t_map map, t_init_step step, t_player_pos pl)
{
	bool	wall;
	int		side;

	wall = false;
	while (!wall)
	{
		if (step.init_dist_x < step.init_dist_y)
		{
			step.init_dist_x += pl.delta_dist_x;
			pl.map_x += step.step_dir_x;
			side = 0;  // assign east west if step_dir_x > 0
		}
		else
		{
			step.init_dist_y += pl.delta_dist_y;
			pl.map_y += step.step_dir_y;
			side = 1;  // assign south or north if step_dir_y > 0
		}
		if (map.map_plan[pl.map_x][pl.map_y] == WALL)  // is this the correct map?
			wall = true;
	}
	// return something useful
	return
}

// calculates the distance from the perpendicular ray between the camera plane
// and the hitpoint in the wall determined by the dda algorithm
double	dist_from_hitpt_to_camera_plane(int	side_hit, t_init_step dda_calc_distance,
										t_player_pos pl)
{
	double	perpendicular_wall_to_cp_distance;

	if (side_hit == 0)
	{
		perpendicular_wall_to_cp_distance = dda_calc_distance.init_dist_x
											- pl.delta_dist_x;
	}
	else
	{
		perpendicular_wall_to_cp_distance = dda_calc_distance.init_dist_y
											- pl.delta_dist_y;
	}
	return (perpendicular_wall_to_cp_distance);
}

typedef struct s_wall {
	int	wall_top_pixel;
	int	wall_bottom_pixel;
	int	direction;
}	t_wall;

// calculate the height of the wall to print to screen from the
// perpendicular distance btw wall hit point and camera plane
// (returned by dist_from_hitpt_to_camera_plane())
t_wall	calculate_wall_height(double dist, int frame_height)
{
	int		wall_height;
	t_wall 	wall;

	wall_height = (int)(frame_height / dist);
	wall.wall_bottom_pixel = (-wall_height / 2) + (frame_height / 2);
	if (wall.wall_bottom_pixel < 0)
		wall.wall_bottom_pixel = 0;
	wall.wall_top_pixel = (wall_height / 2) + (frame_height / 2);
	if (wall.wall_top_pixel >= frame_height)
		wall.wall_top_pixel = frame_height - 1;
	return (wall);
}

void	raycast_frame()
{
	combine everything and decide on variables/parameters to pass
}

