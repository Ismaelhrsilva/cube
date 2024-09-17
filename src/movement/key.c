/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:43:50 by rde-mour          #+#    #+#             */
/*   Updated: 2024/09/16 22:53:11 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <stdint.h>

static void	key_press(t_mlx *mlx, uint32_t key)
{
	if (key == MLX_KEY_ESCAPE || key == MLX_KEY_Q)
		ft_exit(mlx);
	else if (key == MLX_KEY_A)
		mlx->player->l_r = -1;
	else if (key == MLX_KEY_D)
		mlx->player->l_r = 1;
	else if (key == MLX_KEY_S || key == MLX_KEY_DOWN)
		mlx->player->u_d = -1;
	else if (key == MLX_KEY_W || key == MLX_KEY_UP)
		mlx->player->u_d = 1;
	else if (key == MLX_KEY_LEFT)
		mlx->player->rot = -1;
	else if (key == MLX_KEY_RIGHT)
		mlx->player->rot = 1;
	else if (key == MLX_KEY_M)
		ft_minimap(mlx);
}

static void	key_release(t_mlx *mlx, uint32_t key)
{
	if (key == MLX_KEY_A || key == MLX_KEY_D)
		mlx->player->l_r = 0;
	else if (key == MLX_KEY_S || key == MLX_KEY_W)
		mlx->player->u_d = 0;
	else if (key == MLX_KEY_UP || key == MLX_KEY_DOWN)
		mlx->player->u_d = 0;
	else if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
		mlx->player->rot = 0;
}

void	mlx_key(mlx_key_data_t keydata, void *mlx)
{
	if (keydata.action == MLX_PRESS)
		key_press((t_mlx *) mlx, keydata.key);
	if (keydata.action == MLX_RELEASE)
		key_release((t_mlx *) mlx, keydata.key);
}
