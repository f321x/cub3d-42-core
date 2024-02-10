/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:55:38 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2024/02/09 16:43:09 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	all_valid_chars(t_conf_file *conf_file)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < conf_file->map->rows_num)
	{
		j = 0;
		while (j < conf_file->map->columns_per_row[i])
		{
			if (conf_file->map->map_plan[i][j] == NONE)
			{
				conf_file->error = INVALID_MAP_CHAR;
				print_err_msg("Invalid character in map", "", "");
				return (false);
			}
			j++;
		}
		i++;
	}
	
	return (true);
}

bool	parse_map(t_conf_file *conf_file)
{
	if (!all_valid_chars(conf_file))
		return (false);
	return (true);
}
