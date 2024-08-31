/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:52:45 by ishenriq          #+#    #+#             */
/*   Updated: 2024/08/31 19:42:10 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
# include "../lib/libft/gnl/get_next_line.h"

# define WIDTH 1900
# define HEIGHT 1000
# define TILE_SIZE 30
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4


typedef struct s_player
{
	int	player_x;
	int	player_y;
	double	angle;
	float	fov_rd;
	int	left_right;
	int	up_down;
}	t_player;

typedef struct s_ray
{
	double	ray_angle;
	double	distance;
	int	flag;
}	t_ray;

typedef struct s_data
{
	char **map2d;
	int	player_x;
	int	player_y;
	int width_map;
	int height_map;
}	t_data;

typedef struct s_cube
{
	mlx_image_t	*img;
	mlx_t	*init;
	t_player	*player;
	t_ray	*ray;
	t_data	*data;
}	t_cube;

#endif
