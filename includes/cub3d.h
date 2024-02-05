/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:21 by fbock             #+#    #+#             */
/*   Updated: 2024/02/05 12:12:51 by fbock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// check when parsing if map is too big, throw error.
#define MAX_MAP_X_WIDTH 	1000
#define MAX_MAP_Y_HEIGHT	1000

typedef enum e_field {
	EMPTY,
	WALL,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NONE  // initialize array with none
} t_field;

typedef struct s_map {
	size_t	amount_y_rows;		// amount of actual used y rows
	size_t	amount_x_rows[MAX_MAP_Y_HEIGHT];  // stores the x length of the current y row
	t_field	map[MAX_MAP_Y_HEIGHT][MAX_MAP_X_WIDTH]  // contains the kind of map element (enum) at Y/X
}	t_map;
