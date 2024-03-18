/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_ids_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:00:05 by fahmadia          #+#    #+#             */
/*   Updated: 2024/03/18 13:47:50 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_type_id_unique(t_conf_file *conf_file, bool *id_exists, char *id)
{
	if (*id_exists == true)
	{
		conf_file->duplicate_id = true;
		print_err_msg("Duplicate type identifier", ": ", id);
		conf_file->error = WRONG_CONFIG_FILE_TYPE_ID;
		return (false);
	}
	return (true);
}

bool	followed_by_wsp(char *first_three_chars, t_id type_id)
{
	if (type_id == NO || type_id == SO || type_id == EA || type_id == WE)
	{
		if (first_three_chars[2] == ' ' || first_three_chars[2] == '\t')
			return (true);
	}
	else if (type_id == C || type_id == F)
	{
		if (first_three_chars[1] == ' ' || first_three_chars[1] == '\t')
			return (true);
	}
	return (false);
}

bool	valid_id(t_conf_file *conf_file, char *three_char, t_id id, size_t size)
{
	char	*type;
	bool	*type_id_exists;

	type = map_type_id_to_string(id);
	type_id_exists = map_type_id_to_bool_address(conf_file, id);
	if (!type)
		return (false);
	if (ft_strncmp(three_char, type, size) == 0
		&& followed_by_wsp(three_char, id))
	{
		if (!is_type_id_unique(conf_file, type_id_exists, type))
		{
			free(type);
			return (false);
		}
		*type_id_exists = (true);
		conf_file->current_id = id;
		free(type);
		return (true);
	}
	free(type);
	return (false);
}

bool	id_is_valid(t_conf_file *config_file, char *first_three_chars)
{
	if (valid_id(config_file, first_three_chars, NO, 2))
		return (true);
	if (valid_id(config_file, first_three_chars, SO, 2))
		return (true);
	if (valid_id(config_file, first_three_chars, EA, 2))
		return (true);
	if (valid_id(config_file, first_three_chars, WE, 2))
		return (true);
	if (valid_id(config_file, first_three_chars, C, 1))
		return (true);
	if (valid_id(config_file, first_three_chars, F, 1))
		return (true);
	config_file->error = WRONG_CONFIG_FILE_TYPE_ID;
	if (!config_file->duplicate_id)
		print_err_msg("Invalid type id", ": ", first_three_chars);
	return (false);
}

bool	parse_type_ids(t_conf_file *config_file)
{
	t_line	results;

	results = get_next_line(config_file->fd);
	while (results.current_line)
	{
		results.current_line = trim_begin(results);
		if (is_empty_line(config_file, &results))
			continue ;
		if (!parse_cur_line(config_file, results.current_line, &results))
			return (false);
		store_type_id_info(config_file, &results);
		free_pointer(&(results.current_line));
		results = get_next_line(config_file->fd);
		if (!store_map(config_file, &results))
			return (false);
	}
	free_pointer(&(results.remainder));
	if (!all_id_types_present(config_file))
	{
		config_file->error = NOT_ALL_TYPE_IDS_FOUND;
		print_err_msg("One or more type identifiers are missing", "", "");
		return (false);
	}
	return (true);
}
