/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:26:47 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/02 16:40:09 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <math.h>

void	render_wall(t_mlx *mlx, int ray);
float	normalize(float angle);
float	pytheorem(float a, float b);
int		horizontal_unit_circle(float angle);
int		vertical_unit_circle(float angle);

int	intersection(float *inter, float *step, int evaluation)
{
	if (evaluation)
	{
		*inter += TILE_SIZE;
		return (-1);
	}
	*step = -*step;
	return (1);
}

int	wall_hit(float x, float y, t_mlx *mlx)
{
	if (x < 0 || y < 0)
		return (0);
	mlx->ray->door = false;
	x = floor(x / TILE_SIZE);
	y = floor(y / TILE_SIZE);
	if (y >= mlx->data->height || x >= mlx->data->width)
		return (0);
	if (mlx->data->map[(int) y][(int) x] == '1')
		return (0);
	if (mlx->data->map[(int) y][(int) x] == 'd')
	{
		mlx->ray->door = true;
		return (0);
	}
	return (1);
}

float	get_h_inter(t_mlx *mlx, float angle)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE / tan(angle);
	y_step = TILE_SIZE;
	y = floorf((double) mlx->player->y / TILE_SIZE) * TILE_SIZE;
	pixel = intersection(&y, &y_step, horizontal_unit_circle(mlx->ray->angle));
	x = mlx->player->x + (y - mlx->player->y) / tan(angle);
	if ((x_step > 0) == vertical_unit_circle(angle))
		x_step = -x_step;
	while (wall_hit(x, y - pixel, mlx))
	{
		x += x_step;
		y += y_step;
	}
	mlx->ray->x = x;
	mlx->ray->y = 0;
	return (pytheorem(x - mlx->player->x, y - mlx->player->y));
}

float	get_v_inter(t_mlx *mlx, float angle)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	x = floorf((double)mlx->player->x / TILE_SIZE) * TILE_SIZE;
	pixel = intersection(&x, &x_step, !vertical_unit_circle(mlx->ray->angle));
	y = mlx->player->y + (x - mlx->player->x) * tan(angle);
	if ((y_step < 0) == horizontal_unit_circle(angle))
		y_step = -y_step;
	while (wall_hit(x - pixel, y, mlx))
	{
		x += x_step;
		y += y_step;
	}
	mlx->ray->x = 0;
	mlx->ray->y = y;
	return (pytheorem(x - mlx->player->x, y - mlx->player->y));
}

void	raycast(t_mlx *mlx)
{
	double		h_inter;
	double		v_inter;
	uint32_t	ray;

	ray = 0;
	mlx->ray->angle = mlx->player->angle - (mlx->player->fov / 2);
	while (ray < mlx->img->width)
	{
		v_inter = get_v_inter(mlx, normalize(mlx->ray->angle));
		h_inter = get_h_inter(mlx, normalize(mlx->ray->angle));
		if (v_inter < h_inter)
			mlx->ray->distance = get_v_inter(mlx, normalize(mlx->ray->angle));
		else
			mlx->ray->distance = get_h_inter(mlx, normalize(mlx->ray->angle));
		render_wall(mlx, ray++);
		mlx->ray->angle += ((double) mlx->player->fov / mlx->img->width);
	}
	animation(mlx);
}
