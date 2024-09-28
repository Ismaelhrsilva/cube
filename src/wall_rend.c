/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:25:38 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/28 13:55:20 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// get the right texture based on the angle
mlx_texture_t	*get_texture(t_mlx *mlx)
{
	if (mlx->dt->door_closed == 1)
		return (mlx->texture->door);
	mlx->ray->angle = nor_angle(mlx->ray->angle);
	if (mlx->ray->flag == 0)
	{
		if (mlx->ray->angle > M_PI / 2 && mlx->ray->angle < 3 * (M_PI / 2))
			return (mlx->texture->we);
		return (mlx->texture->ea);
	}
	if (mlx->ray->angle > 0 && mlx->ray->angle < M_PI)
		return (mlx->texture->so);
	return (mlx->texture->no);
}

double	get_x_o(mlx_texture_t *texture, t_mlx *mlx)
{
	double	x_o;

	if (mlx->ray->flag == 1)
		x_o = (int)fmodf((mlx->ray->x * \
		((double) texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (int)fmodf((mlx->ray->vy * \
		((double) texture->width / TILE_SIZE)), texture->width);
	return (x_o);
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(mlx);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	if (texture == mlx->texture->so || texture == mlx->texture->we)
		x_o = texture->width - get_x_o(texture, mlx);
	else
		x_o = get_x_o(texture, mlx);
	y_o = (t_pix - ((double) S_H / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		put_pixel(mlx, mlx->ray->index, t_pix, reverse_bytes \
			(arr[(int)y_o * texture->width + (int)x_o]));
		t_pix++;
		y_o += factor;
	}
}

void	render_wall(t_mlx *mlx, int ray)
{
	float	wall_h;
	float	b_pix;
	float	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->angle - mlx->player->angle));
	wall_h = (TILE_SIZE / mlx->ray->distance)
		* (((float )S_W / 2) / tan(mlx->player->fov / 2));
	b_pix = ((double) S_H / 2) + (wall_h / 2);
	t_pix = ((double) S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, t_pix, b_pix, wall_h);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}
