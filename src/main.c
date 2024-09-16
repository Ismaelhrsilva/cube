/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:51:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/16 12:07:41 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "parser.h"
#include <stdlib.h>

int	 main(int argc, char **argv)
{
	t_data	*data;
	t_map	*map;
	//t_mlx	*mlx;

	if (argc != 2)
		return (EXIT_FAILURE);
	map = parser_map(argv[1]);
	print(map);
	clear_map(map);
	data = init_argumet();	// init the data structure
	start_the_game(data);	// start the game
	return (EXIT_SUCCESS);
}
