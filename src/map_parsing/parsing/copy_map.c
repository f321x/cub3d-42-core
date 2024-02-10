/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:44:54 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2024/02/10 09:21:13 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_field	setField(char current_char)
{
	t_field	field;

	if (current_char == ' ' || current_char == '\t')
		field = WSP;
	else if (current_char == '1')
		field = WALL;
	else if (current_char == '0')
		field = EMPTY;
	else if (current_char == 'N')
		field = NORTH;
	else if (current_char == 'S')
		field = SOUTH;
	else if (current_char == 'E')
		field = EAST;
	else if (current_char == 'W')
		field = WEST;
	else if (current_char == '\n')
		field = NEW_LINE;
	else
		field = NONE;
	return field;
}

bool	is_map_size_correct(t_conf_file *conf_file, int row, char *current_line)
{
	if (row >= MAX_ROW_NUM || ft_strlen(current_line) > MAX_COLUMN_NUM)
	{
		print_err_msg("Map is too big", "", "");
		conf_file->error = MAP_TOO_BIG;
		return (false);
	}
	return (true);
}

bool	copy_char_by_char(t_conf_file *conf_file, char *current_line)
{
	int			i;
	static int	row = 0;
	t_field		field;

	i = 0;
	if (!is_map_size_correct(conf_file, row, current_line))
		return (false);
	while (current_line[i])
	{
		// if (current_line[i] == '\n')
		// {
		// 	conf_file->map->map_plan[row][i] = NEW_LINE;
		// 	break ;
		// }
		
		field = setField(current_line[i]);
		conf_file->map->map_plan[row][i] = field;
		if (current_line[i] == '\n')
			break ;
		i++;
	}
	row++;
	return (true);
}

// void	init_map_plan(t_field (*map_plan)[MAX_MAP_X_WIDTH][MAX_MAP_Y_HEIGHT])
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < MAX_MAP_X_WIDTH)
// 	{
// 		j = 0;
// 		while (j < MAX_MAP_Y_HEIGHT)
// 		{
// 			(*map_plan)[i][j] = NONE;
// 			j++;
// 		}
		
// 		i++;
// 	}
	
// }

void	init_map_plan(t_field (*map_plan)[MAX_COLUMN_NUM])
{
	int	i;

	i = 0;
	while (i < MAX_COLUMN_NUM)
	{
			(*map_plan)[i] = INIT;
		i++;
	}
}

bool	is_row_empty(t_field *row)
{
	int	column;

	column = 0;
	while (column < MAX_COLUMN_NUM)
	{
		if (row[column] != INIT)
			return (false);
		column++;
	}
	return (true);
}


size_t	get_row_num(t_conf_file *conf_file)
{
	size_t	row_num;

	row_num = 0;
	while (row_num < MAX_ROW_NUM)
	{
		if (is_row_empty(conf_file->map->map_plan[row_num]))
			break ;
		row_num++;
	}
	return (row_num);
}

void	get_column_nums(t_conf_file *conf_file)
{
	int		row;
	int		column;

	row = 0;
	column = 0;
	while (row < MAX_ROW_NUM)
	{
		column = 0;
		while (column < MAX_COLUMN_NUM)
		{
			if (conf_file->map->map_plan[row][column] == INIT
				|| conf_file->map->map_plan[row][column] == NEW_LINE)
			{
				conf_file->map->columns_per_row[row] = column;
				break ;
			}
			column++;
		}
		conf_file->map->columns_per_row[row] = column;
		row++;
	}
}

size_t	get_max_column_num(t_conf_file *conf_file)
{
	size_t	i;
	size_t	max_columns_num;

	max_columns_num = 0;
	i = 0;
	get_column_nums(conf_file);
	while (i < conf_file->map->rows_num)
	{
		if (conf_file->map->columns_per_row[i] > max_columns_num)
			max_columns_num = conf_file->map->columns_per_row[i];
		i++;
	}
	return (max_columns_num);
}

bool	copy_map(t_conf_file *conf_file, t_line *results)
{
	t_map	*map;
	int		i;

	map = ft_calloc(1, sizeof(t_map));
	i = 0;
	while (i < MAX_ROW_NUM)
	{
		init_map_plan(&(map->map_plan[i]));
		i++;
	}
	conf_file->map = map;
	while (results->current_line)
	{
		if (!copy_char_by_char(conf_file, results->current_line))
			return (false);
		free_pointer(&(results->current_line));
		*results = get_next_line(conf_file->fd);
	}
	conf_file->map->rows_num = get_row_num(conf_file);
	conf_file->map->max_columns_num = get_max_column_num(conf_file);
	
	return (true);
}
