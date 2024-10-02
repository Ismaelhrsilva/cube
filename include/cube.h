/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:52:45 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/01 16:57:04 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "MLX42.h"
# include <stdint.h>

# define S_W 1024
# define S_H 768
# define TILE_SIZE 60 // tile size
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define PLAYER_SIZE 3

# define WALL_TEXT "textures/north.png"

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
	_Bool	run;
}	t_player;

typedef struct s_ray	//the ray structure
{
	int32_t	index;
	double	angle;
	double	distance;
	double	x;
	double	y;
	_Bool	door;
}	t_ray;

typedef struct s_minimap
{
	mlx_image_t	*img;
	int32_t		size;
} t_minimap;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*door;
}	t_texture;

typedef struct s_data	//the data structure
{
	char	**map;	// the map
	int		p_x;		// player x position in the map
	int		p_y;		// player y position in the map
	int		width;		// map width
	int		height;		// map height
	uint32_t	floor;
	uint32_t	ceilling;
	int		size_minimap; // size of block minimap
	mlx_image_t		*image;	// image of minimap
	mlx_texture_t	*wall_text; // texture wall
	
	mlx_texture_t	*texture1;
	mlx_image_t		*animation1;
	uint8_t			frame;
	double			time;
}	t_data;

typedef struct s_mlx
{
	mlx_t		*p;
	mlx_image_t	*img;
	t_ray		*ray;
	t_data		*data;
	t_player	*player;
	t_minimap	*minimap;
	t_texture	*texture;
}	t_mlx;

void	start_the_game(t_data *dt, t_map *map);

//File movement
void mlx_key(mlx_key_data_t keydata, void *ml);
void	hook(t_mlx *mlx);
void	rotation_move(t_mlx *mlx, int32_t direction);

//File raycast 
int	horizontal_unit_circle(float angle);
int	vertical_unit_circle(float angle);
int	wall_hit(float x, float y, t_mlx *mlx);
void	cast_rays(t_mlx *mlx);

//File utils
void	ft_exit(t_mlx *mlx);

//File wall rend
float	normalize(float angle);
void	render_wall(t_mlx *mlx, int ray);

//File mouse
void ft_mouse(double xpos, double ypos, void *ml);

//File minimap
void	ft_minimap(t_mlx *mlx);

//File Animation
mlx_texture_t *construct_texture(t_mlx *mlx, char *png);
void	ft_animation(t_mlx *mlx);
void	ft_init_animation(t_mlx *mlx);

//File open_door
void	ft_open_door(t_mlx *mlx);

#endif
