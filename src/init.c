/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:29:25 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/01 19:05:16 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "ft_stdlib.h"
#include "MLX42.h"
#include <math.h>

void	game_loop(void *ml)	// game loop
{
	t_mlx	*mlx;

	mlx = (t_mlx *) ml;	// cast to the mlx structure
	mlx_delete_image(mlx->p, mlx->img);	// delete the image
	mlx->img = mlx_new_image(mlx->p, S_W, S_H);	// create new image
	hook(mlx); // hook the player
	cast_rays(mlx);	// cast the rays
	mlx_image_to_window(mlx->p, mlx->img, 0, 0); // put the image to the window
	mlx->img->instances[0].z = 0;
}

void init_the_player(t_mlx mlx)	// init the player structure
{
	mlx.player->x = mlx.data->p_x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
	mlx.player->y = mlx.data->p_y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
	mlx.player->fov = (FOV * M_PI) / 180; // field of view in radians
	//mlx.player->angle = M_PI; // player angle
	//the rest of the variables are initialized to zero by calloc
}

void	start_the_game(t_data *data, t_map *map)	// start the game
{
	t_mlx	mlx;

	mlx.data = data;	// init the mlx structure
	mlx.player = ft_calloc(1, sizeof(t_player));	// init the player structure i'm using calloc to initialize the variables to zero
	mlx.ray = ft_calloc(1, sizeof(t_ray));	// init the ray structure
	mlx.minimap = ft_calloc(1, sizeof(t_minimap));
	mlx.texture = ft_calloc(1, sizeof(t_texture));
	

	////
	mlx.texture->north = construct_texture(&mlx, map->north);
	mlx.texture->south = construct_texture(&mlx, map->south);
	mlx.texture->west = construct_texture(&mlx, map->west);
	mlx.texture->east = construct_texture(&mlx, map->east);
	mlx.texture->door = construct_texture(&mlx, "./assets/wall/door.png");
	//mlx.texture->door = construct_texture(&mlx, "./assets/door/cdoord.png");
	////
	
	if (map->player[2] == 'N')
		mlx.player->angle = M_PI * NORTH;
	else if (map->player[2] == 'S')
		mlx.player->angle = M_PI * SOUTH;
	else if (map->player[2] == 'W')
		mlx.player->angle = M_PI * WEST;




	//mlx.minimap->img = NULL;
	//mlx_set_setting(MLX_FULLSCREEN, true); // fullscreen mode
	mlx.p = mlx_init(S_W, S_H, "Cub3d", true);	// init the mlx pointer
	mlx_set_window_limit(mlx.p, 640, 480, -1, -1);
	ft_init_animation(&mlx);
	init_the_player(mlx);	// init the player structure
	mlx_loop_hook(mlx.p, &game_loop, &mlx);	// game loop
	mlx_key_hook(mlx.p, &mlx_key, &mlx);	// key press and release
	mlx_cursor_hook(mlx.p, &ft_mouse, &mlx); // função de movimentação com mouse
	mlx_loop(mlx.p);	// mlx loop
}
