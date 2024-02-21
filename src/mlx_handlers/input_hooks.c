/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:16:25 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/21 09:56:56 by ***REMOVED***         ###   ########.fr       */
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
	gui->width = width;
	gui->height = height;
	// generate_next_cub3d_frame(gui, gui->buffer);  tbd

	if ((mlx_image_to_window(gui->window, gui->buffer, 0, 0)) < 0)
		cleanup(gui);
	mlx_delete_image(gui->window, gui->frame);
	gui->frame = gui->buffer;
	gui->buffer = NULL;
}

void	scrolling_handler(double xdelta, double ydelta, void *param)
{
	xdelta = 0;
	ydelta = 0;
	param = NULL;
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

void handle_movement(mlx_key_data_t keydata, t_window_frame *gui)
{
	int		speed;
	float	dx;
	float	dy;

	speed = 1;
	double degree ;
	if (keydata.key == MLX_KEY_W)
	{
		if (gui->player.player_dir_y == 0 && gui->player.player_dir_x == 0)
		degree = 0;
		else
			degree = atan(gui->player.player_dir_y / gui->player.player_dir_x);

		dx = speed * cos(degree);
		dy = speed * sin(degree);

		// int player_new_y = gui->player.player_pos_y += dy;
		// int player_new_x = gui->player.player_pos_x += dx;
		// if (player_new_y < 0 || player_new_y > gui->config_file.map->rows_num
		// 	|| player_new_x < 0 || player_new_x > gui->config_file.map->max_columns_num)
		// 	return;
		gui->player.player_pos_y += dy;
		gui->player.player_pos_x += dx;
		draw_image(gui);
		new_frame(gui);
		printf("degree = %f\n", degree * 180 / M_PI);
		printf("dx= %f\n", dx);
		printf("dy= %f\n", dy);
		printf("gui->player.player_pos_y = %f\n", gui->player.player_pos_y);
		printf("gui->player.player_pos_x %f\n", gui->player.player_pos_x);
		printf("--------------------------------\n");
	}
	else if (keydata.key == MLX_KEY_S)
	{
		if (gui->player.player_dir_y == 0 && gui->player.player_dir_x == 0)
		degree = 0;
		else
			degree = atan(gui->player.player_dir_y / gui->player.player_dir_x);

		dx = speed * cos(degree);
		dy = speed * sin(degree);

		// int player_new_y = gui->player.player_pos_y += dy;
		// int player_new_x = gui->player.player_pos_x += dx;
		// if (player_new_y < 0 || player_new_y > gui->config_file.map->rows_num
		// 	|| player_new_x < 0 || player_new_x > gui->config_file.map->max_columns_num)
		// 	return;

		gui->player.player_pos_y -= dy;
		gui->player.player_pos_x -= dx;
		draw_image(gui);
		new_frame(gui);
		printf("degree = %f\n", degree * 180 / M_PI);
		printf("dx= %f\n", dx);
		printf("dy= %f\n", dy);
		printf("gui->player.player_pos_y = %f\n", gui->player.player_pos_y);
		printf("gui->player.player_pos_x %f\n", gui->player.player_pos_x);
		printf("--------------------------------\n");
	}
	else if (keydata.key == MLX_KEY_D)
	{
		if (gui->player.player_dir_y == 0 && gui->player.player_dir_x == 0)
		degree = 0;
		else
			degree = atan(gui->player.player_dir_y / gui->player.player_dir_x);
		printf("degree = %f\n", degree * 180 / M_PI);
		degree -= M_PI_2;
		dx = speed * cos(degree);
		dy = speed * sin(degree);

		// int player_new_y = gui->player.player_pos_y += dy;
		// int player_new_x = gui->player.player_pos_x += dx;
		// if (player_new_y < 0 || player_new_y > gui->config_file.map->rows_num
		// 	|| player_new_x < 0 || player_new_x > gui->config_file.map->max_columns_num)
		// 	return;

		gui->player.player_pos_y -= dy;
		gui->player.player_pos_x -= dx;
		draw_image(gui);
		new_frame(gui);
		printf("degree = %f\n", degree * 180 / M_PI);
		printf("dx= %f\n", dx);
		printf("dy= %f\n", dy);
		printf("gui->player.player_pos_y = %f\n", gui->player.player_pos_y);
		printf("gui->player.player_pos_x %f\n", gui->player.player_pos_x);
		printf("--------------------------------\n");
	}
	else if (keydata.key == MLX_KEY_A)
	{
		if (gui->player.player_dir_y == 0 && gui->player.player_dir_x == 0)
		degree = 0;
		else
			degree = atan(gui->player.player_dir_y / gui->player.player_dir_x);
		degree -= M_PI_2;
		dx = speed * cos(degree);
		dy = speed * sin(degree);

		// int player_new_y = gui->player.player_pos_y += dy;
		// int player_new_x = gui->player.player_pos_x += dx;
		// if (player_new_y < 0 || player_new_y > gui->config_file.map->rows_num
		// 	|| player_new_x < 0 || player_new_x > gui->config_file.map->max_columns_num)
		// 	return;

		gui->player.player_pos_y += dy;
		gui->player.player_pos_x += dx;
		draw_image(gui);
		new_frame(gui);
		printf("degree = %f\n", degree * 180 / M_PI);
		printf("dx= %f\n", dx);
		printf("dy= %f\n", dy);
		printf("gui->player.player_pos_y = %f\n", gui->player.player_pos_y);
		printf("gui->player.player_pos_x %f\n", gui->player.player_pos_x);
		printf("--------------------------------\n");
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
	// right: 262
	// left: 263
	// w: 87
	// a: 65
	// s: 83
	// d: 68
	handle_movement(keydata, gui);
	if (keydata.key == 256)
	{
		mlx_delete_image(gui->window, gui->frame);
		mlx_terminate(gui->window);
		exit(EXIT_SUCCESS);
	}
}
