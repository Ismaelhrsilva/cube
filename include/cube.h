/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:52:45 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/18 14:11:37 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "MLX42.h"
# include <stdint.h>

//# define S_W 1900 // screen width
# define S_W 1024 // screen width
//# define S_H 1000 // screen height
# define S_H 600 // screen height
# define TILE_SIZE 30 // tile size
//# define FOV 60 // field of view
#define FOV 60
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4	// player speed
//# define WALL_TEXT "textures/rock.png"
//# define WALL_TEXT "textures/rocket_up.png"
# define WALL_TEXT "textures/north.png"

# define NEGATIVE -1
# define POSITIVE 1

typedef struct s_map
{
	char			*north;	// north texture path
	char			*south;	// south texture path
	char			*west;	// west texture path
	char			*east;	// east texture path
	uint32_t		floor;	// floor hex color
	uint32_t		sky;	// sky hex color
	int32_t		width;		// map width
	int32_t		height;		// map height
	char			**map;	// map array
	int32_t		player[3];	// player position x, y and direction
}	t_map;

void	clear_map(t_map *map);	// clear structure t_map
t_map	*parser_map(char *map);	// parser file .cub and create t_map

typedef struct s_player //the player structure
{
	int32_t	x; // player x position in pixels
	int32_t	y; // player y position in pixels
	double	angle;	// player angle
	double	fov;	// field of view in radians
	int32_t	rot;	// rotation flag
	int32_t	l_r;	// left right flag
	int32_t	u_d;	// up down flag
}	t_player;

typedef struct s_ray	//the ray structure
{
	double	angle;	// ray angle
	double	distance;	// distance to the wall
	int		flag;		// flag for the wall
}	t_ray;

typedef struct s_data	//the data structure
{
	char	**map;	// the map
	int		p_x;		// player x position in the map
	int		p_y;		// player y position in the map
	int		width;		// map width
	int		height;		// map height
	int		size_minimap; // size of block minimap
	mlx_image_t		*image;	// image of minimap
	mlx_texture_t	*wall_text; // texture wall
	
	int	wall_height;
	int	wall_line_start_y;
	int	wall_line_end_y;
	int	texture_pos;
	int	texture_step;
	int	texture_x;
	int	point_x;

}	t_data;

typedef struct s_mlx	//the mlx structure
{
	mlx_image_t		*img;	// the image
	mlx_t			*mlx_p;	// the mlx pointer
	t_ray			*ray;	// the ray structure
	t_data			*dt;	// the data structure
	t_player		*player;	// the player structure
}	t_mlx;

//File init
void	game_loop(void *ml);
void init_the_player(t_mlx mlx);
void	start_the_game(t_data *dt);

//File movement
void	ft_reles(mlx_key_data_t keydata, t_mlx *mlx);
void mlx_key(mlx_key_data_t keydata, void *ml);
void	hook(t_mlx *mlx);
void	rotation_move(t_mlx *mlx, int32_t direction);

//File raycast 
int	unit_circle(float angle, char c);
int	inter_check(float angle, float *inter, float *step, int is_horizon);
int	wall_hit(float x, float y, t_mlx *mlx);
float	get_h_inter(t_mlx *mlx, float angl);
float	get_v_inter(t_mlx *mlx, float angl);
void	cast_rays(t_mlx *mlx);

//File utils
void	ft_exit(t_mlx *mlx);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//File wall rend
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
float	nor_angle(float angle);
void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix);
int	get_color(t_mlx *mlx, int flag);
//void	draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix);
void	render_wall(t_mlx *mlx, int ray);

//File mouse
void ft_mouse(double xpos, double ypos, void *ml);

//File minimap
void	ft_minimap(t_mlx *mlx);

//File Animation
mlx_texture_t *construct_texture(t_mlx *mlx, char *png);

#endif
