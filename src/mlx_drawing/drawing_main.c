/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:42:10 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/21 12:52:05 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	convert_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_image(t_window_frame *gui)
{
	t_wall	*walls;
	int		width_index;
	int		height_index;
	int32_t	pixel;

	walls = raycast_whole_frame(gui->width, gui->height, gui->player, *(gui->config_file.map));
	width_index = 0;

	gui->buffer = mlx_new_image(gui->window, gui->width, gui->height);
	if (!gui->buffer)
		cleanup(gui);
	while (width_index < gui->width)
	{
		height_index = 0;
		while (height_index < gui->height)
		{
			if (height_index < walls[width_index].wall_bottom_pixel)
				pixel = gui->config_file.c_color;
			else if (height_index > walls[width_index].wall_top_pixel)
				pixel = gui->config_file.f_color;
			else
				pixel = convert_rgba(255,0,0,120);
			mlx_put_pixel(gui->buffer, width_index,
				height_index, pixel);
			height_index++;
		}
		width_index++;
	}
	free(walls);
}

void new_frame(t_window_frame *gui)
{
	if ((mlx_image_to_window(gui->window, gui->buffer, 0, 0)) < 0)
		cleanup(gui);
	mlx_delete_image(gui->window, gui->frame);
	gui->frame = gui->buffer;
	gui->buffer = NULL;
}
