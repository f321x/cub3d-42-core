/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:52:31 by fbock             #+#    #+#             */
/*   Updated: 2024/03/20 10:52:39 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// cleanup function to be called on error
// to free up memory and exit with error
void	cleanup(t_window_frame *gui)
{
	if (gui->frame)
		mlx_delete_image(gui->window, gui->frame);
	if (gui->buffer)
		mlx_delete_image(gui->window, gui->buffer);
	if (gui->window)
		mlx_terminate(gui->window);
	if (gui->textures.north.pixels)
		free(gui->textures.north.pixels);
	if (gui->textures.east.pixels)
		free(gui->textures.east.pixels);
	if (gui->textures.west.pixels)
		free(gui->textures.west.pixels);
	if (gui->textures.south.pixels)
		free(gui->textures.south.pixels);
	exit(EXIT_FAILURE);
}

void	cleanup_without_error(t_window_frame *gui)
{
	if (gui->frame)
		mlx_delete_image(gui->window, gui->frame);
	if (gui->buffer)
		mlx_delete_image(gui->window, gui->buffer);
	if (gui->window)
		mlx_terminate(gui->window);
	if (gui->textures.north.pixels)
		free(gui->textures.north.pixels);
	if (gui->textures.east.pixels)
		free(gui->textures.east.pixels);
	if (gui->textures.west.pixels)
		free(gui->textures.west.pixels);
	if (gui->textures.south.pixels)
		free(gui->textures.south.pixels);
	free_config_file_members(&(gui->config_file));
}
