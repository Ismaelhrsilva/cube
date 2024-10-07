/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:30:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/07 15:50:21 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include "MLX42.h"
#include <stdlib.h>

static void	delete_textures(t_mlx *mlx)
{
	if (mlx->data->texture)
		mlx_delete_texture(mlx->data->texture);
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
}

static void	clear(t_mlx *mlx, uint8_t status)
{
	clear_map(mlx->data->parser);
	delete_textures(mlx);
	if (mlx->data)
		free(mlx->data);
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
	exit(status);
}

void	gameover(t_mlx *mlx, char *message, uint8_t status)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	free(message);
	clear(mlx, status);
}
