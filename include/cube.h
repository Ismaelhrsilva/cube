/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:52:45 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/28 12:09:49 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "MLX42.h"
# include <stdint.h>

# define S_W 1024
# define S_H 768
# define TILE_SIZE 60
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define PLAYER_SIZE 3
# define ANIMATION1 "textures/weapon1.png"
# define ANIMATION2 "textures/weapon2.png"
# define WALL_TEXT "textures/north.png"
# define DOOR "textures/rocket_up.png"

# define NEGATIVE -1
# define POSITIVE 1

typedef struct s_map
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	uint32_t	floor;
	uint32_t	sky;
	int32_t		width;
	int32_t		height;
	char		**map;
	int32_t		player[3];
}	t_map;

void	clear_map(t_map *map);
t_map	*parser_map(char *map);

typedef struct s_player
{
	int32_t	x;
	int32_t	y;
	double	angle;
	double	fov;
	int32_t	rot;
	int32_t	l_r;
	int32_t	u_d;
	_Bool	run;
}	t_player;

typedef struct s_ray
{
	int		index;
	double	angle;
	double	distance;
	float	distance_x;
	float	distance_y;
	double	x;
	double	y;
	double	vx;
	double	vy;
	int		flag;
}	t_ray;

typedef struct s_minimap
{
	mlx_image_t	*img;
	int32_t		size;
}	t_minimap;

typedef struct s_texture
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_texture_t	*door;
}	t_texture;

typedef struct s_data
{
	char			**map;
	int				p_x;
	int				p_y;
	int				width;
	int				height;
	uint32_t		floor;
	uint32_t		sky;
	int				size_minimap;
	mlx_image_t		*image;
	mlx_texture_t	*wall_text;
	int				wall_height;
	int				wall_line_start_y;
	int				wall_line_end_y;
	int				texture_pos;
	int				texture_step;
	int				texture_x;
	int				point_x;
	mlx_texture_t	*texture1;
	mlx_texture_t	*texture2;
	mlx_image_t		*animation1;
	uint8_t			frame;
	double			time;
	mlx_image_t		*animation2;
	int				door_closed;
}	t_data;

typedef struct s_mlx
{
	mlx_image_t		*img;
	mlx_t			*mlx_p;
	t_ray			*ray;
	t_data			*dt;
	t_player		*player;
	t_minimap		*minimap;
	t_texture		*texture;
}	t_mlx;

//File init
void	game_loop(void *ml);
void	init_the_player(t_mlx mlx);
void	start_the_game(t_data *dt, t_map *map);

//File movement
void	ft_reles(mlx_key_data_t keydata, t_mlx *mlx);
void	mlx_key(mlx_key_data_t keydata, void *ml);
void	hook(t_mlx *mlx);
void	rotation_move(t_mlx *mlx, int32_t direction);

//File raycast
int		unit_circle(float angle, char c);
int		inter_check(float angle, float *inter, float *step, int is_horizon);
int		wall_hit(float x, float y, t_mlx *mlx);
float	get_h_inter(t_mlx *mlx, float angl);
float	get_v_inter(t_mlx *mlx, float angl);
void	cast_rays(t_mlx *mlx);

//File utils
void	ft_exit(t_mlx *mlx);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
float	pytheorem(float a, float b);
int		horizontal_unit_circle(float angle);
int		vertical_unit_circle(float angle);

//File utils 2
void	put_pixel(t_mlx *mlx, int x, int y, int color);
float	nor_angle(float angle);
void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix);

//File wall rend
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		get_color(t_mlx *mlx, int flag);

//void draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix);
void	render_wall(t_mlx *mlx, int ray);

//File mouse
void	ft_mouse(double xpos, double ypos, void *ml);

//File minimap
void	ft_minimap(t_mlx *mlx);

//File Animation
mlx_texture_t	*construct_texture(t_mlx *mlx, char *png);
void	ft_animation(t_mlx *mlx);
void	ft_init_animation(t_mlx *mlx);

//File open_door
void	ft_open_door(t_mlx *mlx);

#endif
