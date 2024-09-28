/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:51:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/28 11:57:36 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "parser.h"
#include <stdbool.h>
#include <stdlib.h>

/*
 * Get the t_map and converts it to t_data
 */
t_data	*init_map(t_map	*map)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data) * 1);
	if (!data)
		exit(EXIT_FAILURE);
	data->map = map->map;
	data->p_x = map->player[0];
	data->p_y = map->player[1];
	data->width = map->width;
	data->height = map->height;
	data->floor = map->floor;
	data->sky = map->sky;
	data->wall_text = construct_texture(NULL, WALL_TEXT);
	data->door_closed = 1;
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_map	*map;

	if (argc != 2)
		return (EXIT_FAILURE);
	map = parser_map(argv[1]);
	if (!map)
		return (EXIT_FAILURE);
	print(map);
	data = init_map(map);
	start_the_game(data, map);
	clear_map(map);
	return (EXIT_SUCCESS);
}
