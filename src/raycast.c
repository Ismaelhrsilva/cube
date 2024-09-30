/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:26:47 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/30 19:51:37 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "ft_string.h"
#include "MLX42.h"
#include <math.h>
#include <stdlib.h>

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
	int	x_m;
	int	y_m;
	int32_t	map_grid_y;
	int32_t	map_grid_x;

	x = roundf(mlx->player->x + x);
	y = roundf(mlx->player->y + y);

	map_grid_x = x / TILE_SIZE;
	map_grid_y = y / TILE_SIZE;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= mlx->dt->height || x_m >= mlx->dt->width))
		return (0);
	//if (mlx->dt->map[y_m][x_m] == 'd')
	if (mlx->dt->map[map_grid_y][map_grid_x] == 'd'
		|| mlx->dt->map[map_grid_y][mlx->player->x / TILE_SIZE] == 'd'
		|| mlx->dt->map[mlx->player->y / TILE_SIZE][map_grid_x] == 'd')
	{
		mlx->dt->door_closed = 0;
		return (0);
	}
	else if (mlx->dt->map[y_m][x_m] == '1')
	{
		mlx->dt->door_closed = 0;
		return (0);
	}
	else
		mlx->dt->door_closed = 0;
	return (1);
}

float	get_h_inter(t_mlx *mlx, float angle)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	y = floor((double) mlx->player->y / TILE_SIZE) * TILE_SIZE;
	pixel = intersection(&y, &y_step, horizontal_unit_circle(angle));
	x = mlx->player->x + (y - mlx->player->y) / tan(angle);
	if (x_step != 0 && (x_step > 0) == vertical_unit_circle(angle))
		x_step = -x_step;
	while (wall_hit(x, y - pixel, mlx))
	{
		x += x_step;
		y += y_step;
	}
	mlx->ray->x = x;
	mlx->ray->y = y;
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
	x = floor((float)mlx->player->x / TILE_SIZE) * TILE_SIZE;
	pixel = intersection(&x, &x_step, !vertical_unit_circle(angle));
	y = mlx->player->y + (x - mlx->player->x) * tan(angle);
	if (y_step != 0 && (y_step < 0) == horizontal_unit_circle(angle))
		y_step = -y_step;
	while (wall_hit(x - pixel, y, mlx))
	{
		x += x_step;
		y += y_step;
	}
	mlx->ray->vx = x;
	mlx->ray->vy = y;
	return (pytheorem(x - mlx->player->x, y - mlx->player->y));
}

void	cast_rays(t_mlx *mlx)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->angle = mlx->player->angle - (mlx->player->fov / 2);
	while (ray < S_W)
	{
		mlx->ray->flag = 0;
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->angle));
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->angle));
		if (v_inter <= h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->flag = 1;
		}
		render_wall(mlx, ray);
		ray++;
		mlx->ray->angle += (mlx->player->fov / S_W);
	}
	ft_animation(mlx);
} 
