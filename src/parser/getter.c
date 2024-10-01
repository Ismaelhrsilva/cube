/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:56:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/01 11:06:58 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include "parser.h"
#include <stdbool.h>
#include <stdint.h>

static uint32_t	get_hexcolor(char *line)
{
	char		**colors;
	uint32_t	color;
	uint32_t	tmp;
	uint32_t	i;

	colors = ft_split(line, ',');
	if (!colors)
		exit(1);
	i = 0;
	color = 0;
	while (check(colors[i], ft_isdigit) && ft_strlen(colors[i]) < 4)
	{
		tmp = ft_atoi(colors[i]);
		if (tmp > 255)
			break ;
		color += tmp;
		color = color << 8;
		i++;
	}
	ft_split_clear(colors);
	if (i != 3)
		return (0);
	return (color += 0xFF);
}

static void	get_texture(char *line, t_map *map)
{
	char	*tmp;

	tmp = ft_strtrim(line, " \t\n");
	if (!tmp)
		return (exit(1));
	if (!map->north && !ft_strncmp(tmp, "NO ", 3))
		map->north = ft_strtrim(&tmp[3], " \t");
	else if (!map->south && !ft_strncmp(tmp, "SO ", 3))
		map->south = ft_strtrim(&tmp[3], " \t");
	else if (!map->west && !ft_strncmp(tmp, "WE ", 3))
		map->west = ft_strtrim(&tmp[3], " \t");
	else if (!map->east && !ft_strncmp(tmp, "EA ", 3))
		map->east = ft_strtrim(&tmp[3], " \t");
	else if (!map->ceilling && !ft_strncmp(tmp, "C ", 2))
		map->ceilling = get_hexcolor(&tmp[2]);
	else if (!map->floor && !ft_strncmp(tmp, "F ", 2))
		map->floor = get_hexcolor(&tmp[2]);
	else if (ft_strlen(tmp))
	{
		free(tmp);
		free(line);
		panic(map, NULL, "Extra information", 1);
	}
	free(tmp);
}

static void	get_player(t_map *map)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (ft_strchr("NSWE", map->map[y][x]))
			{
				map->player[0] = x;
				map->player[1] = y;
				map->player[2] = map->map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	get_field(char *line, t_map *map)
{
	static int32_t	size;
	int32_t			width;
	char			**tmp;

	if (!(map->height % MEMORY_SIZE))
	{
		size += MEMORY_SIZE;
		tmp = (char **) ft_calloc(sizeof(char *), size + 1);
		if (!tmp)
			exit(1);
		if (map->map)
			ft_memmove(tmp, map->map, sizeof(char **) * (size - MEMORY_SIZE));
		free(map->map);
		map->map = tmp;
	}
	map->map[map->height++] = ft_strdup(line);
	width = ft_strlen(line);
	if (width > map->width)
		map->width = width;
}

void	get_map(char *path, t_map *map)
{
	int32_t	fd;
	char		*line;

	fd = open(path, O_RDONLY, 0644);
	if (fd < 0)
		return (exit(1));
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!map->north
			|| !map->south
			|| !map->west
			|| !map->east
			|| !map->ceilling
			|| !map->floor)
			get_texture(line, map);
		else
			get_field(line, map);
		free(line);
	}
	if (map->map)
		get_player(map);
}
