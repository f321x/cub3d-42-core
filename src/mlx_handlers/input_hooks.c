/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:16:25 by fbock             #+#    #+#             */
/*   Updated: 2024/02/06 16:27:09 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	init_hooks(t_window_frame *gui)
// {
// 	mlx_resize_hook(gui->window, resize_function, gui);
// 	mlx_scroll_hook(gui->window, scrolling_handler, gui);
// 	mlx_cursor_hook(gui->window, mouse_position_handler, gui);
// 	mlx_key_hook(gui->window, key_handler, gui);
// }

void	resize_function(int32_t width, int32_t height, void *param)
{

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
