/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:07 by fbock             #+#    #+#             */
/*   Updated: 2024/03/20 11:04:47 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_south_west(t_window_frame *gui, int x,
									int y, t_player_pos *p)
{
	if (gui->config_file.map->map_plan[x][y] == 'S')
	{
		p->player_dir_x = 1;
		p->player_dir_y = 0;
		p->camera_plane_x = 0;
		p->camera_plane_y = -0.66;
		p->init_dir = 'S';
	}
	else if (gui->config_file.map->map_plan[x][y] == 'W')
	{
		p->player_dir_x = 0;
		p->player_dir_y = -1;
		p->camera_plane_x = -0.66;
		p->camera_plane_y = 0;
		p->init_dir = 'W';
	}
}

static void	set_player_direction(t_window_frame *gui, int x,
									int y, t_player_pos *p)
{
	if (gui->config_file.map->map_plan[x][y] == 'N')
	{
		p->player_dir_x = -1;
		p->player_dir_y = 0;
		p->camera_plane_x = 0;
		p->camera_plane_y = 0.66;
		p->init_dir = 'N';
	}
	else if (gui->config_file.map->map_plan[x][y] == 'E')
	{
		p->player_dir_x = 0;
		p->player_dir_y = 1;
		p->camera_plane_x = 0.66;
		p->camera_plane_y = 0;
		p->init_dir = 'E';
	}
	set_player_south_west(gui, x, y, p);
}

// initializes the player position in the gui struct
// with the parsed start coordinates from the map file
void	init_player(t_window_frame *gui)
{
	t_player_pos	*p;

	p = &(gui->player);
	p->player_pos_x = (double)gui->config_file.map->player_coord[0];
	p->player_pos_y = (double)gui->config_file.map->player_coord[1];
	set_player_direction(gui, gui->config_file.map->player_coord[0],
		gui->config_file.map->player_coord[1], &(gui->player));
	p->map_x = gui->config_file.map->player_coord[0];
	p->map_y = gui->config_file.map->player_coord[1];
}

int	main(int argc, char **argv)
{
	t_window_frame	gui;

	if (!parse_config_file(argc, argv, &(gui.config_file)))
		return (gui.config_file.error);
	if (!textures_dirs_are_valid(gui) || !textures_extension_valid(gui))
	{
		free_config_file_members(&(gui.config_file));
		return (gui.config_file.error);
	}
	init_player(&gui);
	init_gui(&gui);
	init_hooks(&gui);
	mlx_loop(gui.window);
	cleanup_without_error(&gui);
	free_config_file_members(&(gui.config_file));
	return (0);
}
