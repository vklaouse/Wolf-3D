/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 06:16:21 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 14:06:22 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_var(t_env *e, int x)
{
	e->ray->camera_x = 2 * x / (double)WIDTH - 1;
	e->ray->raypos_x = e->ray->pos_y;
	e->ray->raypos_y = e->ray->pos_x;
	e->ray->raydir_x = e->ray->dir_x + e->ray->plan_x * e->ray->camera_x;
	e->ray->raydir_y = e->ray->dir_y + e->ray->plan_y * e->ray->camera_x;
	e->dda->map_x = (int)e->ray->raypos_x;
	e->dda->map_y = (int)e->ray->raypos_y;
	e->dda->deltadist_x = sqrt(1 + (e->ray->raydir_y * e->ray->raydir_y)
							/ (e->ray->raydir_x * e->ray->raydir_x));
	e->dda->deltadist_y = sqrt(1 + (e->ray->raydir_x * e->ray->raydir_x)
							/ (e->ray->raydir_y * e->ray->raydir_y));
	e->dda->hit = 0;
}

static void	init_dir(t_env *e)
{
	if (e->ray->raydir_x < 0)
	{
		e->dda->step_x = -1;
		e->dda->sidedist_x = (e->ray->raypos_x - (double)e->dda->map_x) *
			e->dda->deltadist_x;
	}
	else
	{
		e->dda->step_x = 1;
		e->dda->sidedist_x = ((double)e->dda->map_x + 1.0 - e->ray->raypos_x) *
			e->dda->deltadist_x;
	}
	if (e->ray->raydir_y < 0)
	{
		e->dda->step_y = -1;
		e->dda->sidedist_y = (e->ray->raypos_y - (double)e->dda->map_y) *
			e->dda->deltadist_y;
	}
	else
	{
		e->dda->step_y = 1;
		e->dda->sidedist_y = ((double)e->dda->map_y + 1.0 - e->ray->raypos_y) *
			e->dda->deltadist_y;
	}
}

static void	dda_algo(t_env *e)
{
	init_dir(e);
	while (e->dda->hit == 0)
	{
		if (e->dda->sidedist_x < e->dda->sidedist_y)
		{
			e->dda->sidedist_x += e->dda->deltadist_x;
			e->dda->map_x += e->dda->step_x;
			e->dda->side = 0;
		}
		else
		{
			e->dda->sidedist_y += e->dda->deltadist_y;
			e->dda->map_y += e->dda->step_y;
			e->dda->side = 1;
		}
		if (e->map->map[e->dda->map_y][e->dda->map_x] > 0 ||
			e->map->map[e->dda->map_y][e->dda->map_x] == -1 ||
			e->map->map[e->dda->map_y][e->dda->map_x] == -2)
			e->dda->hit = 1;
	}
}

static void	distance_calc(t_env *e)
{
	if (e->dda->side == 0)
		e->calc->walldist = fabs((e->dda->map_x - e->ray->raypos_x +
								(1 - e->dda->step_x) / 2) / e->ray->raydir_x);
	else
		e->calc->walldist = fabs((e->dda->map_y - e->ray->raypos_y +
								(1 - e->dda->step_y) / 2) / e->ray->raydir_y);
	e->calc->height = abs((int)((HEIGHT) / e->calc->walldist));
	e->calc->start = ((-1 * (e->calc->height)) / 2 + HEIGHT / e->calc->up_down);
	if (e->calc->start < 0)
		e->calc->start = 0;
	e->calc->end = (e->calc->height / 2 + HEIGHT / e->calc->up_down);
	if (e->calc->end >= HEIGHT)
		e->calc->end = HEIGHT - 1;
}

int			raycasting(t_env *e)
{
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_var(e, x);
		dda_algo(e);
		distance_calc(e);
		draw(x, e);
		x++;
	}
	motion(e);
	if (winner(e))
		return (0);
	if (e->bloc <= 99)
		aff(e);
	else
	{
		mlx_clear_window(e->mlx, e->win);
		mlx_string_put(e->mlx, e->win, 600, 500, 0xFFFFFF, "You lose ! D:");
	}
	return (0);
}
