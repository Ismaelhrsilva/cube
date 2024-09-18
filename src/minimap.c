/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:30:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/18 15:51:47 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <math.h>

void	draw_walls_2d(t_mlx *mlx)
{
	int32_t	x;
	int32_t	y;
	int32_t	width;
	int32_t	height;

	y = 0;
	while(y < mlx->dt->height * mlx->dt->size_minimap)
	{
		height = y / mlx->dt->size_minimap;
		x = 0;
		while (x < mlx->dt->width * mlx->dt->size_minimap)
		{
			width = x / mlx->dt->size_minimap;
			if (mlx->dt->map[height][width] == '1')
				mlx_put_pixel(mlx->dt->image, x, y, 0x000000FF);
			else if (mlx->dt->map[height][width] == '2')
				mlx_put_pixel(mlx->dt->image, x, y, 0xFFFFFF7F);
			//if (x % mlx->dt->size_minimap == 0)
			//	mlx_put_pixel(mlx->dt->image, x, y, 0x000000FF);
			//else if (y % mlx->dt->size_minimap == 0)
			//	mlx_put_pixel(mlx->dt->image, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

#include <stdio.h>
void draw_player(t_mlx *mlx)
{
	// Coordenadas centrais e propriedades do quadrado
    int32_t	centerX = (double) mlx->player->x / TILE_SIZE * mlx->dt->size_minimap;
    int32_t	centerY = (double) mlx->player->y / TILE_SIZE * mlx->dt->size_minimap;
    int sideLength = mlx->dt->size_minimap; // Lado do quadrado

    // Desenhar o quadrado
    int halfSide = sideLength / 4;
    for (int y = -halfSide; y <= halfSide; y++)
    {
        for (int x = -halfSide; x <= halfSide; x++)
        {
            int32_t px = centerX + x;
            int32_t py = centerY + y;

            // Verificar se o pixel está dentro dos limites da imagem
            //if (px >= 0 && px < (int32_t) mlx->dt->image->width
			//	&& py >= 0 && py < (int32_t) mlx->dt->image->height)
            //{
			if (halfSide / 2 == (int)sqrt(pow(y - halfSide, 2) + pow(x - halfSide, 2)))
				mlx_put_pixel(mlx->dt->image, px, py, 0xFF0000FF);
            //}
        }
    }
}

void	draw_line(t_mlx *mlx)
{
	int	block_size = mlx->dt->size_minimap;

    for (uint32_t i = 0; i < mlx->dt->image->width; i += block_size)
    {
        for (uint32_t y = 0; y < mlx->dt->image->height; ++y)
        {
            mlx_put_pixel(mlx->dt->image, i, y, 0x000000FF); // Preto
        }
    }
    for (uint32_t y = 0; y < mlx->dt->image->height; y += block_size)
    {
        for (uint32_t i = 0; i < mlx->dt->image->width; ++i)
        {
            mlx_put_pixel(mlx->dt->image, i, y, 0x000000FF); // Preto
        }
    }
}

#include <stdlib.h>
void ft_randomize(void* param)
{
	t_mlx	*mlx;

	mlx = param;
	//for (uint32_t i = 0; i < mlx->dt->image->width; ++i)
	//{
	//	for (uint32_t y = 0; y < mlx->dt->image->height; ++y)
	//	{
	//		//uint32_t color = ft_pixel(
	//		//	rand() % 0xFF, // R
	//		//	rand() % 0xFF, // G
	//		//	rand() % 0xFF, // B
	//		//	rand() % 0xFF  // A
	//		//);
	//		//mlx_put_pixel(mlx->dt->image, i, y, color);
	//		mlx_put_pixel(mlx->dt->image, i, y, 0x00FFFFFF);
	//	}
	//}
	draw_walls_2d(mlx);
    draw_player(mlx);
	//draw_line(mlx);
}

void	ft_minimap(t_mlx *mlx)
{
	if (!mlx->dt->image)
	{
		mlx->dt->size_minimap = TILE_SIZE; //(double) mlx->img->width / (mlx->dt->width - 1) * 0.25;
		mlx->dt->image = mlx_new_image(mlx->mlx_p, 
			mlx->dt->size_minimap * mlx->dt->width, 
			mlx->dt->size_minimap * mlx->dt->height);
		mlx_image_to_window(mlx->mlx_p, mlx->dt->image, 0, 0);
		mlx->dt->image->instances[0].z = 1;
		mlx->dt->image->instances[0].enabled = false;
		mlx_loop_hook(mlx->mlx_p, ft_randomize, mlx);
	}
	mlx->dt->image->instances[0].enabled = !mlx->dt->image->instances[0].enabled;
	//if (mlx->dt->minimap_turn == 1)
	//{
	//	mlx->dt->image->instances[0].enabled = false;
	//	mlx->dt->minimap_turn = 0;
	//	return ;
	//}
	//else
	//	mlx->dt->minimap_turn = 1;
	//mlx->dt->size_minimap = TILE_SIZE;
	//mlx->dt->image = mlx_new_image(mlx->mlx_p, mlx->dt->size_minimap * mlx->dt->width,
	//				   mlx->dt->size_minimap * mlx->dt->height);
	//mlx_image_to_window(mlx->mlx_p, mlx->dt->image, 0, 0);
	//mlx->dt->image->instances[0].enabled = true;
	//mlx->dt->image->instances[0].z = 1;
	//mlx_loop_hook(mlx->mlx_p, ft_randomize, mlx);
}
