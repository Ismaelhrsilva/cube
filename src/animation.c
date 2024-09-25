/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:09:23 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/25 15:58:58 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int	reverse_bytes(int c);

mlx_texture_t *construct_texture(t_mlx *mlx, char *png)
{
	mlx_texture_t	*temp;

	(void )mlx;
	temp = mlx_load_png(png);
	if (!temp)
		return (mlx->dt->wall_text);
	return (temp);
}

static void	draw_animation(t_mlx *mlx, uint8_t frame)
{
	uint32_t	*pixels;
	uint32_t	x;
	uint32_t	y;

	pixels = (uint32_t *) mlx->dt->texture1->pixels;
	y = 0;
	while (y < mlx->dt->animation1->height)
	{
		x = 0;
		while (x < mlx->dt->animation1->width)
		{
			mlx_put_pixel(mlx->dt->animation1, x, y,
				reverse_bytes(
					pixels[y * mlx->dt->texture1->width + \
					mlx->dt->animation1->width * frame + x]));
			x++;
		}
		y++;
	}
}

void	ft_init_animation(t_mlx *mlx)
{
	mlx->dt->texture1 = construct_texture(mlx, "./assets/weapon/weapon.png");
	mlx->dt->animation1 = mlx_new_image(mlx->mlx_p, 600, 430);
	mlx_image_to_window(mlx->mlx_p, mlx->dt->animation1, mlx->mlx_p->width - 600, mlx->mlx_p->height - 430);
	mlx->dt->animation1->instances[0].z = 3;
	mlx->dt->animation1->enabled = true;
	draw_animation(mlx, 0);
}

void	ft_animation(t_mlx *mlx)
{
	if (mlx->dt->frame < 1 || mlx->dt->frame > 15)
		return ;
	draw_animation(mlx, mlx->dt->frame);
	mlx->dt->frame = (uint8_t) ((mlx_get_time() - mlx->dt->time + 1) * 18) % 16;
}
