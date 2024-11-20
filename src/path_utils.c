/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:45:00 by emiro-co          #+#    #+#             */
/*   Updated: 2024/11/20 17:43:50 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	manage_line(t_map *map, char *line)
{
	char	**splitted;

	if (found_all(map))
		push_line(map, line);
	else if (ft_strcmp(line, "") != 0)
	{
		splitted = ft_split(line, ' ');
		ft_check_element(line, splitted);
		if (is_element(splitted[0]))
			assign(map, splitted[1], is_element(splitted[0]));
		free_matrix(splitted, 2);
	}
}
