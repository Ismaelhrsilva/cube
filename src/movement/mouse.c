/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:25:27 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/02 16:17:36 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"

void	mouse(double xpos, double ypos, void *param)
{
	t_mlx	*mlx;
	int32_t	x;
	int32_t	y;

	mlx = (t_mlx *) param;
	y = 0;
	(void)ypos;
	mlx_get_mouse_pos(mlx->p, &x, &y);
	if (x < 25 || x > mlx->p->width - 25)
		mlx_set_mouse_pos(mlx->p, mlx->p->width / 2, mlx->p->height / 2);
	if ((double) x > xpos)
		rotation_move(mlx, POSITIVE);
	else if ((double)x < xpos)
		rotation_move(mlx, NEGATIVE);
}
