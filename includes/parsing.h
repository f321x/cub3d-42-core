/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:35:08 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2024/02/06 13:03:16 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"

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

bool	parse_ids_and_map(t_conf_file *config_file);
void	print_err_msg(char *message1, char *message2, char *message3);
void	free_config_file_members(t_conf_file *const config_file);
void	free_double_pointer(char **p);
bool	atoint(const char *str, int *color);
void	free_config_file_members(t_conf_file *const config_file);
void	free_pointer(char **ptr);
char	**map_id_to_info_str_address(t_conf_file *config_file, t_id type_id);
t_rgb	*map_type_id_to_rgb_address(t_conf_file *config_file, t_id type_id);
bool	*map_type_id_to_bool_address(t_conf_file *config_file, t_id type_id);
char	*map_type_id_to_string(t_id type_id);
bool	is_color_valid(t_conf_file *config_file, t_line *results);
char	*get_info(t_line *results);
char	*skip_wsp(char *line);
char	*trime_new_line_char(char *line);
char	*move_to_first_wsp(t_line *results);
char	*trim_final_new_line_char(char *info);
void	store_type_id_info(t_conf_file *config_file, t_line *results);
void	store_colors(t_conf_file *config_file, int *colors);
char	*trim_begin(t_line results);
bool	parse_type_ids(t_conf_file *config_file);
bool	open_config_file(t_conf_file *config_file);
bool	id_is_valid(t_conf_file *config_file, char *first_three_chars);
bool	parse_config_file(int argc, char **argv, t_conf_file *config_file);

#endif