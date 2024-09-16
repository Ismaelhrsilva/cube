/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:25:38 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/15 17:41:24 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "MLX42.h"
#include <math.h>

uint32_t	get_texture_color(mlx_texture_t *texture, int y, int x)
{
	int		texture_pos;
	uint8_t	*pixel;

	if (x < 0 || x >= (int)texture->width || y < 0
		|| y >= (int)texture->height)
		return (0);
	texture_pos = y * texture->width + x;
	texture_pos *= texture->bytes_per_pixel;
	pixel = &texture->pixels[texture_pos];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}


void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)	// put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= S_W)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color); // put the pixel
}

float	nor_angle(float angle)	// normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;

	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(mlx, ray, i++, 0xB99470FF); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, 0x89CFF3FF); // ceiling
}


static void	intersection_point(t_mlx *mlx)
{
	if (mlx->ray->flag == 0)
		mlx->dt->point_x = mlx->ply->plyr_y + mlx->ray->distance * mlx->ray->ray_ngl;
		//mlx->dt->point_x = mlx->ply->plyr_y + mlx->ray->distance * ray->dir.y;
	else
		mlx->dt->point_x = mlx->ply->plyr_x + mlx->ray->distance * mlx->ray->ray_ngl;
		//mlx->dt->point_x = mlx->ply->plyr_x + mlx->ray->distance * ray->dir.x;
	mlx->dt->point_x -= floor(mlx->dt->point_x);
}

static void	find_texture_position_x(t_mlx *mlx)
{
	mlx->dt->texture_x = (int)(mlx->dt->point_x * mlx->dt->wall_text->width);
	if (mlx->ray->flag == 0)
		mlx->dt->texture_x = mlx->dt->wall_text->width - mlx->dt->texture_x - 1;
	mlx->dt->texture_step = 1.0 * mlx->dt->wall_text->height / mlx->dt->wall_height;
}

static void	render_wall_2(t_mlx *mlx, int pixel)
{
	int			y;
	int			texture_y;
	uint32_t	color;

	y = mlx->dt->wall_line_start_y;
	while (y < mlx->dt->wall_line_end_y)
	{
		texture_y = (int)mlx->dt->texture_pos;
		if (texture_y < 0)
			texture_y = 0;
		if (texture_y >= (int)mlx->dt->wall_text->height)
			texture_y = mlx->dt->wall_text->height - 1;
		mlx->dt->texture_pos += mlx->dt->texture_step;
		color = get_texture_color(mlx->dt->wall_text, texture_y, mlx->dt->texture_x);
		my_mlx_pixel_put(mlx, pixel, y, color);
		y++;
	}
}

void	draw_wall(t_mlx *mlx, int pixel)
{
	mlx->dt->wall_height = (S_H / mlx->ray->distance);
	mlx->dt->wall_line_start_y = (S_H / 2 - mlx->dt->wall_height / 2);
	mlx->dt->wall_line_end_y = (S_H / 2 + mlx->dt->wall_height / 2);
	if (mlx->dt->wall_line_start_y < 0)
		mlx->dt->wall_line_start_y = 0;
	if (mlx->dt->wall_line_end_y >= S_H)
		mlx->dt->wall_line_end_y = S_H - 1;
	intersection_point(mlx);
	find_texture_position_x(mlx);
	mlx->dt->texture_pos = (mlx->dt->wall_line_start_y - S_H / 2 + mlx->dt->wall_height / 2)
		* mlx->dt->texture_step;
	render_wall_2(mlx, pixel);
}

void	render_wall(t_mlx *mlx, int ray)	// render the wall
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle)); // fix the fisheye
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2)); // get the wall height
	b_pix = (S_H / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (S_H / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > S_H) // check the bottom pixel
		b_pix = S_H;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(mlx, ray);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
}

/*static void	intersection_point(t_mlx *mlx)
{
	if (ray->hit_side == 0)
		wall->point_x = game->pos.y + ray->perp_dist * ray->dir.y;
	else
		wall->point_x = game->pos.x + ray->perp_dist * ray->dir.x;
	mlx->dt->point_x -= floor(mlx->dt->point_x);
}

static void	find_texture_position_x(t_mlx *mlx)
{
	mlx->dt->texture_x = (int)(mlx->dt->point_x * mlx->dt->wall_text->width);
	if ((ray->hit_side == 0 && ray->dir.x < 0)
		|| (ray->hit_side == 1 && ray->dir.y > 0))
		wall->texture_x = game->texture->width - wall->texture_x - 1;
	mlx->dt->texture_step = 1.0 * mlx->dt->wall_text->height / mlx->dt->wall_height;
}*/
