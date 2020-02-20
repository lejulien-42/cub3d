/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 15:35:23 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/13 14:05:49 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pos
	ft_set_pos(int x, int y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_square
	ft_set_square(int w, int h, int x, int y)
{
	t_square	square;

	square.pos = ft_set_pos(x, y);
	square.w = w;
	square.h = h;
	return (square);
}

void
	ft_mlx_horizline(t_data *data, int color, t_pos *pos, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		mlx_pixel_put(data->mlx_ptr, data->mlx_win, pos->x + i, pos->y, color);
		i++;
	}
}

void
	ft_vertline(t_mlx_data *data, int color, t_pos *pos, t_pos *postwo)
{
	int i;

	i = 0;
	if (pos->y < postwo->y)
	{
		while (i < (postwo->y - pos->y))
		{
			data->img.data[(pos->y + i) * data->sort->resw + pos->x] = color;
			i++;
		}
	}
	else
	{
		while (i < (pos->y - postwo->y))
		{
			data->img.data[(postwo->y + i) * data->sort->resw
											+ postwo->x] = color;
			i++;
		}
	}
}

void
	ft_mlx_vertline(t_mlx_data *data, int color, t_pos *pos, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		data->img.data[(pos->y + i) * data->sort->resw + pos->x] = color;
		i++;
	}
}
