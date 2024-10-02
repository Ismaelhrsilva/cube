/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:29:25 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/02 18:29:53 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "ft_stdlib.h"
#include "MLX42.h"
#include <math.h>

mlx_texture_t	*construct_texture(char *png);

static void	game_loop(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) param;
	mlx_delete_image(mlx->p, mlx->img);
	mlx->img = mlx_new_image(mlx->p, mlx->p->width, mlx->p->height);
	hook(mlx);
	raycast(mlx);
	mlx_image_to_window(mlx->p, mlx->img, 0, 0);
	mlx->img->instances[0].z = 0;
}

static void	init_player(t_mlx mlx, t_map *map)
{
	mlx.player->x = mlx.data->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->y = mlx.data->p_y * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->fov = (FOV * M_PI) / 180;
	if (map->player[2] == 'N')
		mlx.player->angle = M_PI * NORTH;
	else if (map->player[2] == 'S')
		mlx.player->angle = M_PI * SOUTH;
	else if (map->player[2] == 'W')
		mlx.player->angle = M_PI * WEST;
}

void	start(t_data *data, t_map *map)
{
	t_mlx	mlx;

	mlx.data = data;
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, sizeof(t_ray));
	mlx.minimap = ft_calloc(1, sizeof(t_minimap));
	mlx.texture = ft_calloc(1, sizeof(t_texture));
	if (!mlx.player || !mlx.ray || !mlx.minimap || !mlx.texture)
		exit(125);
	mlx.texture->north = construct_texture(map->north);
	mlx.texture->south = construct_texture(map->south);
	mlx.texture->west = construct_texture(map->west);
	mlx.texture->east = construct_texture(map->east);
	mlx.texture->door = construct_texture("./assets/door.png");
	mlx.p = mlx_init(S_W, S_H, "Cub3d", true);
	mlx_set_window_limit(mlx.p, 1024, 768, -1, -1);
	init_player(mlx, map);
	mlx_loop_hook(mlx.p, &game_loop, &mlx);
	mlx_key_hook(mlx.p, &key, &mlx);
	mlx_cursor_hook(mlx.p, &mouse, &mlx);
	mlx_loop(mlx.p);
}
