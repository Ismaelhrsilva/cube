/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:52:45 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/06 20:35:27 by ishenriq         ###   ########.fr       */
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


# define S_W 1900 // screen width
# define S_H 1000 // screen height
# define TILE_SIZE 30 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4	// player speed

typedef struct s_player //the player structure
{
	int		plyr_x; // player x position in pixels
	int		plyr_y; // player y position in pixels
	double	angle;	// player angle
	float	fov_rd;	// field of view in radians
	int		rot;	// rotation flag
	int		l_r;	// left right flag
	int		u_d;	// up down flag
}	t_player;

typedef struct s_ray	//the ray structure
{
	double	ray_ngl;	// ray angle
	double	distance;	// distance to the wall
	int		flag;		// flag for the wall
}	t_ray;

typedef struct s_data	//the data structure
{
	char	**map2d;	// the map
	int		p_x;		// player x position in the map
	int		p_y;		// player y position in the map
	int		w_map;		// map width
	int		h_map;		// map height
	int		len;		// map block len 
	int		size_minimap;
	int		minimap_turn;
}	t_data;

typedef struct s_mlx	//the mlx structure
{
	mlx_image_t		*img;	// the image
	mlx_t			*mlx_p;	// the mlx pointer
	t_ray			*ray;	// the ray structure
	t_data			*dt;	// the data structure
	t_player		*ply;	// the player structure
}	t_mlx;




//File init
void	game_loop(void *ml);
void init_the_player(t_mlx mlx);
void	start_the_game(t_data *dt);

//File map
t_data *init_argumet(void);

//File movement
void	ft_reles(mlx_key_data_t keydata, t_mlx *mlx);
void mlx_key(mlx_key_data_t keydata, void *ml);
void	rotate_player(t_mlx *mlx, int i);
void	move_player(t_mlx *mlx, double move_x, double move_y);
void	hook(t_mlx *mlx, double move_x, double move_y);

//File raycast 
int	unit_circle(float angle, char c);
int	inter_check(float angle, float *inter, float *step, int is_horizon);
int	wall_hit(float x, float y, t_mlx *mlx);
float	get_h_inter(t_mlx *mlx, float angl);
float	get_v_inter(t_mlx *mlx, float angl);
void	cast_rays(t_mlx *mlx);

//File utils
void	ft_exit(t_mlx *mlx);

//File wall rend
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
float	nor_angle(float angle);
void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix);
int	get_color(t_mlx *mlx, int flag);
void	draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix);
void	render_wall(t_mlx *mlx, int ray);

//File mouse
void ft_mouse(double xpos, double ypos, void *ml);

//File minimap
void	ft_minimap(t_mlx *mlx);


#endif
