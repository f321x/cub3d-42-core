/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:16:25 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/03/18 11:44:39 by ***REMOVED***         ###   ########.fr       */
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











bool	is_inside_map(t_window_frame *gui, float player_new_x, float player_new_y)
{
	size_t	x;
	size_t	y;
	x = trunc(player_new_x);
	y = trunc(player_new_y);
	printf("player_new_x: %lu\n", x);
	printf("player_new_y: %lu\n", y);
	// if (gui->config_file.map->map_plan[x][y] == INIT
	// 	|| gui->config_file.map->map_plan[x][y] == NEW_LINE)
	// {
	// 	printf("MAP BORDER!\n");
	// 	return (false);
	// }
		printf("********gui->config_file.map->rows_num = %lu\n", gui->config_file.map->rows_num);
	if (x <= 0 || x >= gui->config_file.map->rows_num || y <= 0 || y >= gui->config_file.map->columns_per_row[x] || gui->config_file.map->map_plan[x][y] == INIT || gui->config_file.map->map_plan[x][y] == NEW_LINE || gui->config_file.map->map_plan[x][y] == WALL)
		return (false);
	else
		return (true);
}

bool	move_south_east(t_window_frame *gui,float dx, float dy)
{
	float 	player_new_x;
	float	player_new_y;
	player_new_x = gui->player.player_pos_x + dx;
	player_new_y = gui->player.player_pos_y + dy;
	if (!is_inside_map(gui, player_new_x, player_new_y))
		return (false);
	gui->player.player_pos_y += dy;
	gui->player.player_pos_x += dx;
	printf("gui->config_file.map->map_plan[x][y] = %c\n", gui->config_file.map->map_plan[(int)player_new_x][(int)player_new_y]);
	return (true);
}

bool	move_south_west(t_window_frame *gui,float dx, float dy)
{
	float 	player_new_x;
	float	player_new_y;

	player_new_x = gui->player.player_pos_x + dx;
	player_new_y = gui->player.player_pos_y - dy;
	if (!is_inside_map(gui, player_new_x, player_new_y))
		return (false);
	gui->player.player_pos_y -= dy;
	gui->player.player_pos_x += dx;
	printf("gui->config_file.map->map_plan[x][y] = %c\n", gui->config_file.map->map_plan[(int)player_new_x][(int)player_new_y]);
	return (true);
}

bool	move_north_east(t_window_frame *gui,float dx, float dy)
{
	float 	player_new_x;
	float	player_new_y;

	player_new_x = gui->player.player_pos_x - dx;
	player_new_y = gui->player.player_pos_y + dy;
	if (!is_inside_map(gui, player_new_x, player_new_y))
		return (false);
	gui->player.player_pos_y += dy;
	gui->player.player_pos_x -= dx;
	printf("gui->config_file.map->map_plan[x][y] = %c\n", gui->config_file.map->map_plan[(int)player_new_x][(int)player_new_y]);
	return (true);
}

bool	move_north_west(t_window_frame *gui,float dx, float dy)
{
	float 	player_new_x;
	float	player_new_y;

	player_new_y = gui->player.player_pos_y - dy;
	player_new_x = gui->player.player_pos_x - dx;
	if (!is_inside_map(gui, player_new_x, player_new_y))
		return (false);
	gui->player.player_pos_y -= dy;
	gui->player.player_pos_x -= dx;
	printf("gui->config_file.map->map_plan[x][y] = %c\n", gui->config_file.map->map_plan[(int)player_new_x][(int)player_new_y]);
	return (true);
}

void	move_forward(t_window_frame *gui, float  dx, float dy, float angle)
{
	// float	player_new_x;
	// float	player_new_y;

	if (gui->player.player_dir_y == 0 && gui->player.player_dir_x == 0)
		angle = 0;
	else
		angle = atan(gui->player.player_dir_y / gui->player.player_dir_x);
	dx = SPEED * cos(fabs(angle));
	dy = SPEED * sin(fabs(angle));
	if (gui->player.player_dir_y >= 0 && gui->player.player_dir_x >= 0)
		move_south_east(gui, dx, dy);
	else if (gui->player.player_dir_y < 0 && gui->player.player_dir_x >= 0)
		move_south_west(gui, dx, dy);
	else if (gui->player.player_dir_y >= 0 && gui->player.player_dir_x < 0)
		move_north_east(gui,dx, dy);
	else
		move_north_west(gui, dx, dy);
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
	// float	player_new_x;
	// float	player_new_y;

	if (gui->player.player_dir_y == 0 && gui->player.player_dir_x == 0)
		angle = 0;
	else
		angle = atan(gui->player.player_dir_y / gui->player.player_dir_x);
	dx = SPEED * cos(fabs(angle));
	dy = SPEED * sin(fabs(angle));
	if (gui->player.player_dir_y >= 0 && gui->player.player_dir_x >= 0)
		move_north_west(gui, dx, dy);
	else if (gui->player.player_dir_y < 0 && gui->player.player_dir_x >= 0)
		move_north_east(gui, dx, dy);
	else if (gui->player.player_dir_y >= 0 && gui->player.player_dir_x < 0)
		move_south_west(gui, dx, dy);
	else
		move_south_east(gui, dx, dy);
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
	// float	player_new_x;
	// float	player_new_y;

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
		move_south_east(gui, dx, dy);
	}
	else if (gui->player.player_dir_y >= 0 && gui->player.player_dir_x >= 0)
	{
		printf("SE\n");
		move_south_west(gui, dx, dy);
	}
	else if (gui->player.player_dir_y < 0 && gui->player.player_dir_x >= 0)
	{
		printf("SW\n");
		move_north_west(gui, dx, dy);
	}
	else
	{
		printf("NW\n");
		move_north_east(gui, dx, dy);
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
	// float	player_new_x;
	// float	player_new_y;

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
		move_north_west(gui, dx, dy);
	}
	else if (gui->player.player_dir_y >= 0 && gui->player.player_dir_x >= 0)
	{
		printf("SE\n");
		move_north_east(gui, dx, dy);
	}
	else if (gui->player.player_dir_y < 0 && gui->player.player_dir_x >= 0)
	{
		printf("SW\n");
		move_south_east(gui, dx, dy);
	}
	else
	{
		printf("NW\n");
		move_south_west(gui, dx, dy);
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
	float	dx = 0;
	float	dy = 0;
	float	angle = 0 ;

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

// static bool	check_wall(t_window_frame *gui, int new_x, int new_y)
// {
// 	if (gui->config_file.map->map_plan[new_x][new_y] == WALL ||
// 		gui->config_file.map->map_plan[new_x][new_y] == INIT)
// 	{
// 		return (true);
// 	}
// 	return (false);
// }

/* void handle_movement(mlx_key_data_t keydata, t_window_frame *gui)
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
	// uncommented, idk?
	else if (keydata.key == MLX_KEY_S)
	{
		new_x -= gui->player.player_dir_x * SPEED;
		new_y -= gui->player.player_dir_y * SPEED;
	}
	if (!check_wall(gui, (int)new_x, (int)new_y))
	{
		gui->player.player_pos_x = new_x;
		gui->player.player_pos_y = new_y;
		draw_image(gui);
		new_frame(gui);
	}
} */

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
