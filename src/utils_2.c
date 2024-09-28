/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:25:38 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/28 12:08:30 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// put a pixel inside of the limits of mlx image
void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0 || x >= S_W || y < 0 || y > S_W)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

// normalize the angle
float	nor_angle(float angle)
{
	if (angle < 0)
		return (angle + (2 * M_PI));
	if (angle > (2 * M_PI))
		return (angle - (2 * M_PI));
	return (angle);
}

// draw the floor and the ceiling
void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int	i;

	i = 0;
	while (i < S_H)
	{
		if (i < t_pix)
			put_pixel(mlx, ray, i, mlx->dt->sky);
		else if (i >= b_pix)
			put_pixel(mlx, ray, i, mlx->dt->floor);
		i++;
	}
}
