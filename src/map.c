/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:22:18 by ishenriq          #+#    #+#             */
/*   Updated: 2024/09/15 17:37:23 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "MLX42.h"

t_data *init_argumet(void)	// init the data structure
{
	t_data *dt = ft_calloc(1, sizeof(t_data)); // init the data structure
	dt->map2d = ft_calloc(10, sizeof(char *)); // init the map
	dt->map2d[0] = ft_strdup("11111111111111111111111111111111"); //fill the map
	dt->map2d[1] = ft_strdup("1P000000000000000001000000000101");
	dt->map2d[2] = ft_strdup("10000000000000000000000011111111");
	dt->map2d[3] = ft_strdup("1111000000000000001000001");
	dt->map2d[4] = ft_strdup("1001000000000000001000001");
	dt->map2d[5] = ft_strdup("1000000000100000001000001");
	dt->map2d[6] = ft_strdup("1001000000000000001000001");
	dt->map2d[7] = ft_strdup("1001000000001000001000001");
	dt->map2d[8] = ft_strdup("1111111111111111111111111");
	dt->map2d[9] = NULL;
	dt->p_y = 2; // player y position in the map
	dt->p_x = 2; // player x position in the map
	dt->w_map = 25; // map width
	dt->h_map = 9; // map height
	dt->minimap_turn = 0;
	dt->wall_text = construct_texture(NULL, WALL_TEXT); //GET TEXTURE WALL
	return (dt); // return the data structure
}
