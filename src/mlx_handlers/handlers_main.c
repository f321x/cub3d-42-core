/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:41:39 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/22 10:09:30 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_hooks(t_window_frame *gui)
{
	mlx_resize_hook(gui->window, resize_function, gui);
	// mlx_scroll_hook(gui->window, scrolling_handler, gui);
	// mlx_cursor_hook(gui->window, mouse_position_handler, gui);
	mlx_key_hook(gui->window, key_handler, gui);
}

static void	load_textures(t_window_frame *gui)
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;

	north_path = gui->config_file.no_info;
	south_path = gui->config_file.so_info;
	east_path = gui->config_file.ea_info;
	west_path = gui->config_file.we_info;
	gui->textures.north = mlx_load_png(north_path);
	if (!gui->textures.north)
		cleanup(gui);
	gui->textures.south = mlx_load_png(south_path);
	if (!gui->textures.south)
		cleanup(gui);
	gui->textures.east = mlx_load_png(east_path);
	if (!gui->textures.east)
		cleanup(gui);
	gui->textures.west = mlx_load_png(west_path);
	if (!gui->textures.west)
		cleanup(gui);
}

void	init_gui(t_window_frame *gui)
{
	gui->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d | ***REMOVED*** & ***REMOVED***", true);
	if (!(gui->window))
		cleanup(gui);
	gui->height = WINDOW_HEIGHT;
	gui->width = WINDOW_WIDTH;
	// load_textures(gui);
	draw_image(gui);
	if (!(gui->buffer))
		cleanup(gui);
	if ((mlx_image_to_window(gui->window, gui->buffer, 0, 0)) < 0)
		cleanup(gui);
	gui->frame = gui->buffer;
	gui->buffer = NULL;
}

void	cleanup(t_window_frame *gui)
{
	if (gui->frame)
		mlx_delete_image(gui->window, gui->frame);
	if (gui->buffer)
		mlx_delete_image(gui->window, gui->buffer);
	if (gui->window)
		mlx_terminate(gui->window);
	exit(EXIT_FAILURE);
}
