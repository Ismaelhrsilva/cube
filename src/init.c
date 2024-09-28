/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:29:25 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/28 11:56:08 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "ft_stdlib.h"
#include "MLX42.h"
#include <math.h>

void	game_loop(void *ml)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) ml;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	hook(mlx);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
	mlx->img->instances[0].z = 0;
}

void	init_the_player(t_mlx mlx)
{
	mlx.player->x = mlx.dt->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->y = mlx.dt->p_y * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->fov = (FOV * M_PI) / 180;
	mlx.player->angle = M_PI;
}

void	start_the_game(t_data *dt, t_map *map)
{
	t_mlx	mlx;

	mlx.dt = dt;
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, sizeof(t_ray));
	mlx.minimap = ft_calloc(1, sizeof(t_minimap));
	mlx.texture = ft_calloc(1, sizeof(t_texture));
	mlx.texture->no = construct_texture(&mlx, map->north);
	mlx.texture->so = construct_texture(&mlx, map->south);
	mlx.texture->we = construct_texture(&mlx, map->west);
	mlx.texture->ea = construct_texture(&mlx, map->east);
	mlx.texture->door = construct_texture(&mlx, DOOR);
	mlx.mlx_p = mlx_init(S_W, S_H, "Cub3d", 0);
	ft_init_animation(&mlx);
	init_the_player(mlx);
	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);
	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);
	mlx_cursor_hook(mlx.mlx_p, &ft_mouse, &mlx);
	mlx_loop(mlx.mlx_p);
}
