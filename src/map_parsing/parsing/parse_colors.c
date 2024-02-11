/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:38:51 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/11 14:54:31 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_only_three_values(char *color_info)
{
	int	i;

	i = 0;
	while (*color_info && i < 3)
	{
		if (*color_info == ',')
			i++;
		color_info++;
	}
	if (i > 2)
		return (false);
	return (true);
}

int	get_size(char	**p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		i++;
	}
	return (i);
}

bool	is_valid_rgb_range(t_conf_file *config_file, char **rgb)
{
	int	i;
	int	colors[3];

	ft_bzero(colors, sizeof(colors));
	i = 0;
	while (rgb[i])
	{
		if (!atoint(rgb[i], &colors[i]))
			return (false);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (colors[i] < 0 || colors[i] > 255)
			return (false);
		i++;
	}
	store_colors(config_file, colors);
	return (true);
}

bool	parse_color(t_conf_file *config_file, char *color_info)
{
	char	**rgb;
	int		size;

	if (!is_only_three_values(color_info))
		return (false);
	rgb = ft_split(color_info, ',');
	if (!rgb)
		return (false);
	size = get_size(rgb);
	if (size != 3)
	{
		free_double_pointer(rgb);
		return (false);
	}
	if (!is_valid_rgb_range(config_file, rgb))
	{
		free_double_pointer(rgb);
		return (false);
	}
	free_double_pointer(rgb);
	return (true);
}

bool	is_color_valid(t_conf_file *config_file, t_line *results)
{
	char	*color_info;
	char	*temp;

	color_info = get_info(results);
	temp = color_info;
	color_info = trim_final_new_line_char(color_info);
	free(temp);
	if (!parse_color(config_file, color_info))
	{
		print_err_msg("Color is not a valid RGB color", ": ", color_info);
		free(color_info);
		return (false);
	}
	free(color_info);
	return (true);
}
