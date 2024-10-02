/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:25:49 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/02 18:13:08 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include <math.h>

void	door(t_mlx *mlx)
{
	int32_t	map_y;
	int32_t	map_x;
	double	x;
	double	y;

	map_x = mlx->player->x / TILE_SIZE;
	map_y = mlx->player->y / TILE_SIZE;
	if (ft_strchr("Dd", mlx->data->map[map_y][map_x]))
		return ;
	x = POSITIVE * (cos(mlx->player->angle) * SPEED) * 20;
	y = POSITIVE * (sin(mlx->player->angle) * SPEED) * 20;
	x = floor(mlx->player->x + x);
	y = floor(mlx->player->y + y);
	map_x = (x / TILE_SIZE);
	map_y = (y / TILE_SIZE);
	if (ft_strchr("Dd", mlx->data->map[map_y][map_x]))
		mlx->data->map[map_y][map_x] ^= 32;
}
