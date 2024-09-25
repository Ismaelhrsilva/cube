/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:25:49 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/25 19:56:13 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "ft_stdlib.h"
#include "MLX42.h"
#include <stdio.h>
#include <math.h>

void	ft_open_door(t_mlx *mlx)
{
	int32_t	map_grid_y;
	int32_t	map_grid_x;

	double	x;
	double	y;
	x = POSITIVE * (cos(mlx->player->angle) * PLAYER_SPEED) * 20;
	y = POSITIVE * (sin(mlx->player->angle) * PLAYER_SPEED) * 20;

	x = round(mlx->player->x + x); // get the new x position
	y = round(mlx->player->y + y); // get the new y position
	map_grid_x = (x / TILE_SIZE); // get the x position in the map
	map_grid_y = (y / TILE_SIZE); // get the y position in the map
	if (mlx->dt->map[map_grid_y][map_grid_x] == 'D')
		mlx->dt->map[map_grid_y][map_grid_x] = 'd';
	else if (mlx->dt->map[map_grid_y][map_grid_x] == 'd')
		mlx->dt->map[map_grid_y][map_grid_x] = 'D';
}
