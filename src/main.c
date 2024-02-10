/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:07 by fbock             #+#    #+#             */
/*   Updated: 2024/02/10 09:15:57 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_map_plan(t_conf_file const *conf_file)
{
	size_t	i;
	size_t	j;
	i = 0;
	while (i < conf_file->map->rows_num)
	{
		j = 0;
		while (j < conf_file->map->columns_per_row[i])
		{
			printf("%d", conf_file->map->map_plan[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_conf_file	config_file;

	if (!parse_config_file(argc, argv, &config_file))
		return (config_file.error);
	print_test(config_file);
	print_map_plan(&config_file);
	free_config_file_members(&config_file);

	return (0);
}
