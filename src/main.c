/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:07 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/09 15:27:02 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	end_program(t_conf_file *conf_file, t_window_frame *gui)
{
	mlx_terminate(gui->window);
	// free_config_file_members(conf_file);
}

int	main(int argc, char **argv)
{
	t_window_frame gui;

	t_conf_file	config_file;

	init_gui(&gui);
	init_hooks(&gui);

	// if (!parse_config_file(argc, argv, &config_file))
	// 	return (config_file.error);

	mlx_image_to_window(gui.window, gui.frame, 0, 0);
	mlx_loop(gui.window);
	end_program(&config_file, &gui);
	return (0);
}
