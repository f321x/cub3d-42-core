/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:07 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/11 14:43:36 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv)
{
	t_conf_file	config_file;

	if (!parse_config_file(argc, argv, &config_file))
		return (config_file.error);
	print_test(config_file);
	print_map_plan(&config_file, config_file.map->map_plan);
	print_map_plan(&config_file, config_file.map->map_copy);
	free_config_file_members(&config_file);
	return (0);
}
