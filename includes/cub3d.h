/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:21 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/10 07:53:07 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// check when parsing if map is too big, throw error.
#define MAX_COLUMN_NUM	100
#define MAX_ROW_NUM		3

typedef enum e_field {
	EMPTY = 0,
	WALL = 1,
	NORTH = 2,
	SOUTH = 3,
	EAST = 4,
	WEST = 5,
	WSP = 6,
	NEW_LINE = 7,
	NONE = 8, 
	INIT = 9,
} t_field;

typedef struct s_map {
	size_t	rows_num;
	size_t	columns_per_row[MAX_ROW_NUM];
	size_t	max_columns_num;
	t_field	map_plan[MAX_ROW_NUM][MAX_COLUMN_NUM];
}	t_map;
