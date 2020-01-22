/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_mlx_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 15:35:23 by lejulien          #+#    #+#             */
/*   Updated: 2020/01/05 02:13:58 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

pos_t	ft_set_pos(int x, int y)
{
	pos_t	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

square_t	ft_set_square(int w, int h, int x, int y)
{
	square_t	square;

	square.pos = ft_set_pos(x, y);
	square.w = w;
	square.h = h;
	return (square);
}

void	ft_mlx_horizline(data_t *data, int color, pos_t *pos, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		mlx_pixel_put(data->mlx_ptr, data->mlx_win, pos->x + i, pos->y, color);
		i++;
	}
}

void	ft_mlx_vertline(mlx_data_t *data, int color, pos_t *pos, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		data->img.data[(pos->y + i) * data->sort->resw + pos->x] = color;
		i++;
	}
}

void
	ft_mlx_draw_square(square_t *square, data_t *data, int color)
{
	pos_t bottomleft;
	pos_t topright;

	bottomleft = ft_set_pos(square->pos.x, square->pos.y + square->h);
	topright = ft_set_pos(square->pos.x + square->w, square->pos.y);
	ft_mlx_horizline(data, color, &square->pos, square->w);
	ft_mlx_vertline(data, color, &square->pos, square->h);
	ft_mlx_horizline(data, color, &bottomleft, square->w);
	ft_mlx_vertline(data, color, &topright, square->h);
}

void
	ft_mlx_drawfilled_square(square_t *square, data_t *data, int color, mlx_data_t *datamlx)
{
	int		i;

	i = 0;
	while (i < square->w)
	{
		ft_mlx_vertline(datamlx, color, &square->pos, square->h);
		square->pos.x++;
		i++;
	}
}
/*
int	main(void)
{
	data_t		data;
	player_t	player;
	square_t	square;

	square = ft_set_square(599, 599, 0, 0);
	if (!(data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, 600, 600, "cub3d")))
		return (EXIT_FAILURE);
	ft_mlx_draw_square(&square, &data, rgb_int(255, 0, 0));
	square = ft_set_square(64, 64, 50, 50);
	ft_mlx_draw_square(&square, &data, rgb_int(0, 255, 255));
	square = ft_set_square(300, 300, 100, 50);
	ft_mlx_draw_square(&square, &data, rgb_int(0, 255, 0));
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
*/
