/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:30:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/06 20:56:57 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_len(t_mlx *mlx)
{
	int	size = mlx->dt->size_minimap;
	if ((size / mlx->dt->h_map) >= (size / mlx->dt->w_map))
		mlx->dt->len = size / mlx->dt->w_map;
	else
		mlx->dt->len = size / mlx->dt->h_map;
}

void draw_player(mlx_image_t *image, int centerX, int centerY, int sideLength, uint32_t color)
{
    int halfSide = sideLength / 2;
    for (int y = -halfSide; y <= halfSide; ++y)
    {
        for (int x = -halfSide; x <= halfSide; ++x)
        {
            uint32_t px = centerX + x;
            uint32_t py = centerY + y;

            // Verificar se o pixel está dentro dos limites da imagem
            if (px >= 0 && px < image->width && py >= 0 && py < image->height)
            {
                mlx_put_pixel(image, px, py, color);
            }
        }
    }
}

void ft_randomize(void* param)
{
	t_mlx	*mlx;

	mlx = param;
	ft_len(mlx);
	int block_size = mlx->dt->len;
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
	// Desenhar as linhas e colunas de preto
    for (uint32_t i = 0; i < image->width; i += block_size)
    {
        for (uint32_t y = 0; y < image->height; ++y)
        {
            mlx_put_pixel(image, i, y, 0x000000FF); // Preto
        }
    }

    for (uint32_t y = 0; y < image->height; y += block_size)
    {
        for (uint32_t i = 0; i < image->width; ++i)
        {
            mlx_put_pixel(image, i, y, 0x000000FF); // Preto
        }
    }
	// Coordenadas centrais e propriedades do quadrado
    int centerX = mlx->ply->plyr_x; // Exemplo: Centro da imagem
    int centerY = mlx->ply->plyr_y; // Exemplo: Centro da imagem
    int squareSide = 10; // Lado do quadrado
    uint32_t squareColor = 0xFF0000FF; // Cor do quadrado (vermelho)

    // Desenhar o quadrado
    draw_player(image, centerX, centerY, squareSide, squareColor);
}

void	ft_minimap(t_mlx *mlx)
{
	if (mlx->dt->minimap_turn == 1)
	{
		image->instances[0].enabled = false;
		mlx->dt->minimap_turn = 0;
		return ;
	}
	else
		mlx->dt->minimap_turn = 1;
	mlx->dt->size_minimap = 400;
	image = mlx_new_image(mlx->mlx_p, mlx->dt->size_minimap, mlx->dt->size_minimap);
	mlx_image_to_window(mlx->mlx_p, image, 0, 0);
	image->instances[0].enabled = true;
	image->instances[0].z = 1;
	mlx_loop_hook(mlx->mlx_p, ft_randomize, mlx);
}
