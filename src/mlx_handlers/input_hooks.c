/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:16:25 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/06 16:31:19 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Function gets called by the resize hook when the window is resized.
** Will genereate a new frame with the new size which is passed as
** arg by the hook.
** Cleans the old frame and stores the new in the gui struct.
*/
void	resize_function(int32_t width, int32_t height, void *param)
{
	t_window_frame	*gui;

	gui = (t_window_frame *)param;
	gui->buffer = mlx_new_image(gui->window, width, height);
	if (!gui->buffer)
		cleanup(gui);

	// generate_next_cub3d_frame(gui, gui->buffer);  tbd

	if ((mlx_image_to_window(gui->window, gui->buffer, 0, 0)) < 0)
		cleanup(gui);
	mlx_delete_image(gui->window, gui->frame);
	gui->frame = gui->buffer;
	gui->buffer = NULL;
}

void	scrolling_handler(double xdelta, double ydelta, void *param)
{
	return ;
}

/*
** Gets called on every mouse movement and stores the current mouse
** position in the gui struct. If the mouse is outside of the window
** the middle of the screen will be stored in the gui struct on mouse
** movement.
*/
void	mouse_position_handler(double xpos, double ypos, void *param)
{
	t_window_frame	*gui;

	gui = (t_window_frame *)param;
	if (xpos > 0.0 && xpos < gui->frame->width)
		gui->mouse_x = xpos;
	else
	{
		gui->mouse_x = (gui->frame->width / 2);
		gui->mouse_y = (gui->frame->height / 2);
		return ;
	}
	if (ypos > 0.0 && ypos < gui->frame->height)
		gui->mouse_y = ypos;
	else
	{
		gui->mouse_x = (gui->frame->width / 2);
		gui->mouse_y = (gui->frame->height / 2);
		return ;
	}
}

/*
** Short hook handler for the keypresses which terminates the
** programm on press of the ESC key (256).
*/
void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_window_frame	*gui;

	gui = (t_window_frame *)param;
	if (keydata.key == 256)
	{
		mlx_delete_image(gui->window, gui->frame);
		mlx_terminate(gui->window);
		exit(EXIT_SUCCESS);
	}
}