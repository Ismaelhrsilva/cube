/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:30:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/18 19:58:28 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <math.h>

static void	display_wall(t_mlx *mlx)
{
	int32_t	x;
	int32_t	y;
	int32_t	width;
	int32_t	height;

	y = 0;
	while (y < mlx->dt->height * mlx->minimap->size)
	{
		height = y / mlx->minimap->size;
		x = 0;
		while (x < mlx->dt->width * mlx->minimap->size)
		{
			width = x / mlx->minimap->size;
			if (mlx->dt->map[height][width] == '1')
				mlx_put_pixel(mlx->minimap->img, x, y, 0x000000FF);
			else if (mlx->dt->map[height][width] == '2')
				mlx_put_pixel(mlx->minimap->img, x, y, 0xFFFFFF7F);
			//if (x % mlx->minimap->size == 0)
			//	mlx_put_pixel(mlx->minimap->img, x, y, 0x000000FF);
			//else if (y % mlx->minimap->size == 0)
			//	mlx_put_pixel(mlx->minimap->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

void	display_player(t_mlx *mlx)
{
	int32_t	i;
	int32_t	j;
	int32_t	x;
	int32_t	y;
	int32_t	radius;

	x = (double) mlx->player->x / TILE_SIZE * mlx->minimap->size;
	y = (double) mlx->player->y / TILE_SIZE * mlx->minimap->size;
	radius = mlx->minimap->size / 4;
	i = 0;
	while (mlx->minimap->size > ++i)
	{
		j = 0;
		while (mlx->minimap->size > ++j)
		{
			if ((double) radius > (double) sqrt(pow(i - radius, 2) + pow(j - radius, 2)))
				mlx_put_pixel(mlx->minimap->img, x + i - radius, y + j - radius, 0xFF0000FF);
		}
	}
}

static void	display_minimap(void *mlx)
{
	display_wall((t_mlx *) mlx);
	display_player((t_mlx *) mlx);
}

void	ft_minimap(t_mlx *mlx)
{
	if (!mlx->minimap->img)
	{
		mlx->minimap->size = (double) mlx->mlx_p->width / mlx->dt->width * 0.4;
		mlx->minimap->img = mlx_new_image(mlx->mlx_p,
				mlx->minimap->size * mlx->dt->width,
				mlx->minimap->size * mlx->dt->height);
		mlx_image_to_window(mlx->mlx_p, mlx->minimap->img, 0, 0);
		mlx->minimap->img->instances[0].z = 1;
		mlx->minimap->img->instances[0].enabled = false;
		mlx_loop_hook(mlx->mlx_p, display_minimap, mlx);
	}
	mlx->minimap->img->instances[0].enabled
		= !mlx->minimap->img->instances[0].enabled;
}
