/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:43:50 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/09 19:36:15 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"
#include "libft.h"
#include "MLX42.h"

void	key(mlx_key_data_t keydata, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) param;
	if (keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
		gameover(mlx, ft_strdup("Game closed"), 0);
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if (mlx->data->frame > 0 && mlx->data->frame < 16)
			return ;
		mlx->data->frame = 1;
		mlx->data->time = mlx_get_time();
	}
	else if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
		minimap(mlx);
	else if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		door(mlx);
}
