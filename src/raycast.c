/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:26:47 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/17 08:51:47 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "ft_string.h"
#include "MLX42.h"
#include <math.h>

int	unit_circle(float angle, char c)	// check the unit circle
{
	if (c == 'x' && angle > 0 && angle < M_PI)
		return (1);
	else if (c == 'y' && angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
		return (1);
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)	// check the intersection
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_mlx *mlx)	// check the wall hit
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE); // get the x position in the map
	y_m = floor (y / TILE_SIZE); // get the y position in the map
	if ((y_m >= mlx->dt->height || x_m >= mlx->dt->width))
		return (0);
	if (mlx->dt->map[y_m] && x_m <= (int)ft_strlen(mlx->dt->map[y_m]))
		if (mlx->dt->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h_inter(t_mlx *mlx, float angl)	// get the horizontal intersection
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor((float)mlx->player->y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = mlx->player->x + (h_y - mlx->player->y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx)) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - mlx->player->x, 2) + pow(h_y - mlx->player->y, 2))); // get the distance
}

float	get_v_inter(t_mlx *mlx, float angl)	// get the vertical intersection
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE; 
	y_step = TILE_SIZE * tan(angl);
	v_x = floor((float)mlx->player->x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0); // check the intersection and get the pixel value
	v_y = mlx->player->y + (v_x - mlx->player->x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx)) // check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - mlx->player->x, 2) + pow(v_y - mlx->player->y, 2))); // get the distance
}

void	cast_rays(t_mlx *mlx)	// cast the rays
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->angle = mlx->player->angle - (mlx->player->fov / 2); // the start angle
	while (ray < S_W) // loop for the rays
	{
		mlx->ray->flag = 0; // flag for the wall
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->angle)); // get the horizontal intersection
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->angle)); // get the vertical intersection
		if (v_inter <= h_inter) // check the distance
			mlx->ray->distance = v_inter; // get the distance
		else
		{
			mlx->ray->distance = h_inter; // get the distance
			mlx->ray->flag = 1; // flag for the wall
		}
		render_wall(mlx, ray); // render the wall
		ray++; // next ray
		mlx->ray->angle += (mlx->player->fov / S_W); // next angle
	}
}
