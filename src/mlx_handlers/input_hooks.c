/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:16:25 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/21 16:32:11 by ***REMOVED***         ###   ########.fr       */
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
	draw_image(gui);
	new_frame(gui);
}

// void	scrolling_handler(double xdelta, double ydelta, void *param)
// {
// 	xdelta = 0;
// 	ydelta = 0;
// 	param = NULL;
// 	return ;
// }

/*
** Gets called on every mouse movement and stores the current mouse
** position in the gui struct. If the mouse is outside of the window
** the middle of the screen will be stored in the gui struct on mouse
** movement.
*/
// void	mouse_position_handler(double xpos, double ypos, void *param)
// {
// 	t_window_frame	*gui;

// 	gui = (t_window_frame *)param;
// 	if (xpos > 0.0 && xpos < gui->frame->width)
// 		gui->mouse_x = xpos;
// 	else
// 	{
// 		gui->mouse_x = (gui->frame->width / 2);
// 		gui->mouse_y = (gui->frame->height / 2);
// 		return ;
// 	}
// 	if (ypos > 0.0 && ypos < gui->frame->height)
// 		gui->mouse_y = ypos;
// 	else
// 	{
// 		gui->mouse_x = (gui->frame->width / 2);
// 		gui->mouse_y = (gui->frame->height / 2);
// 		return ;
// 	}
// }

void	move_forward(t_window_frame *gui, float  dx, float dy, float angle)
{
	if (gui->player.player_dir_y == 0 && gui->player.player_dir_x == 0)
		angle = 0;
	else
		angle = atan(gui->player.player_dir_y / gui->player.player_dir_x);
	dx = SPEED * cos(fabs(angle));
	dy = SPEED * sin(fabs(angle));
	if (gui->player.player_dir_y >= 0)
		gui->player.player_pos_y += dy;
	else
		gui->player.player_pos_y -= dy;
		
	if (gui->player.player_dir_x >= 0)
		gui->player.player_pos_x += dx;
	else
		gui->player.player_pos_x -= dx;
	draw_image(gui);
	new_frame(gui);
	printf("angle = %f\n", angle * 180 / M_PI);
	printf("dx= %f\n", dx);
	printf("dy= %f\n", dy);
	printf("gui->player.player_dir_y = %f\n", gui->player.player_dir_y);
	printf("gui->player.player_dir_x = %f\n", gui->player.player_dir_x);
	printf("gui->player.player_pos_y = %f\n", gui->player.player_pos_y);
	printf("gui->player.player_pos_x %f\n", gui->player.player_pos_x);
	printf("--------------------------------\n");
	return ;
}

void	move_backward(t_window_frame *gui, float dx, float dy, float angle)
{
	if (gui->player.player_dir_y == 0 && gui->player.player_dir_x == 0)
		angle = 0;
	else
		angle = atan(gui->player.player_dir_y / gui->player.player_dir_x);

	dx = SPEED * cos(fabs(angle));
	dy = SPEED * sin(fabs(angle));
	if (gui->player.player_dir_y >= 0)
		gui->player.player_pos_y -= dy;
	else
		gui->player.player_pos_y += dy;
		
	if (gui->player.player_dir_x >= 0)
		gui->player.player_pos_x -= dx;
	else
		gui->player.player_pos_x += dx;
	draw_image(gui);
	new_frame(gui);
	printf("angle = %f\n", angle * 180 / M_PI);
	printf("dx= %f\n", dx);
	printf("dy= %f\n", dy);
	printf("gui->player.player_pos_y = %f\n", gui->player.player_pos_y);
	printf("gui->player.player_pos_x %f\n", gui->player.player_pos_x);
	printf("--------------------------------\n");
}

void	move_right(t_window_frame *gui, float dx, float dy, float angle)
{
	if (gui->player.player_dir_y == 0 && gui->player.player_dir_x == 0)
		angle = 0;
	else
		angle = atan(gui->player.player_dir_y / gui->player.player_dir_x);
	printf("angle = %f\n", angle * 180 / M_PI);
	angle -= M_PI_2;
	dx = SPEED * fabs(cos(fabs(angle)));
	dy = SPEED * fabs(sin(fabs(angle)));
	if (gui->player.player_dir_y >= 0 && gui->player.player_dir_x < 0)
	{
		printf("NE\n");
		gui->player.player_pos_y += dy;
		gui->player.player_pos_x += dx;
	}
	else if (gui->player.player_dir_y >= 0 && gui->player.player_dir_x >= 0)
	{
		printf("SE\n");
		gui->player.player_pos_y -= dy;
		gui->player.player_pos_x += dx;
	}
	else if (gui->player.player_dir_y < 0 && gui->player.player_dir_x >= 0)
	{
		printf("SW\n");
		gui->player.player_pos_y -= dy;
		gui->player.player_pos_x -= dx;
	}
	else
	{
		printf("NW\n");
		gui->player.player_pos_y += dy;
		gui->player.player_pos_x -= dx;
	}
	draw_image(gui);
	new_frame(gui);
	printf("angle = %f\n", angle * 180 / M_PI);
	printf("dx= %f\n", dx);
	printf("dy= %f\n", dy);
	printf("gui->player.player_pos_y = %f\n", gui->player.player_pos_y);
	printf("gui->player.player_pos_x %f\n", gui->player.player_pos_x);
	printf("--------------------------------\n");
}

void	move_left(t_window_frame *gui, float dx, float dy, float angle)
{
	if (gui->player.player_dir_y == 0 && gui->player.player_dir_x == 0)
		angle = 0;
	else
		angle = atan(gui->player.player_dir_y / gui->player.player_dir_x);
	angle -= M_PI_2;
	dx = SPEED * fabs(cos(fabs(angle)));
	dy = SPEED * fabs(sin(fabs(angle)));
	if (gui->player.player_dir_y >= 0 && gui->player.player_dir_x < 0)
	{
		printf("NE\n");
		gui->player.player_pos_y -= dy;
		gui->player.player_pos_x -= dx;
	}
	else if (gui->player.player_dir_y >= 0 && gui->player.player_dir_x >= 0)
	{
		printf("SE\n");
		gui->player.player_pos_y += dy;
		gui->player.player_pos_x -= dx;
	}
	else if (gui->player.player_dir_y < 0 && gui->player.player_dir_x >= 0)
	{
		printf("SW\n");
		gui->player.player_pos_y += dy;
		gui->player.player_pos_x += dx;
	}
	else
	{
		printf("NW\n");
		gui->player.player_pos_y -= dy;
		gui->player.player_pos_x += dx;
	}
	draw_image(gui);
	new_frame(gui);
	printf("angle = %f\n", angle * 180 / M_PI);
	printf("dx= %f\n", dx);
	printf("dy= %f\n", dy);
	printf("gui->player.player_pos_y = %f\n", gui->player.player_pos_y);
	printf("gui->player.player_pos_x %f\n", gui->player.player_pos_x);
	printf("--------------------------------\n");
}

void handle_movement(mlx_key_data_t keydata, t_window_frame *gui)
{
	float	dx;
	float	dy;
	float	angle ;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_forward(gui, dx, dy, angle);
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_backward(gui, dx, dy, angle);
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_right(gui, dx, dy, angle);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_left(gui, dx, dy, angle);
	return ;
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
	if (keydata.key == 262)  // right
		rotate(gui, true);
	else if (keydata.key == 263)  // left
		rotate(gui, false);
	if (keydata.key == 256)
	{
		mlx_delete_image(gui->window, gui->frame);
		mlx_terminate(gui->window);
		exit(EXIT_SUCCESS);
	}
}
