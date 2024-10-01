/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:09:23 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/01 10:29:03 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	reverse_bytes(int c);

mlx_texture_t *construct_texture(t_mlx *mlx, char *png)
{
	mlx_texture_t	*temp;

	int fd = open(png, O_RDONLY, 0644);
	if (fd == -1)
		exit (100);
	close(fd);
	temp = mlx_load_png(png);
	if (!temp)
		return (mlx->data->wall_text);
	return (temp);
}

static void	draw_animation(t_mlx *mlx, uint8_t frame)
{
	uint32_t	*pixels;
	uint32_t	x;
	uint32_t	y;

	pixels = (uint32_t *) mlx->data->texture1->pixels;
	y = 0;
	while (y < mlx->data->animation1->height)
	{
		x = 0;
		while (x < mlx->data->animation1->width)
		{
			mlx_put_pixel(mlx->data->animation1, x, y,
				reverse_bytes(
					pixels[y * mlx->data->texture1->width + \
					mlx->data->animation1->width * frame + x]));
			x++;
		}
		y++;
	}
}

void	ft_init_animation(t_mlx *mlx)
{
	mlx->data->texture1 = construct_texture(mlx, "./assets/weapon/weapon.png");
	mlx->data->animation1 = mlx_new_image(mlx->p, 600, 430);
	mlx_image_to_window(mlx->p, mlx->data->animation1, mlx->p->width - 600, mlx->p->height - 430);
	mlx->data->animation1->instances[0].z = 3;
	mlx->data->animation1->enabled = true;
	draw_animation(mlx, 0);
}

void	ft_animation(t_mlx *mlx)
{
	if (mlx->data->frame < 1 || mlx->data->frame > 15)
		return ;
	draw_animation(mlx, mlx->data->frame);
	mlx->data->frame = (uint8_t) ((mlx_get_time() - mlx->data->time + 1) * 18) % 16;
}
