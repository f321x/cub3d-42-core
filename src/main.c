/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:07 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/20 13:32:10 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	end_program(t_conf_file *conf_file, t_window_frame *gui)
{
	mlx_terminate(gui->window);
	free_config_file_members(conf_file);
}

int	main(int argc, char **argv)
{
	t_window_frame gui;

	t_conf_file	config_file;

	init_gui(&gui);
	init_hooks(&gui);

	if (!parse_config_file(argc, argv, &config_file))
		return (config_file.error);
	print_test(config_file);
	print_map_plan(&config_file, config_file.map->map_plan);
	// print_map_plan(&config_file, config_file.map->map_copy);

	mlx_image_to_window(gui.window, gui.frame, 0, 0);

	t_player_pos	p;
	p.player_pos_x = (double)config_file.map->player_coord[0];
	p.player_pos_y = (double)config_file.map->player_coord[1];
	p.player_dir_x = -1.0;
	p.player_dir_y = 0;
	// vector is a bit longer than the camera plane, so the FOV will be smaller than 90° (more precisely, the FOV is
	// 2 * atan(0.66/1.0)=66°, which is perfect for a first person shooter game). Later on when rotating around with the
	// input keys, the values of dir and plane will be changed, but they'll always remain perpendicular and keep the same length.
	p.camera_plane_x = 0;
	p.camera_plane_y = 0.66;
	p.map_x = config_file.map->player_coord[0];
	p.map_y = config_file.map->player_coord[1];
	// printf("map_y: %d | map_x: %d\n", p.map_y, p.map_x);
	draw_image(&gui, *(config_file.map), p);
	new_frame(&gui);

	mlx_loop(gui.window);
	end_program(&config_file, &gui);
	free_config_file_members(&config_file);
	return (0);
}
