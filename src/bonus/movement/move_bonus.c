/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:24:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/09 19:36:28 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"
#include "libft.h"
#include "MLX42.h"
#include <math.h>
#include <stdint.h>

static void	move(t_mlx *mlx, float *x, float *y)
{
	int32_t	map_y;
	int32_t	map_x;
	int32_t	map_a;
	int32_t	map_b;

	x[0] = roundf(mlx->player->x + x[0]);
	y[0] = roundf(mlx->player->y + y[0]);
	x[1] = roundf(mlx->player->x + x[1]);
	y[1] = roundf(mlx->player->y + y[1]);
	map_x = x[0] / TILE_SIZE;
	map_y = y[0] / TILE_SIZE;
	map_a = x[1] / TILE_SIZE;
	map_b = y[1] / TILE_SIZE;
	if (ft_strchr("d1", mlx->data->map[map_y][map_x])
		|| ft_strchr("d1", mlx->data->map[map_b][mlx->player->x / TILE_SIZE])
		|| ft_strchr("d1", mlx->data->map[mlx->player->y / TILE_SIZE][map_a]))
		return ;
	mlx->player->x = x[0];
	mlx->player->y = y[0];
}

void	rotation_move(t_mlx *mlx, int32_t direction)
{
	mlx->player->angle += ROTATION_SPEED * direction;
	if (mlx->player->angle < 0 || mlx->player->angle > 2 * M_PI)
		mlx->player->angle += 2 * M_PI * -direction;
}

static void	vertical_move(t_mlx *mlx, int32_t direction)
{
	float	x[2];
	float	y[2];

	x[0] = (direction * (cos(mlx->player->angle)));
	y[0] = (direction * (sin(mlx->player->angle)));
	x[1] = x[0] * (PLAYER_SPEED * PLAYER_SIZE);
	y[1] = y[0] * (PLAYER_SPEED * PLAYER_SIZE);
	x[0] *= PLAYER_SPEED;
	y[0] *= PLAYER_SPEED;
	move(mlx, x, y);
}

static void	horizontal_move(t_mlx *mlx, int32_t direction)
{
	float	x[2];
	float	y[2];

	x[0] = (-direction * (sin(mlx->player->angle)));
	y[0] = (direction * (cos(mlx->player->angle)));
	x[1] = x[0] * (PLAYER_SPEED * PLAYER_SIZE);
	y[1] = y[0] * (PLAYER_SPEED * PLAYER_SIZE);
	x[0] *= PLAYER_SPEED;
	y[0] *= PLAYER_SPEED;
	move(mlx, x, y);
}

void	hook(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->p, MLX_KEY_W))
		vertical_move(mlx, POSITIVE);
	else if (mlx_is_key_down(mlx->p, MLX_KEY_S))
		vertical_move(mlx, NEGATIVE);
	if (mlx_is_key_down(mlx->p, MLX_KEY_D))
		horizontal_move(mlx, POSITIVE);
	else if (mlx_is_key_down(mlx->p, MLX_KEY_A))
		horizontal_move(mlx, NEGATIVE);
	if (mlx_is_key_down(mlx->p, MLX_KEY_RIGHT))
		rotation_move(mlx, POSITIVE);
	else if (mlx_is_key_down(mlx->p, MLX_KEY_LEFT))
		rotation_move(mlx, NEGATIVE);
}
