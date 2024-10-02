/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:30:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/02 18:01:33 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"

char	*ft_strchr(const char *s, int c);
float	pytheorem(float a, float b);

void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x > img->width || y > img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

static void	display_wall(t_mlx *mlx)
{
	int32_t	x;
	int32_t	y;
	int32_t	width;
	int32_t	height;

	y = 0;
	while (y < mlx->data->height * mlx->minimap->size)
	{
		height = y / mlx->minimap->size;
		x = 0;
		while (x < mlx->data->width * mlx->minimap->size)
		{
			width = x / mlx->minimap->size;
			if (mlx->data->map[height][width] == '1')
				put_pixel(mlx->minimap->img, x, y, 0x000000FF);
			else if (mlx->data->map[height][width] == '2')
				put_pixel(mlx->minimap->img, x, y, 0xFFFFFF7F);
			if (ft_strchr("dD", mlx->data->map[height][width]))
				put_pixel(mlx->minimap->img, x, y, 0x7F7F7FFF);
			x++;
		}
		y++;
	}
}

static void	display_player(t_mlx *mlx)
{
	int32_t	i;
	int32_t	j;
	int32_t	x;
	int32_t	y;
	int32_t	radius;

	x = (double) mlx->player->x / TILE_SIZE * mlx->minimap->size;
	y = (double) mlx->player->y / TILE_SIZE * mlx->minimap->size;
	radius = mlx->minimap->size / 2;
	i = 0;
	while (mlx->minimap->size > ++i)
	{
		j = 0;
		while (mlx->minimap->size > ++j)
		{
			if ((double) radius > (double) pytheorem(i - radius, j - radius))
				put_pixel(mlx->minimap->img,
					x + i - radius, y + j - radius, 0xFF0000FF);
		}
	}
}

static void	display_minimap(void *mlx)
{
	if (!((t_mlx *) mlx)->minimap->img->instances[0].enabled)
		return ;
	display_wall((t_mlx *) mlx);
	display_player((t_mlx *) mlx);
}

void	minimap(t_mlx *mlx)
{
	if (!mlx->minimap->img)
	{
		mlx->minimap->size = 4;
		mlx->minimap->img = mlx_new_image(mlx->p,
				mlx->minimap->size * mlx->data->width,
				mlx->minimap->size * mlx->data->height);
		mlx_image_to_window(mlx->p, mlx->minimap->img, 0, 0);
		mlx->minimap->img->instances[0].z = 1;
		mlx->minimap->img->instances[0].enabled = false;
		mlx_loop_hook(mlx->p, display_minimap, mlx);
	}
	mlx->minimap->img->instances[0].enabled
		= !mlx->minimap->img->instances[0].enabled;
}
