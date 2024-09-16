/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:24:54 by rde-mour          #+#    #+#             */
/*   Updated: 2024/09/16 12:07:14 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <stdio.h>

// TEMPORARY FUNCTION
void	print(t_map *map)
{
	uint32_t	i;

	printf("PLAYER   : %c %i %i\n", map->map[map->player[1]][map->player[0]], map->player[0], map->player[1]);
	printf("NORTH(NO): %s\n", map->north);
	printf("SOUTH(SO): %s\n", map->south);
	printf("WEST (WE): %s\n", map->west);
	printf("EAST (EA): %s\n", map->east);
	printf("CEILLING : %x\n", map->sky);
	printf("FLOOR    : %x\n", map->floor);
	printf("WIDTH    : %i\n", map->width);
	printf("HEIGHT   : %i\n", map->height);
	printf("START MAP >>>\n");
	i = 0;
	while (map->map && map->map[i])
		printf("%s\n", map->map[i++]);
	printf("<<< END MAP\n");
}
// TEMPORARY FUNCTION

void	panic(t_map *map, char *str, char *message, unsigned int error)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	clear_map(map);
	get_next_line(-1);
	exit(error);
}

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

t_map	*parser_map(char *path)
{
	t_map	*map;

	if (!validate_file(path))
		return (NULL);
	map = (t_map *) malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	*map = (t_map){0};
	get_map(path, map);
	if (!map->map)
		return (clear_map(map), NULL);
	if (!validate_map(map))
		panic(map, path, " is a bad formated map\n", 1);
	if (!validate_floodfill(map))
		panic(map, path, " is not a valid map\n", 1);
	return (map);
}
