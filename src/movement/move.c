/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:24:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/16 22:15:26 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <math.h>
#include <stdint.h>

void	rotate_player(t_mlx *mlx, int i)	// rotate the player
{
	mlx->ply->angle += (ROTATION_SPEED * i);
	if (mlx->ply->angle < 0 || mlx->ply->angle > 2 * M_PI)
		mlx->ply->angle += 2 * M_PI * -i;
	//if (i == 1)
	//{
	//	//mlx->ply->angle += ROTATION_SPEED; // rotate right
	//	if (mlx->ply->angle > 2 * M_PI)
	//		mlx->ply->angle -= 2 * M_PI;
	//}
	//else
	//{
	//	//mlx->ply->angle -= ROTATION_SPEED; // rotate left
	//	if (mlx->ply->angle < 0)
	//		mlx->ply->angle += 2 * M_PI;
	//}
}

void	move_player(t_mlx *mlx, double move_x, double move_y)	// move the player
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->ply->plyr_x + move_x); // get the new x position
	new_y = roundf(mlx->ply->plyr_y + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
	if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1' && \
	(mlx->dt->map2d[map_grid_y][mlx->ply->plyr_x / TILE_SIZE] != '1' && \
	mlx->dt->map2d[mlx->ply->plyr_y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		mlx->ply->plyr_x = new_x; // move the player
		mlx->ply->plyr_y = new_y; // move the player
	}
}

void	hook(t_mlx *mlx, double move_x, double move_y)	// hook the player
{
	if (mlx->ply->rot != 0)
		rotate_player(mlx, mlx->ply->rot);
	if (mlx->ply->l_r != 0)
	{
		move_x = (-mlx->ply->l_r * sin(mlx->ply->angle)) * PLAYER_SPEED;
		move_y = (mlx->ply->l_r * cos(mlx->ply->angle)) * PLAYER_SPEED;
	}
	//if (mlx->ply->l_r == 1) //move right
	//{
	//	move_x = -sin(mlx->ply->angle) * PLAYER_SPEED;
	//	move_y = cos(mlx->ply->angle) * PLAYER_SPEED;
	//}
	//if (mlx->ply->l_r == -1) //move left
	//{
	//	move_x = sin(mlx->ply->angle) * PLAYER_SPEED;
	//	move_y = -cos(mlx->ply->angle) * PLAYER_SPEED;
	//}
	if (mlx->ply->u_d != 0)
	{
		move_x = mlx->ply->u_d * (cos(mlx->ply->angle) * PLAYER_SPEED);
		move_y = mlx->ply->u_d * (sin(mlx->ply->angle) * PLAYER_SPEED);
	}
	//if (mlx->ply->u_d == 1) //move up
	//{
	//	move_x = cos(mlx->ply->angle) * PLAYER_SPEED;
	//	move_y = sin(mlx->ply->angle) * PLAYER_SPEED;
	//}
	//if (mlx->ply->u_d == -1) //move down
	//{
	//	move_x = -cos(mlx->ply->angle) * PLAYER_SPEED;
	//	move_y = -sin(mlx->ply->angle) * PLAYER_SPEED;
	//}
	move_player(mlx, move_x, move_y); // move the player
}
