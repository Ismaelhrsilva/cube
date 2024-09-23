/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:26:47 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/21 13:59:20 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "ft_string.h"
#include "MLX42.h"
#include <math.h>

float	pytheorem(float a, float b)
{
	return (sqrt((a * a) + (b * b)));
}

static int	horizontal_unit_circle(float angle) // check the unit circle
{
	return (angle > 0 && angle < M_PI);
}

static int	vertical_unit_circle(float angle) // check the unit circle
{
	return (angle > (M_PI / 2) && angle < (3 * M_PI) / 2);
}

//int	inter_check(float angle, float *inter, float *step, int is_horizon)	// check the intersection
//{
//	if (is_horizon)
//	{
//		if (angle > 0 && angle < M_PI)
//		{
//			*inter += TILE_SIZE;
//			return (-1);
//		}
//		*step *= -1;
//	}
//	else
//	{
//		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
//		{
//			*inter += TILE_SIZE;
//			return (-1);
//		}
//		*step *= -1;
//	}
//	return (1);
//}

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

int	wall_hit(float x, float y, t_mlx *mlx)	// check the wall hit
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE); // get the x position in the map
	y_m = floor(y / TILE_SIZE); // get the y position in the map
	if ((y_m >= mlx->dt->height || x_m >= mlx->dt->width))
		return (0);
	//if (mlx->dt->map[y_m] && x_m <= (int)ft_strlen(mlx->dt->map[y_m]))
	if (mlx->dt->map[y_m][x_m] == '1')
		return (0);
	return (1);
}

float	get_h_inter(t_mlx *mlx, float angle)	// get the horizontal intersection
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	y = floor((double) mlx->player->y / TILE_SIZE) * TILE_SIZE;
	//pixel = inter_check(angle, &y, &y_step, 1);
	pixel = intersection(&y, &y_step, horizontal_unit_circle(angle));
	x = mlx->player->x + (y - mlx->player->y) / tan(angle);
	if (x_step != 0 && (x_step > 0) == vertical_unit_circle(angle)) // check x_step value
		x_step = -x_step;
	while (wall_hit(x, y - pixel, mlx)) // check the wall hit whit the pixel value
	{
		x += x_step;
		y += y_step;
	}
	mlx->ray->x = x;
	mlx->ray->y = y;
	return (pytheorem(x - mlx->player->x, y - mlx->player->y));
}

float	get_v_inter(t_mlx *mlx, float angle)	// get the vertical intersection
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE; 
	y_step = TILE_SIZE * tan(angle);
	x = floor((float)mlx->player->x / TILE_SIZE) * TILE_SIZE;
	pixel = intersection(&x, &x_step, !vertical_unit_circle(angle)); // check the intersection and get the pixel value
	//pixel = inter_check(angle, &x, &x_step, 0); // check the intersection and get the pixel value
	y = mlx->player->y + (x - mlx->player->x) * tan(angle);
	if (y_step != 0 && (y_step < 0) == horizontal_unit_circle(angle)) // check y_step value
		y_step = -y_step;
	while (wall_hit(x - pixel, y, mlx)) // check the wall hit whit the pixel value
	{
		x += x_step;
		y += y_step;
	}
	mlx->ray->vx = x;
	mlx->ray->vy = y;
	return (pytheorem(x - mlx->player->x, y - mlx->player->y));
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
	//ft_animation(mlx);
}
