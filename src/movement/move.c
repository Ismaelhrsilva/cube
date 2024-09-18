/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:24:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/17 10:28:59 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <math.h>
#include <stdint.h>

static void	move(t_mlx *mlx, double x, double y)	// move the player
{
	int32_t	map_grid_y;
	int32_t	map_grid_x;

	x = round(mlx->player->x + x); // get the new x position
	y = round(mlx->player->y + y); // get the new y position
	map_grid_x = (x / TILE_SIZE); // get the x position in the map
	map_grid_y = (y / TILE_SIZE); // get the y position in the map
	if (mlx->dt->map[map_grid_y][map_grid_x] == '1'
		|| mlx->dt->map[map_grid_y][mlx->player->x / TILE_SIZE] == '1'
		|| mlx->dt->map[mlx->player->y / TILE_SIZE][map_grid_x] == '1') // check the wall hit and the diagonal wall hit
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
	double	x;
	double	y;

	x = direction * (cos(mlx->player->angle) * PLAYER_SPEED);
	y = direction * (sin(mlx->player->angle) * PLAYER_SPEED);
	move(mlx, x, y);
}

static void	horizontal_move(t_mlx *mlx, int32_t direction)
{
	double	x;
	double	y;

	x = (-direction * (sin(mlx->player->angle)) * PLAYER_SPEED);
	y = (direction * (cos(mlx->player->angle)) * PLAYER_SPEED);
	move(mlx, x, y);
}

void	hook(t_mlx *mlx)
{
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
