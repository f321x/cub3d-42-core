/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:43:05 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/11 14:54:45 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_wsp(char *line)
{
	char	*temp;

	temp = line;
	while (*temp != '\n')
	{
		if (*temp == ' ' || *temp == '\t')
		{
			temp++;
			continue ;
		}
		temp = ft_strdup(temp);
		return (temp);
	}
	temp = ft_strdup(temp);
	return (temp);
}

char	*trim_begin(t_line results)
{
	char	*temp;

	temp = results.current_line;
	results.current_line = skip_wsp(results.current_line);
	free(temp);
	return (results.current_line);
}

char	*trime_new_line_char(char *line)
{
	char	*temp;

	temp = line;
	if (*temp == '\n')
		temp++;
	temp = ft_strdup(temp);
	return (temp);
}

char	*move_to_first_wsp(t_line *results)
{
	char	*info;

	info = results->current_line;
	while (*info)
	{
		if (*info == ' ' || *info == '\t')
			break ;
		info++;
	}
	return (info);
}

char	*trim_final_new_line_char(char *info)
{
	if (ft_strlen(info) && (info[ft_strlen(info) - 1] == '\n'))
		info = ft_substr(info, 0, ft_strlen(info) - 1);
	else
		info = ft_strdup(info);
	return (info);
}
