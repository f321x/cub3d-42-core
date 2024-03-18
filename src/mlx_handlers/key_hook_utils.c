/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:59:45 by fbock             #+#    #+#             */
/*   Updated: 2024/03/18 14:00:18 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_escape(t_window_frame *gui)
{
	mlx_delete_image(gui->window, gui->frame);
	mlx_terminate(gui->window);
	exit(EXIT_SUCCESS);
}
