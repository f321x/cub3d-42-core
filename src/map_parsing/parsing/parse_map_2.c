/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:25:11 by fbock             #+#    #+#             */
/*   Updated: 2024/03/19 10:57:06 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_player_found(t_conf_file *conf_file)
{
	if (!(conf_file->map->is_player))
	{
		conf_file->error = NO_PLAYER;
		print_err_msg("One player is needed", "", "");
		return (false);
	}
	return (true);
}

bool	is_char_valid(t_conf_file *conf_file, size_t i, size_t j)
{
	char	cur_char;

	cur_char = conf_file->map->map_plan[i][j];
	if (cur_char != SPACE && cur_char != NEW_LINE
		&& cur_char != WALL && cur_char != EMPTY && cur_char != NORTH
		&& cur_char != SOUTH && cur_char != WEST && cur_char != EAST)
	{
		conf_file->error = INVALID_MAP_CHAR;
		print_err_msg("Invalid character in map or invalid type id", "", "");
		return (false);
	}
	return (true);
}

bool	is_map_closed(t_conf_file *conf_file)
{
	int		x;
	int		y;

	y = conf_file->map->player_coord[0];
	x = conf_file->map->player_coord[1];
	duplicate_map_plan(conf_file, &(conf_file->map->map_copy));
	check_next_coord(conf_file, x, y);
	if (conf_file->map->is_map_valid)
		return (true);
	else
	{
		print_err_msg("Player is not surrounded by walls", "", "");
		conf_file->error = MAP_NOT_SURROUNDED_BY_WALLS;
		return (false);
	}
}

static bool	all_valid_chars(t_conf_file *conf_file)
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
	if (!is_map_closed(conf_file))
		return (false);
	return (true);
}
