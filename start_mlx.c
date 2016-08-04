/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 03:15:33 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 11:47:27 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	start_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "Wolf3d");
	e->img->adr = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->img->endian = 1;
	if (!(e->img->data = malloc(sizeof(char *))))
		ft_error("Allocation Error : Insufficient memory");
	e->img->data = mlx_get_data_addr(e->img->adr, &e->img->bpp,
									&e->img->size_line, &e->img->endian);
	mlx_loop_hook(e->mlx, &raycasting, e);
	mlx_hook(e->win, 2, (1L << 0), &key_press, e);
	mlx_hook(e->win, 3, (1L << 1), &key_release, e);
	mlx_loop(e->mlx);
}
