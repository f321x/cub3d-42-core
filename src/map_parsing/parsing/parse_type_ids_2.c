/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_ids_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:00:05 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/06 11:02:26 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
