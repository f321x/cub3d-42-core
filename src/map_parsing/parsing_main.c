/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:50:34 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/11 15:19:42 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config_file(t_conf_file *config_file, char *config_file_name)
{
	ft_memset(config_file, 0, sizeof(*config_file));
	config_file->conf_file_name = config_file_name;
	config_file->fd = -1;
	config_file->error = DEFAULT;
}

bool	is_file_extension_valid(t_conf_file *conf_file)
{
	char	*file_name;
	size_t	length;

	if (!conf_file || !(conf_file->conf_file_name))
		return (false);
	file_name = conf_file->conf_file_name;
	length = ft_strlen(file_name);
	if (length >= 4)
		file_name += length - 4;
	if ((int)length - 4 < 0
		|| ft_strncmp(file_name, ".cub", ft_strlen(file_name)) != 0)
	{
		print_err_msg("Invalid config file extension", ": ", file_name);
		conf_file->error = INAVLID_CONFIG_FILE_EXTENSION;
		return (false);
	}
	return (true);
}

bool	parse_ids_and_map(t_conf_file *config_file)
{
	if (!open_config_file(config_file))
		return (false);
	if (!parse_type_ids(config_file))
		return (false);
	if (!parse_map(config_file))
		return (false);
	close(config_file->fd);
	return (true);
}

bool	parse_config_file(int argc, char **argv, t_conf_file *config_file)
{
	if (argc != 2)
	{
		config_file->error = ONE_ARGUMENT_NEEDED;
		print_err_msg("One argument is needed", ": ", "Config File Name");
		return (false);
	}
	init_config_file(config_file, argv[1]);
	if (!is_file_extension_valid(config_file))
		return (false);
	if (!parse_ids_and_map(config_file))
	{
		free_config_file_members(config_file);
		return (false);
	}
	return (true);
}
