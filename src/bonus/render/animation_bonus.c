/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:09:23 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/17 16:27:06 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"
#include "libft.h"
#include "MLX42.h"
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

int	reverse_bytes(int c);

mlx_texture_t	*construct_texture(t_mlx *mlx, char *png)
{
	mlx_texture_t	*tmp;
	int32_t			fd;
	int				len;

	len = ft_strlen(png);
	if (len < 4 || ft_strncmp(&png[len - 4], ".png", 5) != 0)
		gameover(mlx, ft_strdup("Invalid .png texture"), 1);
	fd = open(png, O_RDONLY, 0644);
	if (fd < 1)
		gameover(mlx, ft_strdup("Impossible to load texture"), 1);
	close(fd);
	tmp = mlx_load_png(png);
	if (!tmp)
		gameover(mlx, ft_strdup("Failed to load texture"), 1);
	return (tmp);
}

static void	draw_animation(t_mlx *mlx, uint8_t frame)
{
	uint32_t	*pixels;
	uint32_t	x;
	uint32_t	y;

	if (frame > 15)
		return ;
	pixels = (uint32_t *) mlx->data->texture->pixels;
	y = 0;
	while (y < mlx->data->animation->height - 1)
	{
		x = 0;
		while (x < mlx->data->animation->width - 1)
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
		mlx->data->texture = construct_texture(mlx, "./assets/weapon.png");
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
