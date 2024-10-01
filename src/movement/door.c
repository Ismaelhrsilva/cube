/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:25:49 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/01 10:42:37 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include <math.h>

void	ft_open_door(t_mlx *mlx)
{
	int32_t	map_y;
	int32_t	map_x;
	double	x;
	double	y;

	if (ft_strchr("Dd", mlx->data->map[mlx->player->y / TILE_SIZE][mlx->player->x / TILE_SIZE]))
		return ;
	x = POSITIVE * (cos(mlx->player->angle) * PLAYER_SPEED) * 12;
	y = POSITIVE * (sin(mlx->player->angle) * PLAYER_SPEED) * 12;


	x = round(mlx->player->x + x); // get the new x position
	y = round(mlx->player->y + y); // get the new y position
	map_x = (x / TILE_SIZE); // get the x position in the map
	map_y = (y / TILE_SIZE); // get the y position in the map
	//if (mlx->data->map[map_y][map_x] == 'D')
	//	mlx->data->map[map_y][map_x] = 'd';
	//else if (mlx->data->map[map_y][map_x] == 'd')
	//	mlx->data->map[map_y][map_x] = 'D';
	if (ft_strchr("Dd", mlx->data->map[map_y][map_x]))
		mlx->data->map[map_y][map_x] ^= 32;
}
