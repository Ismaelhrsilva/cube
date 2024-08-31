/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:51:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/08/31 19:48:57 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/cube.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

t_cube	*var_cube(void)
{
	static t_cube	cube;

	return (&cube);
}

void	game_loop(void *cub)
{
	t_cube *cube;

	cube = cub;
	//mlx_delete_image(cube->init, cube->img);
	cube->img = mlx_new_image(cube->init, WIDTH, HEIGHT);
	//hook(cube, 0, 0);
	//cats_rays(cube);
	mlx_image_to_window(cube->init, cube->img, 0, 0);

}

void	init_player(t_cube *cube)
{
	cube->player->player_x = cube->data->player_x * TILE_SIZE + TILE_SIZE / 2;
	cube->player->player_y = cube->data->player_y * TILE_SIZE + TILE_SIZE / 2;
	cube->player->fov_rd = (FOV * M_PI) / 180;
	cube->player->angle = M_PI;
}

void	start_the_game(void)
{
	t_cube *cube;

	cube = var_cube();
	cube->player = calloc(1, sizeof(t_player));
	cube->ray = calloc(1, sizeof(t_ray));
	cube->init = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	init_player(cube);
	mlx_loop_hook(cube->init, &game_loop, &cube);
	//mlx_key_hook(cube->init, &mlx_key, &cube);
	mlx_loop(cube->init);
	//ft_exit(&cube);
}

t_data *init_arg(void)
{
	t_data *dt = calloc(1, sizeof(t_data)); // init the data structure
	dt->map2d = calloc(10, sizeof(char *)); // init the map
	dt->map2d[0] = strdup("1111111111111111111111111"); //fill the map
	dt->map2d[1] = strdup("1000000000000000000100001");
	dt->map2d[2] = strdup("1001000000000P00000000001");
	dt->map2d[3] = strdup("1001000000000000001000001");
	dt->map2d[4] = strdup("1001000000000000001000001");
	dt->map2d[5] = strdup("1001000000100000001000001");
	dt->map2d[6] = strdup("1001000000000000001000001");
	dt->map2d[7] = strdup("1001000000001000001000001");
	dt->map2d[8] = strdup("1111111111111111111111111");
	dt->map2d[9] = NULL;
	dt->player_y = 3; // player y position in the map
	dt->player_x = 14; // player x position in the map
	dt->width_map = 25; // map width
	dt->height_map = 9; // map height
	return (dt); // return the data structure
}

int	main(void)
{
	t_cube *cube;

	cube = var_cube();
	cube->data = init_arg();
	start_the_game();
	return (0);
}
