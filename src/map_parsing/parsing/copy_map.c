/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:44:54 by fahmadia          #+#    #+#             */
/*   Updated: 2024/03/18 13:18:47 by fbock            ###   ########.fr       */
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
