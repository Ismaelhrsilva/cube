/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:16:17 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/16 14:50:44 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"
#include "parser_bonus.h"
#include "libft.h"
#include <stdint.h>
#include <unistd.h>

void	validate_file(char *path)
{
	char	*message;
	int		len;

	len = ft_strlen(path);
	if (len > 3 && ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 5) == 0)
		return ;
	ft_sprintf(&message, "The %s is a invalid file .cub", path);
	panic(NULL, message, 1);
}

static void	check_line(t_map *map, char *line)
{
	static uint32_t	player;
	uint32_t		i;
	char			*message;

	message = NULL;
	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" 01NSWED", line[i]))
		{
			ft_sprintf(&message, "Invalid character: %c", line[i]);
			panic(map, message, 1);
		}
		if (ft_strrchr("NSWE", line[i]))
			player++;
		i++;
	}
	if (player > 1)
		panic(map, ft_strdup("Double player"), 1);
}

void	validate_map(t_map	*map)
{
	char		*tmp;
	uint32_t	size;
	uint32_t	i;

	i = 0;
	while (map->map[i])
	{
		size = ft_strlen(map->map[i]) - 1;
		tmp = (char *) malloc(map->width * sizeof(char) + 1);
		if (!tmp)
			panic(map, ft_strdup("Failed to allocate memory"), 1);
		ft_memmove(tmp, map->map[i], size);
		ft_memset(&tmp[size], ' ', map->width - size);
		tmp[map->width] = '\0';
		free(map->map[i]);
		map->map[i] = tmp;
		check_line(map, map->map[i]);
		i++;
	}
}

void	validate_color(t_map *map)
{
	if (!(map->ceilling & 0xFF))
		panic(map, ft_strdup("ceilling not infomed"), 1);
	if (!(map->floor & 0xFF))
		panic(map, ft_strdup("Floor not informed"), 1);
}

void	validate_floodfill(t_map *map)
{
	int32_t	x;
	int32_t	y;

	x = map->player[0];
	y = map->player[1];
	if (x < 0 || y < 0 || x > map->width || y > map->height)
		panic(map, ft_strdup("Player out of bound"), 1);
	floodfill(map, x, y);
}
