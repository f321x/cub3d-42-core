/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:17:57 by fbock             #+#    #+#             */
/*   Updated: 2024/03/18 13:19:19 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
