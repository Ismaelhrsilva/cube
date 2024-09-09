/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:25:27 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/09 20:04:39 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

void	ft_rotate_player(t_mlx *mlx, int i)	// rotate the player
{
	if (i == 1)
	{
		mlx->ply->angle += ROTATION_SPEED; // rotate right
		if (mlx->ply->angle > 2 * M_PI)
			mlx->ply->angle -= 2 * M_PI;
	}
	else
	{
		mlx->ply->angle -= ROTATION_SPEED; // rotate left
		if (mlx->ply->angle < 0)
			mlx->ply->angle += 2 * M_PI;
	}
}

void ft_mouse(double xpos, double ypos, void *ml)
{
	t_mlx	*mlx;
	int32_t	x;
	int32_t y;

	mlx = ml;
	y = 0;
	ypos = 0;

	mlx_get_mouse_pos(mlx->mlx_p, &x, &y); // relativo a posição do player na hora;
	if ((double)x > xpos)
		ft_rotate_player(mlx, 1);
	else if ((double)x < xpos)
		ft_rotate_player(mlx, 0);
	if (x <= 0 || x >= S_W)
		mlx_set_mouse_pos(mlx->mlx_p, S_W / 2 , S_H / 2); // relativo a posição do player na hora;
}
