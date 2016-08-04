/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 02:22:08 by vklaouse          #+#    #+#             */
/*   Updated: 2016/06/25 11:50:57 by vklaouse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	check_number(char *str)
{
	int	tmp;

	tmp = ft_atoi(str);
	if ((ft_strcmp(str, ft_itoa(tmp))))
		ft_error("Bad formatage");
	return (tmp);
}

int			map_size(t_env *e, char *av)
{
	int		fd;
	char	*line;
	char	**size;

	fd = open(av, O_RDONLY);
	if (get_next_line(fd, &line) != 1)
		ft_error("Wrong usage");
	size = ft_strsplit(line, ' ');
	if (count_tabsize(size) != 2)
		ft_error("Bad formatage");
	e->map->mapwidth = check_number(size[0]);
	e->map->mapheight = check_number(size[1]);
	ft_strdel(&line);
	return (fd);
}

static void	write_map(t_env *e, int i, char **tab_line)
{
	int	cnt;

	cnt = 0;
	while (cnt < e->map->mapwidth)
	{
		e->map->map[i][cnt] = check_number(tab_line[cnt]);
		cnt++;
	}
}

void		aff_map(int **tab, int collum, int line)
{
	int	i;
	int	j;

	i = 0;
	while (i < line)
	{
		j = 0;
		while (j < collum)
		{
			ft_putnbr(tab[i][j]);
			ft_putstr("  ");
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void		map(t_env *e, char *av)
{
	int		fd;
	char	*line;
	int		i;
	char	**tab_line;

	i = 0;
	fd = map_size(e, av);
	e->map->map = (int **)malloc(sizeof(int *) * e->map->mapheight);
	while (get_next_line(fd, &line) == 1)
	{
		e->map->map[i] = (int *)malloc(sizeof(int) * e->map->mapwidth);
		tab_line = ft_strsplit(line, ' ');
		if (count_tabsize(tab_line) != e->map->mapwidth)
			ft_error("Bad formatage");
		write_map(e, i, tab_line);
		ft_strdel(&line);
		free(tab_line);
		i++;
		if (i > e->map->mapheight)
			ft_error("Bad formatage");
	}
	close(fd);
	map_contents(e);
	aff_map(e->map->map, e->map->mapwidth, e->map->mapheight);
}
