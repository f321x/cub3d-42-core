/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:47:40 by ***REMOVED***             #+#    #+#             */
/*   Updated: 2024/02/12 19:52:24 by ***REMOVED***            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_ray {
	double
	double
	double
} t_ray;

// The ray starts at the position of the player (posX, posY).

// cameraX is the x-coordinate on the camera plane that the current x-coordinate of the screen represents, done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1. Out of this, the direction of the ray can be calculated as was explained earlier: as the sum of the direction vector, and a part of the plane vector. This has to be done both for the x and y coordinate of the vector (since adding two vectors is adding their x-coordinates, and adding their y-coordinates).

//     for(int x = 0; x < w; x++)
//     {
//       //calculate ray position and direction
//       double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
//       double rayDirX = dirX + planeX * cameraX;
//       double rayDirY = dirY + planeY * cameraX;

// Calculate each ray for a single player position and direction
// The ray dir is calculated for each x line of the frame

t_ray	calc_ray_direction(double ) {

}

// draft, not final
void calculate_ray(int map[][], int pos_xy[2], int dir_v_xy[2])
{


	return ;
}
