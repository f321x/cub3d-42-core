/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:07:09 by fbock             #+#    #+#             */
/*   Updated: 2024/03/18 12:15:03 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// returns the correct texture depending on which
// side of the wall has been hit by the ray
static t_tex	*fetch_fitting_texture(t_ray *ray, t_window_frame *gui)
{
	t_field	side;

	side = ray->hit_side_color;
	if (side == NORTH)
		return (&(gui->textures.north));
	else if (side == SOUTH)
		return (&(gui->textures.south));
	else if (side == WEST)
		return (&(gui->textures.west));
	else if (side == EAST)
		return (&(gui->textures.east));
	else
		cleanup(gui);
	return (NULL);
}

// Calculates the exact hit point on a wall where a ray intersects it
static double	calc_exact_wall_hitpoint(t_ray *ray, t_window_frame *gui)
{
	double	exact_wall_hp;

	if (ray->hit_side_bin == 1)
		exact_wall_hp = fabs(gui->player.player_pos_x
				+ ray->perpendicular_wall_to_cp_distance * ray->ray_dir_x);
	else
		exact_wall_hp = fabs(gui->player.player_pos_y
				+ ray->perpendicular_wall_to_cp_distance * ray->ray_dir_y);
	return (exact_wall_hp - (int)exact_wall_hp);
}

// returns the 32-bit array of integers for the colors of a single
// column of the wall (one t_wall element)
static int32_t	*determine_wall_pixels(double exact_wall_hp,
										t_tex *tex, int wall_height)
{
	int32_t		*wall_pixels;
	int			index;
	double		step_size;
	double		position;

	index = 0;
	wall_pixels = malloc(sizeof(int32_t) * wall_height);
	if (!wall_pixels)
		return (NULL);
	step_size = (double)tex->height / wall_height;
	position = 0;
	exact_wall_hp = (int)(exact_wall_hp * tex->width) % tex->width;
	while (index < wall_height)
	{
		wall_pixels[index++] = tex->pixels[(int)position * tex->width
			+ (int)exact_wall_hp];
		position += step_size;
	}
	return (wall_pixels);
}

// main texture calculation function, determines the correct
// texture, scales the texture to the wall size and determines the
// correct pixels to draw on the wall. returns t_wall which
// contains an array of 32-bit integers that represent the colors
// of the wall
t_wall	calculate_textures(t_ray *ray, t_window_frame *gui)
{
	t_wall			wall_result;
	t_tex			*wall_tex;
	double			exact_wall_hp;
	int				wall_height;

	wall_tex = fetch_fitting_texture(ray, gui);
	if (!wall_tex->pixels)
		cleanup(gui);
	exact_wall_hp = calc_exact_wall_hitpoint(ray, gui);
	wall_result = calculate_wall_height(ray, gui->height);
	wall_height = (wall_result.wall_top_pixel
			- wall_result.wall_bottom_pixel) + 1;
	wall_result.pixels = determine_wall_pixels(exact_wall_hp,
			wall_tex, wall_height);
	if (!wall_result.pixels)
		cleanup(gui);
	return (wall_result);
}
