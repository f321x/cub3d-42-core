/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:21 by fbock             #+#    #+#             */
/*   Updated: 2024/02/11 15:40:40 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "MLX42.h"
# include "libft.h"
# include "get_next_line.h"

// Initial window size
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024

#define MAX_COLUMN_NUM	1000
#define MAX_ROW_NUM		1000

# include "parsing.h"

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

typedef struct s_window_frame {
	mlx_t			*window;
	mlx_image_t		*frame;
	mlx_image_t		*buffer;
	double			mouse_x;
	double			mouse_y;
}	t_window_frame;

// mlx_handlers/handlers_main.c
void	init_hooks(t_window_frame *gui);
void	init_gui(t_window_frame *gui);
void	cleanup(t_window_frame *gui);

// mlx_handlers/input_hooks.c
void	resize_function(int32_t width, int32_t height, void *param);
void	scrolling_handler(double xdelta, double ydelta, void *param);
void	mouse_position_handler(double xpos, double ypos, void *param);
void	key_handler(mlx_key_data_t keydata, void *param);
