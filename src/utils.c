/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:30:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/02 19:52:11 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <stdlib.h>

#include <stdio.h>

void	ft_exit(t_mlx *mlx)
{
	if (mlx->data->texture)
		mlx_delete_texture(mlx->data->texture);
	clear_map(mlx->data->parser);
	if (mlx->data)
		free(mlx->data);
	if (mlx->texture->door)
		mlx_delete_texture(mlx->texture->door);
	if (mlx->texture->north)
		mlx_delete_texture(mlx->texture->north);
	if (mlx->texture->south)
		mlx_delete_texture(mlx->texture->south);
	if (mlx->texture->west)
		mlx_delete_texture(mlx->texture->west);
	if (mlx->texture->east)
		mlx_delete_texture(mlx->texture->east);
	if (mlx->texture)
		free(mlx->texture);
	if (mlx->minimap)
		free(mlx->minimap);
	if (mlx->player)
		free(mlx->player);
	if (mlx->ray)
		free(mlx->ray);
	if (mlx->p && mlx->img)
		mlx_delete_image(mlx->p, mlx->img);
	if (mlx->p)
		mlx_close_window(mlx->p);
	if (mlx->p)
		mlx_terminate(mlx->p);
	printf("Game closed\n");
	exit(0);
}
