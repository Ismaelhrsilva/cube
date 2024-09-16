/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:29:25 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/15 18:06:10 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "ft_stdlib.h"
#include "MLX42.h"
#include <math.h>

void	game_loop(void *ml)	// game loop
{
	t_mlx	*mlx;

	mlx = ml;	// cast to the mlx structure
	mlx_delete_image(mlx->mlx_p, mlx->img);	// delete the image
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);	// create new image
	hook(mlx, 0, 0); // hook the player
	cast_rays(mlx);	// cast the rays
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0); // put the image to the window
	mlx->img->instances[0].z = 0;
}

void init_the_player(t_mlx mlx)	// init the player structure
{
	mlx.ply->plyr_x = mlx.dt->p_x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
	mlx.ply->plyr_y = mlx.dt->p_y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
	mlx.ply->fov_rd = (FOV * M_PI) / 180; // field of view in radians
	mlx.ply->angle = M_PI; // player angle
	//the rest of the variables are initialized to zero by calloc
}

void	start_the_game(t_data *dt)	// start the game
{
	t_mlx	mlx;

	mlx.dt = dt;	// init the mlx structure
	mlx.ply = ft_calloc(1, sizeof(t_player));	// init the player structure i'm using calloc to initialize the variables to zero
	mlx.ray = ft_calloc(1, sizeof(t_ray));	// init the ray structure
	//mlx_set_setting(MLX_FULLSCREEN, true); // fullscreen mode
	mlx.mlx_p = mlx_init(S_W, S_H, "Cub3d", 0);	// init the mlx pointer
	init_the_player(mlx);	// init the player structure
	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);	// game loop
	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);	// key press and release
	mlx_cursor_hook(mlx.mlx_p, &ft_mouse, &mlx); // função de movimentação com mouse
	mlx_loop(mlx.mlx_p);	// mlx loop
}
