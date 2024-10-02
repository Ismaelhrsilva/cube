/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:30:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/02 16:42:16 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <stdlib.h>

#include <stdio.h>

void	ft_exit(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->data->map[i])
		free(mlx->data->map[i++]);
	free(mlx->data->map);
	free(mlx->data);
	free(mlx->player);
	free(mlx->ray);
	mlx_delete_image(mlx->p, mlx->img);
	mlx_close_window(mlx->p);
	mlx_terminate(mlx->p);
	printf("Game closed\n");
	exit(0);
}
