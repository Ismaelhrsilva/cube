/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:30:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/28 12:17:20 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void	ft_exit(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->dt->map[i])
		free(mlx->dt->map[i++]);
	free(mlx->dt->map);
	free(mlx->dt);
	free(mlx->player);
	free(mlx->ray);
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx_close_window(mlx->mlx_p);
	mlx_terminate(mlx->mlx_p);
	printf("Game closed\n");
	exit(0);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	pytheorem(float a, float b)
{
	return (sqrt((a * a) + (b * b)));
}

int	horizontal_unit_circle(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int	vertical_unit_circle(float angle)
{
	return (angle > (M_PI / 2) && angle < (3 * M_PI) / 2);
}
