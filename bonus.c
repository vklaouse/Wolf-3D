/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 09:39:40 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 20:42:08 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		destroy(t_env *e)
{
	if (e->map->map[(int)(e->ray->pos_x + e->ray->dir_y * SPEED)]
		[(int)(e->ray->pos_y)] > 1)
	{
		e->bloc++;
		e->map->map[(int)(e->ray->pos_x + e->ray->dir_y * SPEED)]
			[(int)(e->ray->pos_y)] = 0;
	}
	else if (e->map->map[(int)(e->ray->pos_x)]
			[(int)(e->ray->pos_y + e->ray->dir_x * SPEED)] > 1)
	{
		e->bloc++;
		e->map->map[(int)(e->ray->pos_x)]
			[(int)(e->ray->pos_y + e->ray->dir_x * SPEED)] = 0;
	}
}

void		construct_2(t_env *e)
{
	if (e->dda->step_x == -1 && e->dda->step_y == -1 &&
			!e->map->map[(int)(e->ray->pos_x + e->ray->dir_y * SPEED) - 1]
			[(int)(e->ray->pos_y)])
	{
		e->bloc--;
		e->map->map[(int)(e->ray->pos_x - e->ray->dir_y * SPEED) - 1]
			[(int)(e->ray->pos_y)] = 100;
		protect_border(e);
	}
	else if (e->dda->step_x == -1 && e->dda->step_y == 1 &&
			!e->map->map[(int)(e->ray->pos_x + e->ray->dir_y * SPEED)]
			[(int)(e->ray->pos_y) - 1])
	{
		e->bloc--;
		e->map->map[(int)(e->ray->pos_x - e->ray->dir_y * SPEED)]
			[(int)(e->ray->pos_y) - 1] = 100;
		protect_border(e);
	}
}

void		construct(t_env *e)
{
	if (e->dda->step_x == 1 && e->dda->step_y == 1 &&
		!e->map->map[(int)(e->ray->pos_x + e->ray->dir_y * SPEED) + 1]
		[(int)(e->ray->pos_y)])
	{
		e->bloc--;
		e->map->map[(int)(e->ray->pos_x + e->ray->dir_y * SPEED) + 1]
			[(int)(e->ray->pos_y)] = 100;
		protect_border(e);
	}
	else if (e->dda->step_x == 1 && e->dda->step_y == -1 &&
			!e->map->map[(int)(e->ray->pos_x + e->ray->dir_y * SPEED)]
			[(int)(e->ray->pos_y) + 1])
	{
		e->bloc--;
		e->map->map[(int)(e->ray->pos_x - e->ray->dir_y * SPEED)]
			[(int)(e->ray->pos_y) + 1] = 100;
		protect_border(e);
	}
	construct_2(e);
}

static void	teleport_2(t_env *e, int x)
{
	int	y;

	while (++x < e->map->mapheight)
	{
		y = -1;
		while (++y < e->map->mapwidth)
		{
			if (e->map->map[x][y] == -1)
			{
				if (!e->map->map[x - 1][y] && !e->map->map[x + 1][y] &&
					!e->map->map[x][y + 1] && !e->map->map[x][y - 1])
				{
					e->ray->pos_x = x;
					e->ray->pos_y = y;
				}
				y = 0;
				break ;
			}
		}
		if (y == 0)
			break ;
	}
}

void		teleport(t_env *e)
{
	int x;
	int y;

	x = -1;
	if (e->map->map[(int)e->ray->pos_x][(int)e->ray->pos_y] == -1)
		while (++x < e->map->mapheight && y != -10)
		{
			y = -1;
			while (++y < e->map->mapwidth && y != -10)
			{
				if (e->map->map[x][y] == -2)
				{
					if (!e->map->map[x - 1][y] && !e->map->map[x + 1][y] &&
						!e->map->map[x][y + 1] && !e->map->map[x][y - 1])
					{
						e->ray->pos_x = x;
						e->ray->pos_y = y;
						y = -11;
					}
				}
			}
		}
	else if (e->map->map[(int)e->ray->pos_x][(int)e->ray->pos_y] == -2)
		teleport_2(e, x);
}
