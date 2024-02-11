/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:21 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/11 13:37:03 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COLUMN_NUM	1000
#define MAX_ROW_NUM		1000

typedef enum e_field {
	EMPTY = '0',
	SPACE = ' ',
	WALL = '1',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	NEW_LINE = '\n',
	INIT = '-',
} t_field;

typedef struct s_map {
	size_t	rows_num;
	size_t	columns_per_row[MAX_ROW_NUM];
	size_t	max_columns_num;
	char	map_plan[MAX_ROW_NUM][MAX_COLUMN_NUM];
	char	map_copy[MAX_ROW_NUM][MAX_COLUMN_NUM];
	size_t	player_coord[2];
	bool	is_player;
	bool	is_map_valid;
}	t_map;
