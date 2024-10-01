/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:16:17 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/01 11:07:17 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "parser.h"
#include "libft.h"
#include <stdint.h>
#include <stdbool.h>

_Bool	validate_file(char *path)
{
	if (ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 5) != 0)
		return (false);
	return (true);
}

static _Bool	check_line(char *line)
{
	static uint32_t	player;
	uint32_t		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" 01NSWED", line[i]))
			return (false);
		if (ft_strrchr("NSWE", line[i]))
			player++;
		i++;
	}
	if (player > 1)
		return (false);
	return (true);
}

_Bool	validate_map(t_map	*map)
{
	char		*tmp;
	uint32_t	size;
	uint32_t	i;

	if (!map->map)
		return (false);
	i = 0;
	while (map->map[i])
	{
		size = ft_strlen(map->map[i]) - 1;
		tmp = (char *) malloc(map->width * sizeof(char) + 1);
		if (!tmp)
			exit(1);
		ft_memmove(tmp, map->map[i], size);
		ft_memset(&tmp[size], ' ', map->width - size);
		tmp[map->width] = '\0';
		free(map->map[i]);
		map->map[i] = tmp;
		if (!check_line(map->map[i]))
			return (false);
		i++;
	}
	return (true);
}

_Bool	validate_color(t_map *map)
{
	if (!(map->ceilling & 0xFF) || !(map->floor & 0xFF))
		return (false);
	return (true);
}

_Bool	validate_floodfill(t_map *map)
{
	int32_t	x;
	int32_t	y;

	x = map->player[0];
	y = map->player[1];
	if (x < 0 || y < 0 || x > map->width || y > map->height)
		return (false);
	if (!floodfill(map, x, y))
		return (false);
	return (true);
}
