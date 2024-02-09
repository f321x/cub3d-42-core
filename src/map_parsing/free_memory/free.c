/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:39:10 by fahmadia          #+#    #+#             */
/*   Updated: 2024/02/06 13:11:20 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_pointer(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_double_pointer(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		p[i] = NULL;
		i++;
	}
	free(p);
	return ;
}

void	free_config_file_members(t_conf_file *const config_file)
{
	free_pointer(&(config_file->no_info));
	free_pointer(&(config_file->so_info));
	free_pointer(&(config_file->ea_info));
	free_pointer(&(config_file->we_info));
	free_pointer(&(config_file->c_info));
	free_pointer(&(config_file->f_info));
}
