/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:09:23 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/18 20:47:58 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"

mlx_texture_t *construct_texture(t_mlx *mlx, char *png)
{
	mlx_texture_t	*temp;

	(void )mlx;
	temp = mlx_load_png(png);
	return (temp);
}

void	ft_animation(t_mlx *mlx)
{
	double	time;

	time = mlx_get_time();
	if (mlx->dt->animation1)
		mlx_delete_image(mlx->mlx_p, mlx->dt->animation1);
	if (mlx->dt->animation2)
		mlx_delete_image(mlx->mlx_p, mlx->dt->animation2);
	mlx->dt->texture1 = construct_texture(mlx, ANIMATION1);
	mlx->dt->texture2 = construct_texture(mlx, ANIMATION2);
	mlx->dt->animation1 = mlx_texture_to_image(mlx->mlx_p, mlx->dt->texture1);
	mlx->dt->animation2 = mlx_texture_to_image(mlx->mlx_p, mlx->dt->texture2);
	mlx_resize_image(mlx->dt->animation1, 250, 250);
	mlx_resize_image(mlx->dt->animation2, 250, 250);
	mlx_image_to_window(mlx->mlx_p, mlx->dt->animation1, 250, 350);
	mlx_image_to_window(mlx->mlx_p, mlx->dt->animation2, 250, 350);
	mlx->dt->animation1->instances[0].z = 3;
	mlx->dt->animation2->instances[0].z = 4;
	if ((int)time % 2 == 0)
	{
		mlx->dt->animation1->enabled = false;
		mlx->dt->animation2->enabled = true;
	}
	else
	{
		mlx->dt->animation2->enabled = false;
		mlx->dt->animation1->enabled = true;
	}
}
