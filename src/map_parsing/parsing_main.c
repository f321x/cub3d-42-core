/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:50:34 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2024/02/06 14:15:39 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	print_test(t_conf_file config_file)
{
	printf("config_file.NO_info = %s\n", config_file.no_info);
	printf("config_file.SO_info = %s\n", config_file.so_info);
	printf("config_file.EA_info = %s\n", config_file.ea_info);
	printf("config_file.WE_info = %s\n", config_file.we_info);
	printf("config_file.C_info = %s\n", config_file.c_info);
	printf("config_file.F_info %s\n", config_file.f_info);
	printf("config_file.NO_exist = %d\n", config_file.no_exist);
	printf("config_file.SO_exist = %d\n", config_file.so_exist);
	printf("config_file.EA_exist = %d\n", config_file.ea_exist);
	printf("config_file.WE_exist = %d\n", config_file.we_exist);
	printf("config_file.C_exist = %d\n", config_file.c_exist);
	printf("config_file.F_exist = %d\n", config_file.f_exist);
	printf("config_file.all_type_id_found = %d\n", config_file.all_ids_found);
	printf("config_file.current_type_id = %d\n", config_file.current_id);
	printf("C_colors.r = %d\n", config_file.c_color.r);
	printf("C_colors.g = %d\n", config_file.c_color.g);
	printf("C_colors.b = %d\n", config_file.c_color.b);
	printf("F_colors.r = %d\n", config_file.f_color.r);
	printf("F_colors.g = %d\n", config_file.f_color.g);
	printf("F_colors.b = %d\n", config_file.f_color.b);
	return ;
}

bool	parse_ids_and_map(t_conf_file *config_file)
{
	if (!open_config_file(config_file))
		return (false);
	if (!parse_type_ids(config_file))
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
	print_test(*config_file);
	return (true);
}
