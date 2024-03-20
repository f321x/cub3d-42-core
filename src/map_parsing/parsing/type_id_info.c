/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_id_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:47:05 by fahmadia          #+#    #+#             */
/*   Updated: 2024/03/19 12:12:44 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_info(t_line *results)
{
	char	*info;

	info = move_to_first_wsp(results);
	while (*info == ' ' || *info == '\t' || *info == '\n')
		info++;
	info = ft_strdup(info);
	return (info);
}

void	store_type_id_info(t_conf_file *conf_file, t_line *results)
{
	char	*info;
	char	*temp;
	char	**cur_info_ptr;

	info = get_info(results);
	temp = info;
	info = trim_final_new_line_char(info);
	free(temp);
	cur_info_ptr = map_id_to_info_str_address(conf_file, conf_file->current_id);
	*cur_info_ptr = ft_strdup(info);
	free_pointer(&info);
	info = NULL;
	return ;
}

void	store_colors(t_conf_file *config_file, int *colors)
{
	int32_t	*rgbs;

	rgbs = map_type_id_to_rgb_address(config_file, config_file->current_id);
	if (!rgbs)
		return ;
	*rgbs = convert_rgba(colors[0], colors[1], colors[2], 255);
}
