/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 10:05:03 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 14:31:10 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	mpush(t_env *e)
{
	if (e->map->map[(int)(e->ray->pos_x + e->ray->dir_y *
		SPEED)][(int)(e->ray->pos_y)] <= 0 &&
		e->map->map[(int)(e->ray->pos_x + e->ray->dir_y *
		SPEED)][(int)(e->ray->pos_y)] >= -3)
		e->ray->pos_x += e->ray->dir_y * SPEED;
	if (e->map->map[(int)(e->ray->pos_x)]
		[(int)(e->ray->pos_y + e->ray->dir_x * SPEED)] <= 0 &&
		e->map->map[(int)(e->ray->pos_x)]
		[(int)(e->ray->pos_y + e->ray->dir_x * SPEED)] >= -3)
		e->ray->pos_y += e->ray->dir_x * SPEED;
	if (e->map->map[(int)e->ray->pos_x][(int)e->ray->pos_y] == -1
		|| e->map->map[(int)e->ray->pos_x][(int)e->ray->pos_y] == -2)
		teleport(e);
}

void	mleft(t_env *e)
{
	double tmp_x;
	double tmp_y;

	tmp_x = e->ray->pos_x;
	tmp_y = e->ray->pos_y;
	if (e->map->map[(int)(e->ray->pos_x)]
		[(int)(e->ray->pos_y + e->ray->dir_y * SPEED)] <= 0
		&& e->map->map[(int)(e->ray->pos_x + e->ray->dir_x * SPEED)]
		[(int)(e->ray->pos_y)] <= 0 && e->map->map[(int)(e->ray->pos_x)]
		[(int)(e->ray->pos_y + e->ray->dir_y * SPEED)] >= -3
		&& e->map->map[(int)(e->ray->pos_x + e->ray->dir_x * SPEED)]
		[(int)(e->ray->pos_y)] >= -3)
	{
		e->ray->pos_y -= e->ray->dir_y * SPEED;
		e->ray->pos_x += e->ray->dir_x * SPEED;
	}
	if (e->map->map[(int)(e->ray->pos_x)][(int)(e->ray->pos_y)] > 0)
	{
		e->ray->pos_x = tmp_x;
		e->ray->pos_y = tmp_y;
	}
	if (e->map->map[(int)e->ray->pos_x][(int)e->ray->pos_y] == -1 ||
		e->map->map[(int)e->ray->pos_x][(int)e->ray->pos_y] == -2)
		teleport(e);
}

void	mback(t_env *e)
{
	if (e->map->map[(int)(e->ray->pos_x - e->ray->dir_y * SPEED)]
		[(int)(e->ray->pos_y)] <= 0 &&
		e->map->map[(int)(e->ray->pos_x - e->ray->dir_y * SPEED)]
		[(int)(e->ray->pos_y)] >= -3)
		e->ray->pos_x -= e->ray->dir_y * SPEED;
	if (e->map->map[(int)(e->ray->pos_x)]
		[(int)(e->ray->pos_y - e->ray->dir_x * SPEED)] <= 0 &&
		e->map->map[(int)(e->ray->pos_x)]
		[(int)(e->ray->pos_y - e->ray->dir_x * SPEED)] >= -3)
		e->ray->pos_y -= e->ray->dir_x * SPEED;
	if (e->map->map[(int)e->ray->pos_x][(int)e->ray->pos_y] == -1 ||
		e->map->map[(int)e->ray->pos_x][(int)e->ray->pos_y] == -2)
		teleport(e);
}

void	mright(t_env *e)
{
	double tmp_x;
	double tmp_y;

	tmp_x = e->ray->pos_x;
	tmp_y = e->ray->pos_y;
	if (e->map->map[(int)(e->ray->pos_x)]
		[(int)(e->ray->pos_y - e->ray->dir_y * SPEED)] <= 0
		&& e->map->map[(int)(e->ray->pos_x - e->ray->dir_x * SPEED)]
		[(int)(e->ray->pos_y)] <= 0 && e->map->map[(int)(e->ray->pos_x)]
		[(int)(e->ray->pos_y - e->ray->dir_y * SPEED)] >= -3
		&& e->map->map[(int)(e->ray->pos_x - e->ray->dir_x * SPEED)]
		[(int)(e->ray->pos_y)] >= -3)
	{
		e->ray->pos_y += e->ray->dir_y * SPEED;
		e->ray->pos_x -= e->ray->dir_x * SPEED;
	}
	if (e->map->map[(int)(e->ray->pos_x)][(int)(e->ray->pos_y)] > 0)
	{
		e->ray->pos_x = tmp_x;
		e->ray->pos_y = tmp_y;
	}
	if (e->map->map[(int)e->ray->pos_x][(int)e->ray->pos_y] == -1 ||
		e->map->map[(int)e->ray->pos_x][(int)e->ray->pos_y] == -2)
		teleport(e);
}

int		winner(t_env *e)
{
	if (e->map->map[(int)e->ray->raypos_y][(int)e->ray->raypos_x] == -3)
	{
		e->winner = 1;
		mlx_clear_window(e->mlx, e->win);
		mlx_string_put(e->mlx, e->win, 600, 500, 0xFFFFFF, "YOU WIN !");
		return (1);
	}
	return (0);
}
