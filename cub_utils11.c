/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 04:54:16 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/21 05:40:54 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_checkandputsquare(char **map, int i, int j)
{
	if (map[i][j] == '1')
	{
		ft_putstr_fd("\e[41m ", 1);
		ft_putstr_fd("\e[41m ", 1);
	}
	else if (map[i][j] == '2')
	{
		ft_putstr_fd("\e[45m ", 1);
		ft_putstr_fd("\e[45m ", 1);
	}
	else if (map[i][j] == '3')
	{
		ft_putstr_fd("\e[102m ", 1);
		ft_putstr_fd("\e[102m ", 1);
	}
	else if (map[i][j] == '0')
	{
		ft_putstr_fd("\e[107m ", 1);
		ft_putstr_fd("\e[107m ", 1);
	}
	else
	{
		ft_putstr_fd("\e[46m ", 1);
		ft_putstr_fd("\e[46m ", 1);
	}
}

void
	ft_debugmap(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i][j])
	{
		while (map[i][j])
		{
			ft_checkandputsquare(map, i, j);
			j++;
		}
		j = 0;
		ft_putstr_fd("\e[49m \n", 1);
		i++;
	}
}

void
	ft_show_enemypos(t_mlx_data *data, int resph)
{
	int			i;
	t_square	square;

	i = 0;
	while (i < data->spritenumber)
	{
		if (data->sprite[i].texture == 0)
		{
			square = ft_set_square(5, 5, 8 + data->sprite[i].y * resph, 8
			+ data->sprite[i].x * resph);
			ft_mlx_drawfilled_square(&square, rgb_int(255, 0, 0), data);
		}
		i++;
	}
}

void
	ft_putsquare(int i, int j, t_mlx_data *data)
{
	data->square = ft_set_square(data->resph, data->resph, 10
	+ j * data->resph, 10 + i * data->resph);
	ft_mlx_drawfilled_square(&data->square, rgb_int(0, 204, 153), data);
}

void
	ft_showposes(t_mlx_data *data)
{
	ft_show_enemypos(data, data->resph);
	data->square = ft_set_square(5, 5, 8 + data->posy * data->resph, 8
	+ data->posx * data->resph);
	ft_mlx_drawfilled_square(&data->square, rgb_int(255, 127, 80), data);
	data->square = ft_set_square(3, 3, 9 + data->posy * data->resph
	+ 2 * data->diry, 9 + data->posx * data->resph + 2 * data->dirx);
	ft_mlx_drawfilled_square(&data->square, rgb_int(0, 0, 0), data);
}
