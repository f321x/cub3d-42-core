/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:35:08 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/09 14:03:06 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum e_type_id
{
	NO = 1,
	SO,
	WE,
	EA,
	F,
	C
}	t_id;

typedef enum e_error
{
	DEFAULT = -1,
	ONE_ARGUMENT_NEEDED = 1,
	NO_FILE_OR_DIRECTORY,
	WRONG_CONFIG_FILE_TYPE_ID,
	INAVLID_CONFIG_FILE_EXTENSION,
	NOT_ALL_TYPE_IDS_FOUND,
}	t_err;

typedef struct s_rgb
{
	unsigned short int	r;
	unsigned short int	g;
	unsigned short int	b;
}	t_rgb;

typedef struct s_config_file
{
	char			*conf_file_name;
	int				fd;
	bool			no_exist;
	bool			so_exist;
	bool			we_exist;
	bool			ea_exist;
	bool			f_exist;
	bool			c_exist;
	bool			duplicate_id;
	bool			all_ids_found;
	char			*no_info;
	char			*so_info;
	char			*we_info;
	char			*ea_info;
	char			*f_info;
	char			*c_info;
	t_rgb			f_color;
	t_rgb			c_color;
	t_id			current_id;
	t_err			error;
}	t_conf_file;

// parsing_main.c
bool	parse_ids_and_map(t_conf_file *config_file);
bool	parse_config_file(int argc, char **argv, t_conf_file *config_file);

// print_error_message.c
void	print_err_msg(char *message1, char *message2, char *message3);

// free.c
void	free_config_file_members(t_conf_file *const config_file);
void	free_double_pointer(char **p);
void	free_pointer(char **ptr);

// atoi.c
bool	atoint(const char *str, int *color);

// get_config_file_members.c
char	**map_id_to_info_str_address(t_conf_file *config_file, t_id type_id);
t_rgb	*map_type_id_to_rgb_address(t_conf_file *config_file, t_id type_id);
bool	*map_type_id_to_bool_address(t_conf_file *config_file, t_id type_id);
char	*map_type_id_to_string(t_id type_id);

// parse_colors.c
bool	is_color_valid(t_conf_file *config_file, t_line *results);

// type_id_info.c
char	*get_info(t_line *results);
void	store_type_id_info(t_conf_file *config_file, t_line *results);
void	store_colors(t_conf_file *config_file, int *colors);

// trim.c
char	*skip_wsp(char *line);
char	*trime_new_line_char(char *line);
char	*move_to_first_wsp(t_line *results);
char	*trim_final_new_line_char(char *info);
char	*trim_begin(t_line results);

// parse_type_ids_1.c
bool	parse_type_ids(t_conf_file *config_file);

// parse_type_ids_2.c
bool	id_is_valid(t_conf_file *config_file, char *first_three_chars);

// open_config_file.c
bool	open_config_file(t_conf_file *config_file);
