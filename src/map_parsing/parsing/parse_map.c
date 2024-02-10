/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:55:38 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2024/02/10 16:56:12 by ***REMOVED***         ###   ########.fr       */
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

// bool	check_next_coord(t_conf_file *conf_file, int x, int y)
// {
// 	t_field		field;
// 	static bool	is_wsp = false;
// 	static bool	is_closed = true;
// 	// printf("x = %d\n", x);
// 	// printf("y = %d\n", y);
// 	field = conf_file->map->map_plan[y][x];
// 	if (field ==  WSP || field == NEW_LINE || field == INIT)
// 	{
// 		is_wsp = true;
// 		// return (false);
// 	}
// 	// if (field == WALL || field == INIT)
// 	// 	return (true);
// 	if (field == WALL)
// 		return (true);
// 	if (x < 0 || x > (int)conf_file->map->columns_per_row[y] - 1)
// 		return (false);
// 	if (y < 0 || y > (int)conf_file->map->rows_num - 1)
// 		return (false);
// 	if ((x == 0 || x == (int)conf_file->map->columns_per_row[y] - 1) && field != WALL)
// 	{
// 		is_closed = false;
// 	}
// 	if ((y == 0 || y == (int)conf_file->map->rows_num - 1) && field != WALL)
// 	{
// 		is_closed = false;
// 	}
// 	printf("field = %d\n", field);
// 	// print_map_plan(conf_file);
// 	// printf("---------------------\n");
// 	conf_file->map->map_plan[y][x] = WALL;
// 	print_map_plan(conf_file);
// 	printf("---------------------\n");
// 	check_next_coord(conf_file, x, y - 1);
// 	check_next_coord(conf_file, x, y + 1);
// 	check_next_coord(conf_file, x + 1, y);
// 	check_next_coord(conf_file, x - 1, y);
// 	if (!is_wsp && is_closed)
// 		return (true);
// 	else
// 		return (false);
// }

void	check_next_coord(t_conf_file *conf_file, int x, int y)
{
	t_field		field;
	static bool	is_wsp = false;
	static bool	is_closed = true;

	field = conf_file->map->map_copy[y][x];
	if (field ==  WSP || field == NEW_LINE || field == INIT)
		is_wsp = true;
	if (field == WALL || field == TEST)
		return ;
	if (x < 0 || x > (int)conf_file->map->columns_per_row[y] - 1)
		return ;
	if (y < 0 || y > (int)conf_file->map->rows_num - 1)
		return ;
	if ((x == 0 || x == (int)conf_file->map->columns_per_row[y] - 1)
		&& field != WALL)
		is_closed = false;
	if ((y == 0 || y == (int)conf_file->map->rows_num - 1) && field != WALL)
		is_closed = false;
	conf_file->map->map_copy[y][x] = WALL;
	print_map_plan(conf_file, conf_file->map->map_copy);
	printf("------------------------------------------------------\n");
	check_next_coord(conf_file, x, y - 1);
	check_next_coord(conf_file, x, y + 1);
	check_next_coord(conf_file, x + 1, y);
	check_next_coord(conf_file, x - 1, y);
	if (!is_wsp && is_closed)
		conf_file->map->is_map_valid = true;
}

t_field (*duplicate_map_plan(t_conf_file const *conf_file, t_field(*map_copy_ptr)[MAX_ROW_NUM][MAX_COLUMN_NUM]))[MAX_ROW_NUM][MAX_COLUMN_NUM]
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
	{
		//free();
		return (false);
	}
	return (true);
}
