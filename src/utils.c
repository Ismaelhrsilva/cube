/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:30:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/07 16:50:09 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

void	ft_exit(t_mlx *mlx) 		// exit the game
{
	int	i = 0;
	while (mlx->dt->map2d[i])
		free(mlx->dt->map2d[i++]); // free the map line by line
	free(mlx->dt->map2d); // free the map
	free(mlx->dt); // free the data structure
	free(mlx->ply); // free the player structure
	free(mlx->ray); // free the ray structure
	mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
	mlx_close_window(mlx->mlx_p); // close the window
	mlx_terminate(mlx->mlx_p); // terminate the mlx pointer
	printf("Game closed\n"); // print the message
	exit(0); // exit the game
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
