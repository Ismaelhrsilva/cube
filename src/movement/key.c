/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:43:50 by rde-mour          #+#    #+#             */
/*   Updated: 2024/09/28 12:17:07 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"

void	mlx_key(mlx_key_data_t keydata, void *mlx)
{
	if (keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
		ft_exit((t_mlx *) mlx);
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if (((t_mlx *) mlx)->dt->frame > 0 && ((t_mlx *) mlx)->dt->frame < 16)
			return ;
		((t_mlx *) mlx)->dt->frame = 1;
		((t_mlx *) mlx)->dt->time = mlx_get_time();
	}
	else if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		ft_minimap(mlx);
	else if (keydata.key == MLX_KEY_F11 && keydata.action == MLX_PRESS)
		mlx_set_setting(MLX_FULLSCREEN, true);
	else if (keydata.key == MLX_KEY_N && keydata.action == MLX_PRESS)
		ft_open_door(mlx);
}
