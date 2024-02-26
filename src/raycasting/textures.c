/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:07:09 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/23 12:51:35 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"

// static mlx_texture_t	*fetch_fitting_texture(t_ray *ray, t_window_frame *gui)
// {
// 	t_field	side;

// 	side = ray->hit_side_color;
// 	if (side == NORTH)
// 		return (gui->textures.north);
// 	else if (side == SOUTH)
// 		return (gui->textures.north);
// 	else if (side == WEST)
// 		return (gui->textures.north);
// 	else if (side == EAST)
// 		return (gui->textures.north);
// 	else
// 		return (NULL);
// }

// static double	calc_exact_wall_hitpoint(t_ray *ray, t_window_frame *gui)
// {
// 	double	exact_wall_hp;

// 	if (ray->hit_side_bin == 1)
// 		exact_wall_hp = gui->player.player_pos_x +
// 						ray->perpendicular_wall_to_cp_distance * ray->ray_dir_x;
// 	else
// 		exact_wall_hp = gui->player.player_pos_y +
// 						ray->perpendicular_wall_to_cp_distance * ray->ray_dir_y;

// 	deduct floor

// 	return (exact_wall_hp);
// }

// void	calculate_textures(t_ray *ray, t_window_frame *gui)
// {
// 	mlx_texture_t*	wall_tex;
// 	double			exact_wall_hp;

// 	wall_tex = fetch_fitting_texture(ray, gui);
// 	if (!wall_tex)
// 	{
// 		printf("Wall side not found?\n");
// 		cleanup(gui);
// 	}
// 	exact_wall_hp = calc_exact_wall_hitpoint(ray, gui);
// }
