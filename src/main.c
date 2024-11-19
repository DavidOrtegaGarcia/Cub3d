/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:48:27 by emiro-co          #+#    #+#             */
/*   Updated: 2024/11/19 21:59:09 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	ft_memset(&map, 0, sizeof(t_map));
	ft_check_input(&map, argc, argv[1]);
	map.content = malloc(sizeof(char *) * map.check.map_lines);
	ft_get_doc(&map, argv[1], ft_get_rows(&map, map.check.path));
	ft_parse(&map);
	init_game(map);
	free_all_doc(&map.check.all_doc);
}
