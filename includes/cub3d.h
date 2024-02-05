/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:21 by fbock             #+#    #+#             */
/*   Updated: 2024/02/05 12:07:14 by fbock            ###   ########.fr       */
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
	size_t	size_x;
	size_t	size_y;
	t_field	map[MAX_MAP_Y_HEIGHT][MAX_MAP_X_WIDTH]  //
}	t_map;
