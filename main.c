/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/20 23:04:50 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 14:30:12 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_env	*ft_init(void)
{
	t_env	*e;

	if (!(e = malloc(sizeof(*e))))
		ft_error("Allocation Error : Insufficient memory");
	if (!(e->map = malloc(sizeof(t_map))))
		ft_error("Allocation Error : Insufficient memory");
	if (!(e->ray = malloc(sizeof(t_ray))))
		ft_error("Allocation Error : Insufficient memory");
	if (!(e->dda = malloc(sizeof(t_dda))))
		ft_error("Allocation Error : Insufficient memory");
	if (!(e->calc = malloc(sizeof(t_calc))))
		ft_error("Allocation Error : Insufficient memory");
	if (!(e->img = malloc(sizeof(t_img))))
		ft_error("Allocation Error : Insufficient memory");
	if (!(e->player = malloc(sizeof(t_player))))
		ft_error("Allocation Error : Insufficient memory");
	return (e);
}

void			aff(t_env *e)
{
	char *str;

	mlx_put_image_to_window(e->mlx, e->win, e->img->adr, 0, 0);
	mlx_string_put(e->mlx, e->win, 1140, 20, 0x000000, "Bloc(s) :");
	str = ft_itoa(e->bloc);
	mlx_string_put(e->mlx, e->win, 1240, 20, 0x000000, str);
	ft_strdel(&str);
}

void			init_raycast(t_env *e)
{
	e->ray->pos_x = 2;
	e->ray->pos_y = 2;
	e->ray->dir_x = -1;
	e->ray->dir_y = 0;
	e->ray->plan_x = 0;
	e->ray->plan_y = 0.66;
	e->player->mleft = 0;
	e->player->mright = 0;
	e->player->mpush = 0;
	e->player->mback = 0;
	e->player->tleft = 0;
	e->player->tright = 0;
	e->calc->up_down = 2;
	e->player->tup = 0;
	e->player->tdown = 0;
	e->player->destroy = 0;
	e->player->construct = 0;
	e->bloc = 0;
	e->winner = 0;
}

int				main(int ac, char **av)
{
	t_env *e;

	if (ac != 2)
		ft_error("Wrong usage");
	e = ft_init();
	map(e, av[1]);
	init_raycast(e);
	start_mlx(e);
	return (0);
}
