/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:55:38 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/10 10:33:17 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_char_valid(t_conf_file *conf_file, size_t i, size_t j)
{
	char	cur_char;

	cur_char = conf_file->map->map_plan[i][j];
	if (cur_char == NONE)
	{
		conf_file->error = INVALID_MAP_CHAR;
		print_err_msg("Invalid character in map", "", "");
		return (false);
	}
	return (true);
}

bool	search_for_player(t_conf_file *conf_file, size_t i, size_t j)
{
	bool	is_player;
	char	cur_char;

	cur_char = conf_file->map->map_plan[i][j];
	is_player = cur_char == NORTH || cur_char == SOUTH || cur_char == EAST || cur_char == WEST;
	if (is_player)
	{
		conf_file->map->is_player = true;
		conf_file->map->player_coord[0] = i;
		conf_file->map->player_coord[1] = j;
		return (true);
	}
	return (false);
}

bool	is_only_one_player(t_conf_file *conf_file, size_t i, size_t j)
{
	bool	is_player;
	char	cur_char;

	cur_char = conf_file->map->map_plan[i][j];
	is_player = cur_char == NORTH || cur_char == SOUTH || cur_char == EAST || cur_char == WEST;

	if (conf_file->map->is_player && is_player)
	{
		conf_file->error = MULTI_PLAYER;
		print_err_msg("Only one player is allowed", "", "");
		return (false);
	}
	else 
		return (true);
}

bool	is_player_found(t_conf_file *conf_file)
{
	if (!(conf_file->map->is_player))
	{
		conf_file->error = NO_PLAYER;
		print_err_msg("One player is needed", "", "");
		return (false);
	}
	return (true);
}

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
			if (!is_only_one_player(conf_file, i, j))
				return (false);
			if (!is_char_valid(conf_file, i, j))
				return (false);
			search_for_player(conf_file, i, j);
			j++;
		}
		i++;
	}
	if (!is_player_found(conf_file))
		return (false);
	return (true);
}


bool	parse_map(t_conf_file *conf_file)
{
	if (!all_valid_chars(conf_file))
		return (false);
	return (true);
}
