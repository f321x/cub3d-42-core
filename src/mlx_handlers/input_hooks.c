/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:16:25 by fbock             #+#    #+#             */
/*   Updated: 2024/03/19 10:36:07 by fahmadia         ###   ########.fr       */
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

static bool	check_wall(t_window_frame *gui, int new_x, int new_y)
{
	if (gui->config_file.map->map_plan[new_x][new_y] == WALL ||
		gui->config_file.map->map_plan[new_x][new_y] == INIT)
	{
		return (true);
	}
	return (false);
}

static void	move_left_right(t_window_frame *gui, double *new_x, double *new_y,
							mlx_key_data_t keydata)
{
	double	perpendicular_x;
	double	perpendicular_y;

	perpendicular_x = gui->player.player_dir_y;
	perpendicular_y = -gui->player.player_dir_x;
	if (keydata.key == MLX_KEY_A)
	{
		*new_x -= perpendicular_x * SPEED;
		*new_y -= perpendicular_y * SPEED;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		*new_x += perpendicular_x * SPEED;
		*new_y += perpendicular_y * SPEED;
	}
}

void	handle_movement(mlx_key_data_t keydata, t_window_frame *gui)
{
	double	new_x;
	double	new_y;

	new_x = gui->player.player_pos_x;
	new_y = gui->player.player_pos_y;
	if (keydata.key == MLX_KEY_W)
	{
		new_x += gui->player.player_dir_x * SPEED;
		new_y += gui->player.player_dir_y * SPEED;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		new_x -= gui->player.player_dir_x * SPEED;
		new_y -= gui->player.player_dir_y * SPEED;
	}
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		move_left_right(gui, &new_x, &new_y, keydata);
	if (!check_wall(gui, (int)new_x, (int)new_y))
	{
		gui->player.player_pos_x = new_x;
		gui->player.player_pos_y = new_y;
		draw_image(gui);
		new_frame(gui);
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
	handle_movement(keydata, gui);
	if (keydata.key == 262)
		rotate(gui, true);
	else if (keydata.key == 263)
		rotate(gui, false);
	else if (keydata.key == 256)
		handle_escape(gui);
	else if (keydata.key == 81)
		reset(gui);
}
