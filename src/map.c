/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:22:18 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/09 20:02:33 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

t_data *init_argumet(void)	// init the data structure
{
	t_data *dt = calloc(1, sizeof(t_data)); // init the data structure
	dt->map2d = calloc(10, sizeof(char *)); // init the map
	dt->map2d[0] = strdup("1111111111111111111111111"); //fill the map
	dt->map2d[1] = strdup("1P00000000000000000100001");
	dt->map2d[2] = strdup("1000000000000000000000001");
	dt->map2d[3] = strdup("1111000000000000001000001");
	dt->map2d[4] = strdup("1001000000000000001000001");
	dt->map2d[5] = strdup("1000000000100000001000001");
	dt->map2d[6] = strdup("1001000000000000001000001");
	dt->map2d[7] = strdup("1001000000001000001000001");
	dt->map2d[8] = strdup("1111111111111111111111111");
	dt->map2d[9] = NULL;
	dt->p_y = 2; // player y position in the map
	dt->p_x = 2; // player x position in the map
	dt->w_map = 25; // map width
	dt->h_map = 9; // map height
	dt->minimap_turn = 0;
	dt->wall_text = construct_texture(NULL, WALL_TEXT); //GET TEXTURE WALL
	return (dt); // return the data structure
}
