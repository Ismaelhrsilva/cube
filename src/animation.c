/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:09:23 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/23 17:19:38 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <stdlib.h>

mlx_texture_t *construct_texture(t_mlx *mlx, char *png)
{
	mlx_texture_t	*temp;

	(void )mlx;
	temp = mlx_load_png(png);
	if (!temp)
		return (mlx->dt->wall_text);
	return (temp);
}

void	ft_init_animation(t_mlx *mlx)
{
	double	time;

	time = mlx_get_time();
	(void) time;
	mlx_delete_image(mlx->mlx_p, mlx->dt->animation1);
	mlx_delete_image(mlx->mlx_p, mlx->dt->animation2);
	mlx->dt->texture1 = construct_texture(mlx, ANIMATION1);
	mlx->dt->texture2 = construct_texture(mlx, ANIMATION2);
	mlx->dt->animation1 = mlx_texture_to_image(mlx->mlx_p, mlx->dt->texture1);
	mlx->dt->animation2 = mlx_texture_to_image(mlx->mlx_p, mlx->dt->texture2);
	mlx_resize_image(mlx->dt->animation1, 150, 150);
	mlx_resize_image(mlx->dt->animation2, 150, 150);
}

void	ft_animation(t_mlx *mlx)
{
	double	time;

	time = mlx_get_time();
	mlx_image_to_window(mlx->mlx_p, mlx->dt->animation1, 250, 450);
	mlx_image_to_window(mlx->mlx_p, mlx->dt->animation2, 250, 450);
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
