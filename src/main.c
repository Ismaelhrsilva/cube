/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:51:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/02 19:29:25 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

t_data	*init_map(t_map	*map)
{
	t_data	*data;

	data = (t_data *) ft_calloc(sizeof(t_data), 1);
	if (!data)
		exit(EXIT_FAILURE);
	data->map = map->map;
	data->p_x = map->player[0];
	data->p_y = map->player[1];
	data->width = map->width;
	data->height = map->height;
	data->floor = map->floor;
	data->ceilling = map->ceilling;
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
	data = init_map(map);
	data->parser = map;
	start(data);
	clear_map(map);
	return (EXIT_SUCCESS);
}
