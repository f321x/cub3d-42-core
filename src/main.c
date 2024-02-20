/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:07 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/20 15:39:05 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	end_program(t_conf_file *conf_file, t_window_frame *gui)
{
	mlx_terminate(gui->window);
	free_config_file_members(conf_file);
}

static void	init_player(t_window_frame *gui)
{
	t_player_pos *p;

	p = &(gui->player);
	p->player_pos_x = (double)gui->config_file.map->player_coord[0];
	p->player_pos_y = (double)gui->config_file.map->player_coord[1];
	p->player_dir_x = -1.0;
	p->player_dir_y = 0;

	p->camera_plane_x = 0;
	p->camera_plane_y = 0.66;
	p->map_x = gui->config_file.map->player_coord[0];
	p->map_y = gui->config_file.map->player_coord[1];
}

int	main(int argc, char **argv)
{
	t_window_frame gui;

	if (!parse_config_file(argc, argv, &(gui.config_file)))
		return (gui.config_file.error);
	print_test(gui.config_file);
	print_map_plan(&(gui.config_file), gui.config_file.map->map_plan);
	// print_map_plan(&config_file, config_file.map->map_copy);

	init_player(&gui);

	init_gui(&gui);
	init_hooks(&gui);
	mlx_loop(gui.window);
	end_program(&(gui.config_file), &gui);
	free_config_file_members(&(gui.config_file));
	return (0);
}
