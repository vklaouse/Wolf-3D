/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 13:34:02 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 14:30:30 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include "libft/include/libft.h"

# define HEIGHT 1024
# define WIDTH 1280
# define SPEED 0.15
# define RSPEED 0.07

/*
** Keycodes
*/

# define K_EXIT 53
# define MLEFT 0
# define MRIGHT 2
# define MPUSH 13
# define MBACK 1
# define TLEFT 123
# define TRIGHT 124
# define TUP 125
# define TDOWN 126
# define DESTROY 49
# define CONSTRUCT 36

typedef struct	s_map
{
	int			mapwidth;
	int			mapheight;
	int			**map;
}				t_map;

typedef struct	s_dda
{
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}				t_dda;

typedef struct	s_calc
{
	double		walldist;
	int			height;
	int			start;
	int			end;
	double		up_down;
}				t_calc;

typedef struct	s_ray
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
	double		old_dir;
	double		old_plan;
	double		camera_x;
	double		raypos_x;
	double		raypos_y;
	double		raydir_x;
	double		raydir_y;
}				t_ray;

typedef struct	s_img
{
	void		*adr;
	char		*data;
	int			endian;
	int			bpp;
	int			size_line;
}				t_img;

typedef struct	s_player
{
	int			mleft;
	int			mright;
	int			mback;
	int			mpush;
	int			tleft;
	int			tright;
	int			tup;
	int			tdown;
	int			destroy;
	int			construct;
}				t_player;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	int			color;
	int			bloc;
	int			winner;
	t_map		*map;
	t_ray		*ray;
	t_dda		*dda;
	t_calc		*calc;
	t_img		*img;
	t_player	*player;
}				t_env;

/*
** main.c
*/

int				main(int ac, char **av);
void			aff(t_env *e);

/*
** check_error.c
*/

void			ft_error(char *str);
int				count_tabsize(char **tab);
void			protect_border(t_env *e);

/*
** read_map.c
*/

void			map(t_env *e, char *av);
int				map_size(t_env *e, char *av);

/*
** parse_map.c
*/

void			map_contents(t_env *e);

/*
** start_mlx.c
*/

void			start_mlx(t_env *e);

/*
** raycasting.c
*/

int				raycasting(t_env *e);

/*
** draw.c
*/

void			wall_color(t_env *e);
void			ft_pixel_put_image(t_env *e, int x, int y, int color);
void			draw(int x, t_env *e);

/*
** key_hook.c
*/

int				key_release(int keycode, t_env *e);
int				key_press(int keycode, t_env *e);
void			motion_turn(t_env *e);
void			motion(t_env *e);

/*
** bonus.c
*/

void			teleport(t_env *e);
void			destroy(t_env *e);
void			construct(t_env *e);

/*
** move.c
*/

void			mpush(t_env *e);
void			mleft(t_env *e);
void			mback(t_env *e);
void			mright(t_env *e);
int				winner(t_env *e);

#endif
