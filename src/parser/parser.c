/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:24:54 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/12 12:38:04 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

void	clear_map(t_map *map)
{
	if (!map)
		return ;
	if (map->north)
		free(map->north);
	if (map->south)
		free(map->south);
	if (map->west)
		free(map->west);
	if (map->east)
		free(map->east);
	if (map->map)
		ft_split_clear(map->map);
	free(map);
}

void	panic(t_map *map, char *message, uint8_t error)
{
	get_next_line(-1);
	clear_map(map);
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	free(message);
	exit(error);
}

t_map	*parser_map(char *path)
{
	t_map	*map;

	validate_file(path);
	map = (t_map *) ft_calloc(1, sizeof(t_map));
	if (!map)
		panic(map, ft_strdup("Failed to allocate memory"), 1);
	*map = (t_map){0};
	get_map(path, map);
	if (!map->map)
		panic(map, ft_strdup("No map"), 1);
	if (map->height > 100 || map->width > 100)
		panic(map, ft_strdup("Map to big"), 1);
	validate_map(map);
	validate_floodfill(map);
	return (map);
}
