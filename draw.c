/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 03:32:16 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 14:23:45 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_pixel_put_image(t_env *e, int x, int y, int color)
{
	unsigned int pos;
	unsigned int mem;

	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		pos = (y * e->img->size_line) + ((e->img->bpp / 8) * x);
		mem = mlx_get_color_value(e->mlx, color);
		e->img->data[pos + 0] = (mem & 0xFF);
		e->img->data[pos + 1] = (mem & 0xFF00) >> 8;
		e->img->data[pos + 2] = (mem & 0xFF0000) >> 16;
	}
}

static void	draw_wall(t_env *e, int x, int y)
{
	if (e->map->map[e->dda->map_y][e->dda->map_x] > 0)
	{
		if (e->dda->side == 1)
			ft_pixel_put_image(e, x, y, e->color / 2);
		else
			ft_pixel_put_image(e, x, y, e->color);
	}
	if (e->map->map[e->dda->map_y][e->dda->map_x] == -1)
	{
		if (e->dda->side == 1)
			ft_pixel_put_image(e, x, y, (0xCCFF00 + y * x) / 2);
		else
			ft_pixel_put_image(e, x, y, 0xCCFF00 + y * x);
	}
	if (e->map->map[e->dda->map_y][e->dda->map_x] == -2)
	{
		if (e->dda->side == 1)
			ft_pixel_put_image(e, x, y, (0x330000 + y * x) / 2);
		else
			ft_pixel_put_image(e, x, y, 0x330000 + x * y);
	}
}

void		draw(int x, t_env *e)
{
	int	y;

	y = 0;
	while (y < e->calc->start)
	{
		ft_pixel_put_image(e, x, y, 0x66CCFF);
		y++;
	}
	wall_color(e);
	y = e->calc->start;
	while (y < e->calc->end)
	{
		draw_wall(e, x, y);
		y++;
	}
	y = e->calc->end;
	wall_color(e);
	while (y < HEIGHT)
	{
		ft_pixel_put_image(e, x, y, 0x808080);
		y++;
	}
}

void		wall_color(t_env *e)
{
	if (e->map->map[e->dda->map_y][e->dda->map_x] == 1)
		e->color = 0xCCFFFF;
	else if (e->map->map[e->dda->map_y][e->dda->map_x] == 2)
		e->color = 0xCCCC00;
	else if (e->map->map[e->dda->map_y][e->dda->map_x] == 3)
		e->color = 0x3300FF;
	else if (e->map->map[e->dda->map_y][e->dda->map_x] == 4)
		e->color = 0xFF22EE;
	else if (e->map->map[e->dda->map_y][e->dda->map_x] == 5)
		e->color = 0xFF0033;
	else if (e->map->map[e->dda->map_y][e->dda->map_x] == 6)
		e->color = 0x33CC00;
	else if (e->map->map[e->dda->map_y][e->dda->map_x] == 100)
		e->color = 0x000033;
	else
		e->color = 0xFFFFFF;
}
