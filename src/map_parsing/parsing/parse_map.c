/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:55:38 by fahmadia          #+#    #+#             */
/*   Updated: 2024/03/18 14:07:54 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	search_for_player(t_conf_file *conf_file, size_t i, size_t j)
{
	bool	is_player;
	char	cur_char;

	cur_char = conf_file->map->map_plan[i][j];
	is_player = cur_char == NORTH || cur_char == SOUTH
		|| cur_char == EAST || cur_char == WEST;
	if (is_player)
	{
		conf_file->map->is_player = true;
		conf_file->map->player_coord[0] = i;
		conf_file->map->player_coord[1] = j;
		return (true);
	}
	return (false);
}

static bool	check_if_closed(char field, int x, int y, t_conf_file *conf_file)
{
	if ((x == 0 || x == (int)conf_file->map->columns_per_row[y] - 1)
		&& field != '1')
		return (false);
	if ((y == 0 || y == (int)conf_file->map->rows_num - 1) && field != '1')
		return (false);
	return (true);
}

void	check_next_coord(t_conf_file *conf_file, int x, int y)
{
	char		field;
	static bool	is_wsp = false;
	static bool	is_closed = true;

	field = conf_file->map->map_copy[y][x];
	if (field == SPACE || field == NEW_LINE || field == INIT)
		is_wsp = true;
	if (field == '1' || field == 'X')
		return ;
	if (x < 0 || x > (int)conf_file->map->columns_per_row[y] - 1)
		return ;
	if (y < 0 || y > (int)conf_file->map->rows_num - 1)
		return ;
	is_closed = check_if_closed(field, x, y, conf_file);
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

bool	is_only_one_player(t_conf_file *conf_file, size_t i, size_t j)
{
	bool	is_player;
	char	cur_char;

	cur_char = conf_file->map->map_plan[i][j];
	is_player = cur_char == NORTH || cur_char == SOUTH
		|| cur_char == EAST || cur_char == WEST;
	if (conf_file->map->is_player && is_player)
	{
		conf_file->error = MULTI_PLAYER;
		print_err_msg("Only one player is allowed", "", "");
		return (false);
	}
	else
		return (true);
}

map_ptr	duplicate_map_plan(t_conf_file const *conf_file, map_ptr map_copy_ptr)
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
