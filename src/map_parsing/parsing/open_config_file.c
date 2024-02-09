/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_config_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:54:04 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2024/02/09 14:08:16 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	open_config_file(t_conf_file *config_file)
{
	config_file->fd = open(config_file->conf_file_name, O_RDONLY);
	if (config_file->fd == -1)
	{
		print_err_msg(strerror(errno), ": ", config_file->conf_file_name);
		config_file->error = NO_FILE_OR_DIRECTORY;
		return (false);
	}
	return (true);
}
