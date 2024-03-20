/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:07 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/03/20 10:48:52 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	end_program(t_conf_file *conf_file, t_window_frame *gui)
{
	mlx_terminate(gui->window);
	free_config_file_members(conf_file);
}

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

bool	open_current_file(t_window_frame gui, char *current_texture_dir)
{
	int fd;
	
	fd = open(current_texture_dir, O_RDONLY | EISDIR);
	if (fd == -1)
	{
		gui.config_file.error = INVALID_TEXTURE_DIR;
		print_err_msg("Invalid texture directory", ": ", current_texture_dir);
		return (false);
	}
	close(fd);
	return (true);
}

bool	open_all_files(t_window_frame gui)
{
	int i;
	char	*textures_dirs[4];

	textures_dirs[0] = gui.config_file.no_info;
	textures_dirs[1] = gui.config_file.ea_info;
	textures_dirs[2] = gui.config_file.so_info;
	textures_dirs[3] = gui.config_file.we_info;
	i = 0;
	while (i < 4)
	{
		if (!open_current_file(gui, textures_dirs[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	textures_dirs_are_valid(t_window_frame gui)
{
	if (!open_all_files(gui))
		return (false);
	return (true);
}

bool	current_extension_valid(t_window_frame gui, char *current_texture_dir)
{
	size_t	length;
	char	*extension;

	length = ft_strlen(current_texture_dir);
	extension = ft_substr(current_texture_dir, length - 1 - 3, 4);
	if (ft_strncmp(".png", extension, 4) != 0)
	{
		gui.config_file.error = INVALID_TEXTURE_EXTENSION;
		print_err_msg("Invalid texture extension", ": ", current_texture_dir);
		return (false);
	}
	free(extension);
	return (true);
}

bool	textures_extension_valid(t_window_frame gui)
{
	int i;
	char	*textures_dirs[4];

	textures_dirs[0] = gui.config_file.no_info;
	textures_dirs[1] = gui.config_file.ea_info;
	textures_dirs[2] = gui.config_file.so_info;
	textures_dirs[3] = gui.config_file.we_info;
	i = 0;
	while (i < 4)
	{
		if (!current_extension_valid(gui, textures_dirs[i]))
			return (false);
		i++;
	}
	return (true);
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
	end_program(&(gui.config_file), &gui);
	free_config_file_members(&(gui.config_file));
	return (0);
}
