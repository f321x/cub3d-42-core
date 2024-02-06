/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:21 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/06 15:53:09 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "MLX42.h"

// Initial window size
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024

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

typedef struct s_window_frame {
	mlx_t			*window;
	mlx_image_t		*frame;
	mlx_image_t		*buffer;
	double			mouse_x;
	double			mouse_y;
}	t_window_frame;
