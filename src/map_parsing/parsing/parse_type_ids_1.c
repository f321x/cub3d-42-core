/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_ids_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:32:21 by fahmadia          #+#    #+#             */
/*   Updated: 2024/03/18 13:47:39 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	all_id_types_present(t_conf_file *conf_file)
{
	if (conf_file->no_exist && conf_file->so_exist && conf_file->ea_exist
		&& conf_file->we_exist && conf_file->c_exist && conf_file->f_exist)
	{
		conf_file->all_ids_found = true;
		return (true);
	}
	else
		return (false);
}

bool	is_empty_line(const t_conf_file *const config_file, t_line *results)
{
	if (results->current_line[0] == '\n' || results->current_line[0] == '\0')
	{
		free(results->current_line);
		*results = get_next_line(config_file->fd);
		return (true);
	}
	return (false);
}

bool	valid_line(t_conf_file *conf_file, char *trimmed_begin, t_line *results)
{
	char	*first_three_chars;
	bool	color_info;

	first_three_chars = ft_substr(trimmed_begin, 0, 3);
	color_info = first_three_chars[0] == 'C' || first_three_chars[0] == 'F';
	if (id_is_valid(conf_file, first_three_chars))
	{
		free(first_three_chars);
		if (color_info)
		{
			if (!is_color_valid(conf_file, results))
				return (false);
		}
		return (true);
	}
	else
	{
		free(first_three_chars);
		return (false);
	}
}

bool	parse_cur_line(t_conf_file *conf_file, char *trim_line, t_line *results)
{
	if (!valid_line(conf_file, trim_line, results))
	{
		free_pointer(&(results->remainder));
		free_pointer(&(results->current_line));
		close(conf_file->fd);
		return (false);
	}
	return (true);
}

bool	store_map(t_conf_file *config_file, t_line *results)
{
	if (all_id_types_present(config_file) && !copy_map(config_file, results))
	{
		free_pointer(&(results->remainder));
		free_pointer(&(results->current_line));
		close(config_file->fd);
		return (false);
	}
	return (true);
}
