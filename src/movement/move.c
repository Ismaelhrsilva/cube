/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:24:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/17 08:51:28 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <math.h>
#include <stdint.h>

void	rotate_player(t_mlx *mlx, int i)	// rotate the player
{
	mlx->player->angle += (ROTATION_SPEED * i);
	if (mlx->player->angle < 0 || mlx->player->angle > 2 * M_PI)
		mlx->player->angle += 2 * M_PI * -i;
	//if (i == 1)
	//{
	//	//mlx->player->angle += ROTATION_SPEED; // rotate right
	//	if (mlx->player->angle > 2 * M_PI)
	//		mlx->player->angle -= 2 * M_PI;
	//}
	//else
	//{
	//	//mlx->player->angle -= ROTATION_SPEED; // rotate left
	//	if (mlx->player->angle < 0)
	//		mlx->player->angle += 2 * M_PI;
	//}
}

void	move_player(t_mlx *mlx, double move_x, double move_y)	// move the player
{
	int32_t	map_grid_y;
	int32_t	map_grid_x;
	int32_t	new_x;
	int32_t	new_y;

	new_x = roundf(mlx->player->x + move_x); // get the new x position
	new_y = roundf(mlx->player->y + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
	if (mlx->dt->map[map_grid_y][map_grid_x] != '1' && \
	(mlx->dt->map[map_grid_y][mlx->player->x / TILE_SIZE] != '1' && \
	mlx->dt->map[mlx->player->y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		mlx->player->x = new_x; // move the player
		mlx->player->y = new_y; // move the player
	}
}

void	hook(t_mlx *mlx, double move_x, double move_y)	// hook the player
{
	if (mlx->player->rot != 0)
		rotate_player(mlx, mlx->player->rot);
	else if (mlx->player->l_r != 0)
	{
		move_x = (-mlx->player->l_r * sin(mlx->player->angle)) * PLAYER_SPEED;
		move_y = (mlx->player->l_r * cos(mlx->player->angle)) * PLAYER_SPEED;
	}
	//if (mlx->player->l_r == 1) //move right
	//{
	//	move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
	//	move_y = cos(mlx->player->angle) * PLAYER_SPEED;
	//}
	//if (mlx->player->l_r == -1) //move left
	//{
	//	move_x = sin(mlx->player->angle) * PLAYER_SPEED;
	//	move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
	//}
	else if (mlx->player->u_d != 0)
	{
		move_x = mlx->player->u_d * (cos(mlx->player->angle) * PLAYER_SPEED);
		move_y = mlx->player->u_d * (sin(mlx->player->angle) * PLAYER_SPEED);
	}
	//if (mlx->player->u_d == 1) //move up
	//{
	//	move_x = cos(mlx->player->angle) * PLAYER_SPEED;
	//	move_y = sin(mlx->player->angle) * PLAYER_SPEED;
	//}
	//if (mlx->player->u_d == -1) //move down
	//{
	//	move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
	//	move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
	//}
	move_player(mlx, move_x, move_y); // move the player
}
