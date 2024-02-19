/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:38:21 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/19 13:16:14 by ***REMOVED***            ###   ########.fr       */
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
	char	map_plan[MAX_ROW_NUM][MAX_COLUMN_NUM];  // shouldn't this be defined as t_field enum instead of char?
	char	map_copy[MAX_ROW_NUM][MAX_COLUMN_NUM];
	size_t	player_coord[2];
	bool	is_player;
	bool	is_map_valid;
}	t_map;

typedef struct s_window_frame {
	mlx_t			*window;
	mlx_image_t		*frame;
	mlx_image_t		*buffer;
	int32_t			width;
	int32_t			height;
	double			mouse_x;
	double			mouse_y;
}	t_window_frame;

typedef struct s_wall {
	int	wall_top_pixel;
	int	wall_bottom_pixel;
	int	direction;
}	t_wall;

typedef struct s_ray {
	double	camera_x_point;
	double	ray_dir_x;
	double	ray_dir_y;
	double 	delta_dist_x;
	double 	delta_dist_y;
	double	init_dist_x;
	double	init_dist_y;
	int		step_dir_x;
	int		step_dir_y;
	int		hit_side_bin;
	int		hit_side_color;
	double	perpendicular_wall_to_cp_distance;
} t_ray;

typedef struct s_player_pos {
	double	player_pos_x;
	double	player_pos_y;
	double	player_dir_x;
	double	player_dir_y;
	int		map_x;
	int		map_y;
}	t_player_pos;

// mlx_handlers/handlers_main.c
void	init_hooks(t_window_frame *gui);
void	init_gui(t_window_frame *gui);
void	cleanup(t_window_frame *gui);

// mlx_handlers/input_hooks.c
void	resize_function(int32_t width, int32_t height, void *param);
void	scrolling_handler(double xdelta, double ydelta, void *param);
void	mouse_position_handler(double xpos, double ypos, void *param);
void	key_handler(mlx_key_data_t keydata, void *param);

// raycasting_main.c
t_wall	*raycast_whole_frame(int frame_width, int frame_height, t_player_pos player, t_map parsed_map);
t_wall	calculate_wall_height(t_ray *current_ray, int frame_height);
void	dist_from_hitpt_to_camera_plane(t_ray *ray,	t_player_pos *pl);
void	dda(t_map *map, t_ray *ray, t_player_pos *pl);
void	calculate_initial_step_and_dist(t_ray *ray, t_player_pos *p);
t_ray	calc_ray_direction(int current_x, int width, t_player_pos p);

// drawing_main.c
void	draw_a_cast(t_window_frame *gui, t_map map, t_player_pos p);
