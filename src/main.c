/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:07 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/09 13:54:20 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_window_frame gui;

	t_conf_file	config_file;

	init_gui(&gui);
	init_hooks(&gui);

	if (!parse_config_file(argc, argv, &config_file))
		return (config_file.error);
	free_config_file_members(&config_file);
	return (0);
}
