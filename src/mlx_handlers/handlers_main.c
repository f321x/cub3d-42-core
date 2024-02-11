/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:41:39 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/06 16:15:54 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_hooks(t_window_frame *gui)
{
	mlx_resize_hook(gui->window, resize_function, gui);
	mlx_scroll_hook(gui->window, scrolling_handler, gui);
	mlx_cursor_hook(gui->window, mouse_position_handler, gui);
	mlx_key_hook(gui->window, key_handler, gui);
}

void	init_gui(t_window_frame *gui)
{
	gui->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d | ***REMOVED*** & ***REMOVED***", true);
	if (!(gui->window))
		cleanup(gui);
	gui->frame = mlx_new_image(gui->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!(gui->frame))
	{
		mlx_terminate(gui->window);
		cleanup(gui);
	}
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
