/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 05:44:33 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 14:31:42 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int			key_press(int keycode, t_env *e)
{
	if (keycode == K_EXIT)
		exit(0);
	else if (keycode == MLEFT && e->winner == 0)
		e->player->mleft = 1;
	else if (keycode == MRIGHT && e->winner == 0)
		e->player->mright = 1;
	else if (keycode == MPUSH && e->winner == 0)
		e->player->mpush = 1;
	else if (keycode == MBACK && e->winner == 0)
		e->player->mback = 1;
	else if (keycode == TLEFT)
		e->player->tleft = 1;
	else if (keycode == TRIGHT)
		e->player->tright = 1;
	else if (keycode == TUP)
		e->player->tup = 1;
	else if (keycode == TDOWN)
		e->player->tdown = 1;
	else if (keycode == DESTROY)
		e->player->destroy = 1;
	else if (keycode == CONSTRUCT && e->bloc <= 99)
		e->player->construct = 1;
	return (0);
}

int			key_release(int keycode, t_env *e)
{
	if (keycode == MLEFT)
		e->player->mleft = 0;
	else if (keycode == MRIGHT)
		e->player->mright = 0;
	else if (keycode == MPUSH)
		e->player->mpush = 0;
	else if (keycode == MBACK)
		e->player->mback = 0;
	else if (keycode == TLEFT)
		e->player->tleft = 0;
	else if (keycode == TRIGHT)
		e->player->tright = 0;
	else if (keycode == TUP)
		e->player->tup = 0;
	else if (keycode == TDOWN)
		e->player->tdown = 0;
	else if (keycode == DESTROY)
		e->player->destroy = 0;
	else if (keycode == CONSTRUCT)
		e->player->construct = 0;
	return (0);
}

static void	motion_updown(t_env *e)
{
	if (e->player->tleft == 1)
	{
		e->ray->old_dir = e->ray->dir_x;
		e->ray->dir_x = e->ray->dir_x * cos(RSPEED) - e->ray->dir_y
			* sin(RSPEED);
		e->ray->dir_y = e->ray->old_dir * sin(RSPEED) + e->ray->dir_y
			* cos(RSPEED);
		e->ray->old_plan = e->ray->plan_x;
		e->ray->plan_x = e->ray->plan_x * cos(RSPEED) - e->ray->plan_y
			* sin(RSPEED);
		e->ray->plan_y = e->ray->old_plan * sin(RSPEED) + e->ray->plan_y
			* cos(RSPEED);
	}
	if (e->player->tup == 1)
		if (e->calc->up_down < 3)
			e->calc->up_down += 0.05;
	if (e->player->tdown == 1)
		if (e->calc->up_down > 1.5)
			e->calc->up_down -= 0.05;
}

void		motion_turn(t_env *e)
{
	if (e->player->tright == 1)
	{
		e->ray->old_dir = e->ray->dir_x;
		e->ray->dir_x = e->ray->dir_x * cos(-RSPEED) - e->ray->dir_y
			* sin(-RSPEED);
		e->ray->dir_y = e->ray->old_dir * sin(-RSPEED) + e->ray->dir_y
			* cos(-RSPEED);
		e->ray->old_plan = e->ray->plan_x;
		e->ray->plan_x = e->ray->plan_x * cos(-RSPEED) - e->ray->plan_y
			* sin(-RSPEED);
		e->ray->plan_y = e->ray->old_plan * sin(-RSPEED) + e->ray->plan_y
			* cos(-RSPEED);
	}
	motion_updown(e);
}

void		motion(t_env *e)
{
	if (e->player->mpush == 1)
		mpush(e);
	if (e->player->destroy == 1)
		destroy(e);
	if (e->player->construct == 1 && e->bloc > 0)
		construct(e);
	if (e->player->mleft == 1)
		mleft(e);
	if (e->player->mback == 1)
		mback(e);
	if (e->player->mright == 1)
		mright(e);
	motion_turn(e);
}
