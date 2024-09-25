/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:24:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/25 15:14:13 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <math.h>
#include <stdint.h>

#include <stdio.h>
static void	move(t_mlx *mlx, float x, float y, float a, float b)	// move the player
{
	int32_t	map_grid_y;
	int32_t	map_grid_x;
	int32_t	map_grid_a;
	int32_t	map_grid_b;

	x = roundf(mlx->player->x + x); // get the new x position
	y = roundf(mlx->player->y + y); // get the new y position
	a = roundf(mlx->player->x + a);
	b = roundf(mlx->player->y + b);
	map_grid_x = x / TILE_SIZE; // get the x position in the map
	map_grid_y = y / TILE_SIZE; // get the y position in the map
	map_grid_a = a / TILE_SIZE;
	map_grid_b = b / TILE_SIZE;
	if (mlx->dt->map[map_grid_y][map_grid_x] == '1'
		 || mlx->dt->map[map_grid_b][mlx->player->x / TILE_SIZE] == '1'
		 || mlx->dt->map[mlx->player->y / TILE_SIZE][map_grid_a] == '1')  // check the wall hit and the diagonal wall hit
		return ;
	else if (mlx->dt->map[map_grid_y][map_grid_x] == 'd'
		|| mlx->dt->map[map_grid_y][mlx->player->x / TILE_SIZE] == 'd'
		|| mlx->dt->map[mlx->player->y / TILE_SIZE][map_grid_x] == 'd') // check the wall hit and the diagonal wall hit
		return ;
	mlx->player->x = x; // move the player
	mlx->player->y = y; // move the player
}

void	rotation_move(t_mlx *mlx, int32_t direction)
{
	mlx->player->angle += ROTATION_SPEED * direction;
	if (mlx->player->angle < 0 || mlx->player->angle > 2 * M_PI)
		mlx->player->angle += 2 * M_PI * -direction;
}

static void	vertical_move(t_mlx *mlx, int32_t direction)
{
	float	x;
	float	y;
	float	a;
	float	b;

	x = (direction * (cos(mlx->player->angle)));
	y = (direction * (sin(mlx->player->angle)));
	a = x * (PLAYER_SPEED * PLAYER_SIZE + mlx->player->run * PLAYER_SPEED);
	b = y * (PLAYER_SPEED * PLAYER_SIZE + mlx->player->run * PLAYER_SPEED);
	move(mlx, x * (PLAYER_SPEED + mlx->player->run * PLAYER_SPEED), y * (PLAYER_SPEED + PLAYER_SPEED * mlx->player->run), a, b);
}

static void	horizontal_move(t_mlx *mlx, int32_t direction)
{
	float	x;
	float	y;
	float	a;
	float	b;

	x = (-direction * (sin(mlx->player->angle)));
	y = (direction * (cos(mlx->player->angle)));
	a = x * (PLAYER_SPEED * PLAYER_SIZE + mlx->player->run * PLAYER_SPEED);
	b = y * (PLAYER_SPEED * PLAYER_SIZE + mlx->player->run * PLAYER_SPEED);
	move(mlx, x * (PLAYER_SPEED + mlx->player->run * PLAYER_SPEED), y * (PLAYER_SPEED + PLAYER_SPEED * mlx->player->run), a, b);
}

void	hook(t_mlx *mlx)
{
	mlx->player->run = false;
	if (mlx_is_key_down(mlx->mlx_p, MLX_KEY_LEFT_SHIFT))
		mlx->player->run = true;
	if (mlx_is_key_down(mlx->mlx_p, MLX_KEY_W))
		vertical_move(mlx, POSITIVE);
	else if (mlx_is_key_down(mlx->mlx_p, MLX_KEY_S))
		vertical_move(mlx, NEGATIVE);
	if (mlx_is_key_down(mlx->mlx_p, MLX_KEY_D))
		horizontal_move(mlx, POSITIVE);
	else if (mlx_is_key_down(mlx->mlx_p, MLX_KEY_A))
		horizontal_move(mlx, NEGATIVE);
	if (mlx_is_key_down(mlx->mlx_p, MLX_KEY_RIGHT))
		rotation_move(mlx, POSITIVE);
	else if (mlx_is_key_down(mlx->mlx_p, MLX_KEY_LEFT))
		rotation_move(mlx, NEGATIVE);
}
