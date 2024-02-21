/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_file_members.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:21:45 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/21 12:12:18 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**map_id_to_info_str_address(t_conf_file *config_file, t_id id)
{
	char	**info_pointer;

	info_pointer = NULL;
	if (id == NO)
		info_pointer = &(config_file->no_info);
	else if (id == SO)
		info_pointer = &(config_file->so_info);
	else if (id == EA)
		info_pointer = &(config_file->ea_info);
	else if (id == WE)
		info_pointer = &(config_file->we_info);
	else if (id == C)
		info_pointer = &(config_file->c_info);
	else if (id == F)
		info_pointer = &(config_file->f_info);
	return (info_pointer);
}

int32_t	*map_type_id_to_rgb_address(t_conf_file *config_file, t_id id)
{
	if (id == C)
		return (&(config_file->c_color));
	else if (id == F)
		return (&(config_file->f_color));
	return (NULL);
}

bool	*map_type_id_to_bool_address(t_conf_file *config_file, t_id id)
{
	bool	*type_id_exists;

	type_id_exists = NULL;
	if (id == NO)
		type_id_exists = &(config_file->no_exist);
	else if (id == SO)
		type_id_exists = &(config_file->so_exist);
	else if (id == EA)
		type_id_exists = &(config_file->ea_exist);
	else if (id == WE)
		type_id_exists = &(config_file->we_exist);
	else if (id == C)
		type_id_exists = &(config_file->c_exist);
	else if (id == F)
		type_id_exists = &(config_file->f_exist);
	return (type_id_exists);
}

char	*map_type_id_to_string(t_id type_id)
{
	char	*type;

	type = NULL;
	if (type_id == NO)
		type = ft_strdup("NO");
	else if (type_id == SO)
		type = ft_strdup("SO");
	else if (type_id == EA)
		type = ft_strdup("EA");
	else if (type_id == WE)
		type = ft_strdup("WE");
	else if (type_id == C)
		type = ft_strdup("C");
	else if (type_id == F)
		type = ft_strdup("F");
	return (type);
}
