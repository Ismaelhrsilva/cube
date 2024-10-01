/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:25:27 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/01 10:25:56 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"

#include <stdio.h>
void ft_mouse(double xpos, double ypos, void *ml)
{
	t_mlx	*mlx;
	int32_t	x;
	int32_t y;

	mlx = ml;
	y = 0;
	(void)ypos;

	mlx_get_mouse_pos(mlx->p, &x, &y); // relativo a posição do player na hora;
	//if ((double) x != xpos)
	//	rotation_move(mlx, ((int32_t)(x - xpos) >> (sizeof(int32_t) * 8 - 1)) | 1);
	if ((double)x > xpos)
		rotation_move(mlx, POSITIVE);
	else if ((double)x < xpos)
		rotation_move(mlx, NEGATIVE);
	if (x < 25 || x > S_W - 25)
		mlx_set_mouse_pos(mlx->p, S_W / 2 , S_H / 2); // relativo a posição do player na hora
}
