/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:32:42 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2024/02/21 12:46:40 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map_number_of_columns_per_row(t_conf_file config_file)
{
	int	i;

	i = 0;
	while (i < MAX_ROW_NUM)
	{
		printf("columns_per_row[%d]= %lu\n", i, config_file.map->columns_per_row[i]);
		i++;
	}

}

void	print_test(t_conf_file config_file)
{
	printf("rows = %lu\n", config_file.map->rows_num);
	printf("max_columns_num = %lu\n", config_file.map->max_columns_num);
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
	// printf("C_colors.r = %d\n", config_file.c_color.r);
	// printf("C_colors.g = %d\n", config_file.c_color.g);
	// printf("C_colors.b = %d\n", config_file.c_color.b);
	// printf("F_colors.r = %d\n", config_file.f_color.r);
	// printf("F_colors.g = %d\n", config_file.f_color.g);
	// printf("F_colors.b = %d\n", config_file.f_color.b);
	printf("------------------------------------------------\n");
	return ;
}

void	print_map_plan(t_conf_file const *conf_file, char map[MAX_ROW_NUM][MAX_COLUMN_NUM])
{
	size_t	i;
	size_t	j;
	i = 0;
	while (i < conf_file->map->rows_num)
	{
		j = 0;
		while (j < conf_file->map->columns_per_row[i])
		{
			printf("%c", map[i][j]);
			j++;
		}
		i++;
	}
	printf("\n");
	printf("------------------------------------------------\n");
	return ;
}
