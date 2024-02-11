/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:44:54 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/11 15:42:07 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	i = 0;
	if (!is_map_size_correct(conf_file, row, current_line))
		return (false);
	while (current_line[i])
	{
		conf_file->map->map_plan[row][i] = current_line[i];
		i++;
	}
	row++;
	return (true);
}

void	init_map_plan(char (*map_plan)[MAX_COLUMN_NUM])
{
	int	i;

	i = 0;
	while (i < MAX_COLUMN_NUM)
	{
			(*map_plan)[i] = INIT;
		i++;
	}
}

bool	is_row_empty(char *row)
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

bool	is_other_char(char *row, size_t column)
{
	size_t	i;

	i = 0;
	while ((i < MAX_COLUMN_NUM - column - 1) && row[i] != NEW_LINE)
	{
		if (row[i + column] != INIT)
			return (true);
		i++;
	}
	return (false);
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
			if (conf_file->map->map_plan[row][column] == INIT)
			{
				if (!is_other_char(conf_file->map->map_plan[row], column))
				{
					conf_file->map->columns_per_row[row] = column;
					break ;
				}
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
