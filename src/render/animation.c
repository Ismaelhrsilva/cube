/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:09:23 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/02 16:28:44 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	reverse_bytes(int c);

mlx_texture_t	*construct_texture(char *png)
{
	mlx_texture_t	*temp;
	int32_t			fd;

	fd = open(png, O_RDONLY, 0644);
	if (fd == -1)
		exit (100);
	close(fd);
	temp = mlx_load_png(png);
	if (!temp)
		exit(100);
	return (temp);
}

static void	draw_animation(t_mlx *mlx, uint8_t frame)
{
	uint32_t	*pixels;
	uint32_t	x;
	uint32_t	y;

	pixels = (uint32_t *) mlx->data->texture->pixels;
	y = 0;
	while (y < mlx->data->animation->height)
	{
		x = 0;
		while (x < mlx->data->animation->width)
		{
			mlx_put_pixel(mlx->data->animation, x, y,
				reverse_bytes(
					pixels[y * mlx->data->texture->width + \
					mlx->data->animation->width * frame + x]));
			x++;
		}
		y++;
	}
}

static void	init_image(t_mlx *mlx)
{
	mlx_delete_image(mlx->p, mlx->data->animation);
	if (!mlx->data->texture)
		mlx->data->texture = construct_texture("./assets/weapon.png");
	mlx->data->animation = mlx_new_image(mlx->p, 600, 430);
	mlx_image_to_window(mlx->p, mlx->data->animation,
		mlx->p->width - 600, mlx->p->height - 430);
	mlx->data->animation->instances[0].z = 3;
	mlx->data->animation->enabled = true;
	draw_animation(mlx, 0);
}

void	animation(t_mlx *mlx)
{
	static int32_t	width;
	static int32_t	height;

	if (mlx->p->width != width || mlx->p->height != height)
		init_image(mlx);
	width = mlx->p->width;
	height = mlx->p->height;
	if (mlx->data->frame < 1 || mlx->data->frame > 15)
		return ;
	draw_animation(mlx, mlx->data->frame);
	mlx->data->frame = (int)((mlx_get_time() - mlx->data->time + 1) * 18) % 16;
}
