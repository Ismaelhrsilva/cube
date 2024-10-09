/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:29:25 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/09 18:44:14 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include "ft_stdlib.h"
#include "MLX42.h"
#include <math.h>

mlx_texture_t	*construct_texture(t_mlx *mlx, char *png);

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

static void	init_player(t_mlx mlx)
{
	mlx.player->x = mlx.data->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->y = mlx.data->p_y * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->fov = (FOV * M_PI) / 180;
	if (mlx.data->parser->player[2] == 'N')
		mlx.player->angle = M_PI * NORTH;
	else if (mlx.data->parser->player[2] == 'S')
		mlx.player->angle = M_PI * SOUTH;
	else if (mlx.data->parser->player[2] == 'W')
		mlx.player->angle = M_PI * WEST;
}

void	start(t_data *data)
{
	t_mlx	mlx;

	mlx = (t_mlx){0};
	mlx.data = data;
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, sizeof(t_ray));
	mlx.minimap = ft_calloc(1, sizeof(t_minimap));
	mlx.texture = ft_calloc(1, sizeof(t_texture));
	if (!mlx.player || !mlx.ray || !mlx.minimap || !mlx.texture)
		exit(125);
	mlx.texture->north = construct_texture(&mlx, data->parser->north);
	mlx.texture->south = construct_texture(&mlx, data->parser->south);
	mlx.texture->west = construct_texture(&mlx, data->parser->west);
	mlx.texture->east = construct_texture(&mlx, data->parser->east);
	mlx.texture->door = construct_texture(&mlx, "./assets/door.png");
	mlx.p = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", true);
	mlx_set_window_limit(mlx.p, 1024, 768, -1, -1);
	init_player(mlx);
	mlx_loop_hook(mlx.p, &game_loop, &mlx);
	mlx_key_hook(mlx.p, &key, &mlx);
	mlx_cursor_hook(mlx.p, &mouse, &mlx);
	mlx_loop(mlx.p);
	gameover(&mlx, ft_strdup("Game Over"), 0);
}
