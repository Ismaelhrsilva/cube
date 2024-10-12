/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:52:45 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/12 10:48:47 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "MLX42.h"
# include <stdint.h>

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define TILE_SIZE 60
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SIZE 3
# define PLAYER_SPEED 3

# define NEGATIVE -1
# define POSITIVE 1

# define NORTH 1.5
# define EAST 0
# define SOUTH 0.5
# define WEST 1

enum e_color {
	A = 0xFF000000,
	R = 0x00FF0000,
	G = 0x0000FF00,
	B = 0x000000FF
};

typedef struct s_map
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	uint32_t	floor;
	uint32_t	ceilling;
	int32_t		player[3];
	int32_t		width;
	int32_t		height;
	char		**map;
}	t_map;

typedef struct s_player
{
	int32_t	x;
	int32_t	y;
	double	angle;
	double	fov;
}	t_player;

typedef struct s_ray
{
	int32_t	index;
	double	angle;
	double	distance;
	double	x;
	double	y;
}	t_ray;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}	t_texture;

typedef struct s_data
{
	char			**map;
	int				x;
	int				y;
	int				width;
	int				height;
	uint32_t		floor;
	uint32_t		ceilling;
	t_map			*parser;
}	t_data;

typedef struct s_mlx
{
	mlx_t		*p;
	mlx_image_t	*img;
	t_ray		*ray;
	t_data		*data;
	t_player	*player;
	t_texture	*texture;
}	t_mlx;

void	start(t_data *data);
void	key(mlx_key_data_t keydata, void *ml);
void	hook(t_mlx *mlx);
void	rotation_move(t_mlx *mlx, int32_t direction);
void	raycast(t_mlx *mlx);
void	gameover(t_mlx *mlx, char *message, uint8_t status);
t_map	*parser_map(char *path);
void	clear_map(t_map *map);

#endif
