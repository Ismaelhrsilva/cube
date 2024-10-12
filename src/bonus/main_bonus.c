/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:51:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/10/12 13:07:53 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"
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

	if (argc < 2)
		gameover(NULL, ft_strdup("No map informed"), 1);
	if (argc > 2)
		gameover(NULL, ft_strdup("Too many arguments"), 1);
	map = parser_map(argv[1]);
	if (!map)
		gameover(NULL, ft_strdup("Failed to parser map"), 1);
	data = init_map(map);
	data->parser = map;
	start(data);
	return (EXIT_SUCCESS);
}
