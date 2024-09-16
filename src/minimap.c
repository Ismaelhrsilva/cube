/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:30:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/15 22:13:45 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <math.h>

void	draw_walls_2d(t_mlx *mlx)
{
	int	line;
	int	col;
	int size = mlx->dt->size_minimap;

	col = 0;
	while (col < mlx->dt->w_map)
	{
		line = 0;
		while (line < mlx->dt->h_map)
		{
			if (mlx->dt->map2d[line][col] == 49)
			{
				for (uint32_t y = size * line; y < (uint32_t)size * (line + 1); ++y)
    			{
    				for (uint32_t i = size * col; i < (uint32_t)size * (col + 1); ++i)
					{
            			mlx_put_pixel(mlx->dt->image, i, y, 0x000000FF); // Preto
        			}
    			}
			}
			line++;
		}
		col++;
	}
}

void draw_player(t_mlx *mlx)
{
	// Coordenadas centrais e propriedades do quadrado
    int centerX = mlx->ply->plyr_x; // Exemplo: Centro da imagem
    int centerY = mlx->ply->plyr_y; // Exemplo: Centro da imagem
    int sideLength = mlx->dt->size_minimap / 2; // Lado do quadrado
    uint32_t squareColor = 0xFF0000FF; // Cor do quadrado (vermelho)

    // Desenhar o quadrado
    int halfSide = sideLength / 2;
    for (int y = -halfSide; y <= halfSide; ++y)
    {
        for (int x = -halfSide; x <= halfSide; ++x)
        {
            int32_t px = centerX + x;
            int32_t py = centerY + y;

            // Verificar se o pixel está dentro dos limites da imagem
            if (px >= 0 && px < (int32_t) mlx->dt->image->width
				&& py >= 0 && py < (int32_t) mlx->dt->image->height)
            {
                mlx_put_pixel(mlx->dt->image, px, py, squareColor);
            }
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
	for (uint32_t i = 0; i < mlx->dt->image->width; ++i)
	{
		for (uint32_t y = 0; y < mlx->dt->image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(mlx->dt->image, i, y, color);
		}
	}
	draw_line(mlx);
    draw_player(mlx);
    draw_walls_2d(mlx);
}

void	ft_minimap(t_mlx *mlx)
{
	if (mlx->dt->minimap_turn == 1)
	{
		mlx->dt->image->instances[0].enabled = false;
		mlx->dt->minimap_turn = 0;
		return ;
	}
	else
		mlx->dt->minimap_turn = 1;
	mlx->dt->size_minimap = TILE_SIZE;
	mlx->dt->image = mlx_new_image(mlx->mlx_p, mlx->dt->size_minimap * mlx->dt->w_map,
					   mlx->dt->size_minimap * mlx->dt->h_map);
	mlx_image_to_window(mlx->mlx_p, mlx->dt->image, 0, 0);
	mlx->dt->image->instances[0].enabled = true;
	mlx->dt->image->instances[0].z = 1;
	mlx_loop_hook(mlx->mlx_p, ft_randomize, mlx);
}
