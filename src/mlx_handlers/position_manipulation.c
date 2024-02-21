/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_manipulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:27:52 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/21 10:13:17 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static double degree_to_rad(double degree)
// {
// 	return ((double)degree * (M_PI / 180.0));
// }

static void	rotation_calculation(double x, double y, double rotation_rad, double result[2])
{
	result[0] = x * cos(rotation_rad) - y * sin(rotation_rad);
	result[1] = x * sin(rotation_rad) + y * cos(rotation_rad);
}

void rotate(t_window_frame *gui, bool true_if_right)
{
	double			calc_result[2];
	double			rotation_rad;

	if (true_if_right)
		rotation_rad = ROTATION_SPEED_RAD;
	else
		rotation_rad = ROTATION_SPEED_RAD * (-1);
	rotation_calculation(gui->player.player_dir_x, gui->player.player_dir_y, rotation_rad, calc_result);
	gui->player.player_dir_x = calc_result[0];
	gui->player.player_dir_y = calc_result[1];
	rotation_calculation(gui->player.camera_plane_x, gui->player.camera_plane_y, rotation_rad, calc_result);
	gui->player.camera_plane_x = calc_result[0];
	gui->player.camera_plane_y = calc_result[1];
	draw_image(gui);
	new_frame(gui);
}
