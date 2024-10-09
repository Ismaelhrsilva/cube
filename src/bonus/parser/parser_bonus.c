/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:24:54 by rde-mour          #+#    #+#             */
/*   Updated: 2024/10/09 19:38:46 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"
#include "libft.h"
#include "parser_bonus.h"
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <stdio.h>
// TEMPORARY FUNCTION
void	print(t_map *map)
{
	uint32_t	i;

	printf("PLAYER  : %c %i %i\n",
		map->player[2], map->player[0], map->player[1]);
	printf("NO NORTH: %s\n", map->north);
	printf("SO SOUTH: %s\n", map->south);
	printf("WE WEST : %s\n", map->west);
	printf("EA EAST : %s\n", map->east);
	printf("CEILLING: %x\n", map->ceilling);
	printf("FLOOR   : %x\n", map->floor);
	printf("WIDTH   : %i\n", map->width);
	printf("HEIGHT  : %i\n", map->height);
	printf("START MAP >>>\n");
	i = 0;
	while (map->map && map->map[i])
		printf("%s\n", map->map[i++]);
	printf("<<< END MAP\n");
}
// TEMPORARY FUNCTION

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
	print(map);
	return (map);
}
