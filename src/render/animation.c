/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:09:23 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/12 10:42:35 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include "MLX42.h"
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

int	reverse_bytes(int c);

void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x > img->width || y > img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

mlx_texture_t	*construct_texture(t_mlx *mlx, char *png)
{
	mlx_texture_t	*tmp;
	int32_t			fd;

	if (ft_strncmp(&png[ft_strlen(png) - 4], ".png", 5) != 0)
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
