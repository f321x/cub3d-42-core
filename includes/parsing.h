/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:35:08 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2024/03/20 11:03:40 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "get_next_line.h"
#include "cub3d.h"

typedef struct s_map	t_map;
typedef char (*map_ptr)[1000][1000];
typedef struct s_window_frame t_window_frame;

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
	INVALID_TEXTURE_DIR,
	INVALID_TEXTURE_EXTENSION,
	INVALID_MAP_CHAR,
	MAP_TOO_BIG,
	NO_PLAYER,
	MULTI_PLAYER,
	MAP_NOT_SURROUNDED_BY_WALLS,
}	t_err;

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
	int32_t			f_color;
	int32_t			c_color;
	t_id			current_id;
	t_err			error;
	t_map			*map;
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
int32_t	*map_type_id_to_rgb_address(t_conf_file *config_file, t_id type_id);
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
bool	is_empty_line(const t_conf_file *const config_file, t_line *results);
bool	parse_cur_line(t_conf_file *conf_file,
			char *trim_line, t_line *results);
bool	store_map(t_conf_file *config_file, t_line *results);
bool	all_id_types_present(t_conf_file *conf_file);

// parse_type_ids_2.c
bool	id_is_valid(t_conf_file *config_file, char *first_three_chars);
bool	parse_type_ids(t_conf_file *config_file);

bool	copy_map(t_conf_file *conf_file, t_line *result);
bool	parse_map(t_conf_file *conf_file);

// parse_map.c
map_ptr	duplicate_map_plan(t_conf_file const *conf_file, map_ptr map_copy_ptr);
void	check_next_coord(t_conf_file *conf_file, int x, int y);
bool	is_only_one_player(t_conf_file *conf_file, size_t i, size_t j);
bool	search_for_player(t_conf_file *conf_file, size_t i, size_t j);

// copy_map.c
void	init_map_plan(char (*map_plan)[MAX_COLUMN_NUM]);
bool	copy_char_by_char(t_conf_file *conf_file, char *current_line);
size_t	get_row_num(t_conf_file *conf_file);

void	print_map_plan(t_conf_file const *conf_file,
			char map[MAX_ROW_NUM][MAX_COLUMN_NUM]);
void	print_test(t_conf_file config_file);

// open_config_file.c
bool	open_config_file(t_conf_file *config_file);

// check_textures.c
bool	textures_extension_valid(t_window_frame gui);
bool	textures_dirs_are_valid(t_window_frame gui);
