/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:51:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/08/29 20:11:36 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/cube.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

static mlx_image_t* image;

t_cube	*var_cube(void)
{
	static t_cube	cube;

	return (&cube);
}

mlx_t	*init_windows(void)
{
	static mlx_t	*instance;

	instance = mlx_init(WIDTH, HEIGHT, "cub3D", true);	
	var_cube()->instance = instance;
	return (instance);
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

int	main(void)
{
	t_cube	*cube;

	cube = var_cube();
	cube->instance = init_windows();
	image = mlx_new_image(cube->instance, 128, 128);
	mlx_image_to_window(cube->instance, image, 0, 0);

	mlx_loop_hook(cube->instance, ft_randomize, cube->instance);
	mlx_loop_hook(cube->instance, ft_hook, cube->instance);

	mlx_loop(cube->instance);
	mlx_terminate(cube->instance);
	return (0);
}
