/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:42:10 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/20 16:14:41 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	convert_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_image(t_window_frame *gui)
{
	t_wall	*walls;
	int		width_index;
	int		height_index;
	int32_t	pixel;

	// printf("draw_image: map_y: %d | map_x: %d\n", p.map_y, p.map_x);
	walls = raycast_whole_frame(gui->width, gui->height, gui->player, *(gui->config_file.map));
	width_index = 0;

	gui->buffer = mlx_new_image(gui->window, gui->width, gui->height);
	if (!gui->buffer)
		cleanup(gui);

	// for (int i = 0; i < gui->width; i++) {
	// 	printf("Wall top: %d, wall bottom: %d \n", walls[i].wall_top_pixel, walls[i].wall_bottom_pixel);
	// }
	while (width_index < gui->width)
	{
		height_index = 0;
		while (height_index < gui->height)
		{
			if (height_index > walls[width_index].wall_top_pixel)
				pixel = convert_rgba(0,0,255,120);
			else if (height_index < walls[width_index].wall_bottom_pixel)
				pixel = convert_rgba(0,255,0,120);
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
