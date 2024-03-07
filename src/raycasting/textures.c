/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:07:09 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/03/07 10:56:14 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tex*	fetch_fitting_texture(t_ray *ray, t_window_frame *gui)
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
}

static double	calc_exact_wall_hitpoint(t_ray *ray, t_window_frame *gui)
{
	double	exact_wall_hp;

	if (ray->hit_side_bin == 1)
		exact_wall_hp = abs(gui->player.player_pos_x +
						ray->perpendicular_wall_to_cp_distance * ray->ray_dir_x);
	else
		exact_wall_hp = abs(gui->player.player_pos_y +
						ray->perpendicular_wall_to_cp_distance * ray->ray_dir_y);
	return (exact_wall_hp - (int)exact_wall_hp);
}

static int32_t*	determine_wall_pixels(double exact_wall_hp, t_tex* tex, int wall_height)
{
	int32_t*	wall_pixels;
	int			index;
	double		step_size;

	index = 0;
	wall_pixels = malloc(sizeof(int32_t) * wall_height);
	if (!wall_pixels)
		return (NULL);
	// probably needs a case for mirroring
	step_size = tex->height / wall_height;
	while (index < wall_height && (int)position < tex->height)
	// { wall hp ?
		wall_pixels[index] = tex->pixels[];
	}

}

t_wall	calculate_textures(t_ray *ray, t_window_frame *gui)
{
	t_wall			wall_result;
	t_tex*			wall_tex;
	double			exact_wall_hp;
	int				wall_height;

	wall_tex = fetch_fitting_texture(ray, gui);
	if (!wall_tex->pixels)
		cleanup(gui);

	exact_wall_hp = calc_exact_wall_hitpoint(ray, gui);

	wall_result = calculate_wall_height(ray, gui->height);
	wall_height = wall_result.wall_top_pixel - wall_result.wall_bottom_pixel;
	wall_result.pixels = determine_wall_pixels(exact_wall_hp, wall_tex, wall_height);
	if (!wall_result.pixels)
		cleanup(gui);

}
