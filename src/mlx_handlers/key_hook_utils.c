/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:59:45 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/03/18 14:00:18 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_escape(t_window_frame *gui)
{
	mlx_delete_image(gui->window, gui->frame);
	mlx_terminate(gui->window);
	exit(EXIT_SUCCESS);
}
