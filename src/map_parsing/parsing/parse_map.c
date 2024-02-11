/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:55:38 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/11 12:56:25 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_char_valid(t_conf_file *conf_file, size_t i, size_t j)
{
	char	cur_char;

	cur_char = conf_file->map->map_plan[i][j];
	if (cur_char != SPACE && cur_char != NEW_LINE
		&& cur_char != WALL && cur_char != EMPTY && cur_char != NORTH
		&& cur_char != SOUTH && cur_char != WEST && cur_char != EAST)
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

void	check_next_coord(t_conf_file *conf_file, int x, int y)
{
	char		field;
	static bool	is_wsp = false;
	static bool	is_closed = true;

	field = conf_file->map->map_copy[y][x];
	if (field ==  SPACE || field == NEW_LINE || field == INIT)
		is_wsp = true;
	if (field == '1' || field == 'X')
		return ;
	if (x < 0 || x > (int)conf_file->map->columns_per_row[y] - 1)
		return ;
	if (y < 0 || y > (int)conf_file->map->rows_num - 1)
		return ;
	if ((x == 0 || x == (int)conf_file->map->columns_per_row[y] - 1)
		&& field != '1')
		is_closed = false;
	if ((y == 0 || y == (int)conf_file->map->rows_num - 1) && field != '1')
		is_closed = false;
	conf_file->map->map_copy[y][x] = 'X';
	check_next_coord(conf_file, x, y - 1);
	check_next_coord(conf_file, x, y + 1);
	check_next_coord(conf_file, x + 1, y);
	check_next_coord(conf_file, x - 1, y);
	if (!is_wsp && is_closed)
		conf_file->map->is_map_valid = true;
	else
		conf_file->map->is_map_valid = false;
}

char (*duplicate_map_plan(t_conf_file const *conf_file, char(*map_copy_ptr)[MAX_ROW_NUM][MAX_COLUMN_NUM]))[MAX_ROW_NUM][MAX_COLUMN_NUM]
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < conf_file->map->rows_num)
	{
		j = 0;
		while (j < conf_file->map->max_columns_num)
		{
			(*map_copy_ptr)[i][j] = conf_file->map->map_plan[i][j];
			j++;
		}
		i++;
	}
	return (map_copy_ptr);
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

bool	parse_map(t_conf_file *conf_file)
{
	if (!all_valid_chars(conf_file))
		return (false);
	if (!is_map_closed(conf_file))
		return (false);
	return (true);
}
