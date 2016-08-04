/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 18:12:43 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 08:08:44 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	map_start(t_env *e)
{
	if (e->map->map[1][1] != 0 || e->map->map[2][1] != 0 ||
		e->map->map[1][2] != 0)
		ft_error("Bad formatage for the start position");
}

void		map_contents(t_env *e)
{
	int	i;
	int	j;

	i = -1;
	while (e->map->mapheight > ++i)
	{
		j = -1;
		while (e->map->mapwidth > ++j)
		{
			if (i == 0)
			{
				if (e->map->map[i][j] != 1)
					ft_error("Bad formatage");
			}
			else if (i == e->map->mapheight - 1)
			{
				if (e->map->map[i][j] != 1)
					ft_error("Bad formatage");
			}
			else if (j == 0 || j == e->map->mapwidth - 1)
				if (e->map->map[i][j] != 1)
					ft_error("Bad formatage");
		}
	}
	map_start(e);
}
