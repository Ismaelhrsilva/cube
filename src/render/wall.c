/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:25:38 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/02 17:00:41 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <math.h>
#include <stdint.h>

float		normalize(float angle);
int			horizontal_unit_circle(float angle);
int			vertical_unit_circle(float angle);
uint32_t	reverse_bytes(unsigned int c);
void		put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int32_t	i;

	i = 0;
	while (i < mlx->p->height)
	{
		if (i < t_pix)
			put_pixel(mlx->img, ray, i, mlx->data->ceilling);
		else if (i >= b_pix)
			put_pixel(mlx->img, ray, i, mlx->data->floor);
		i++;
	}
}

mlx_texture_t	*get_texture(t_mlx *mlx)
{
	mlx->ray->angle = normalize(mlx->ray->angle);
	if (mlx->ray->door)
		return (mlx->texture->door);
	if (mlx->ray->y)
	{
		if (vertical_unit_circle(mlx->ray->angle))
			return (mlx->texture->west);
		return (mlx->texture->east);
	}
	if (horizontal_unit_circle(mlx->ray->angle))
		return (mlx->texture->south);
	return (mlx->texture->north);
}

double	get_x_o(mlx_texture_t *texture, t_mlx *mlx)
{
	double	x;
	double	width;

	width = (double) texture->width;
	if (mlx->ray->x)
		x = fmodf((mlx->ray->x * (width / TILE_SIZE)), width);
	else
		x = fmodf((mlx->ray->y * (width / TILE_SIZE)), width);
	if (texture == mlx->texture->south || texture == mlx->texture->west)
		return (width - x);
	return (x);
}

void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
	double			x;
	double			y;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(mlx);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x = get_x_o(texture, mlx);
	y = (t_pix - ((double) mlx->img->height / 2) + (wall_h / 2)) * factor;
	if (y < 0)
		y = 0;
	while (t_pix < b_pix)
	{
		put_pixel(mlx->img, mlx->ray->index, t_pix++,
			reverse_bytes(arr[(int) y * texture->width + (int) x]));
		y += factor;
	}
}

void	render_wall(t_mlx *mlx, int ray)
{
	float	wall_h;
	float	b_pix;
	float	t_pix;

	mlx->ray->distance *= cos(normalize(mlx->ray->angle - mlx->player->angle));
	wall_h = (TILE_SIZE / mlx->ray->distance) * (((float) mlx->img->width / 2)
			/ tan(mlx->player->fov / 2));
	b_pix = ((double) mlx->img->height / 2) + (wall_h / 2);
	t_pix = ((double) mlx->img->height / 2) - (wall_h / 2);
	if (b_pix > mlx->img->height)
		b_pix = mlx->img->height;
	if (t_pix < 0)
		t_pix = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, t_pix, b_pix, wall_h);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}
