/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 00:57:10 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 10:51:46 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(0);
}

int			count_tabsize(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static void	protect(t_env *e, int i, int j)
{
	if (i == 0)
	{
		if (e->map->map[i][j] != 1)
		{
			e->map->map[i][j] = 1;
			e->bloc++;
		}
	}
	else if (i == e->map->mapheight - 1)
	{
		if (e->map->map[i][j] != 1)
		{
			e->bloc++;
			e->map->map[i][j] = 1;
		}
	}
	else if (j == 0 || j == e->map->mapwidth - 1)
		if (e->map->map[i][j] != 1)
		{
			e->bloc++;
			e->map->map[i][j] = 1;
		}
}

void		protect_border(t_env *e)
{
	int i;
	int j;

	i = -1;
	while (e->map->mapheight > ++i)
	{
		j = -1;
		while (e->map->mapwidth > ++j)
		{
			protect(e, i, j);
		}
	}
}
