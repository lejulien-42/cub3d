/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 05:28:01 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/03 11:24:15 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_get_color_tex(t_mlx_data *data, int x, int y)
{
	int txf;
	int tyf;
	int txr;
	int tyr;
	int color;

	txf = (int)(data->s_escalier.width * (data->floorx - data->cellx)) &
		(data->s_escalier.width - 1);
	tyf = (int)(data->s_escalier.height * (data->floory - data->celly)) &
		(data->s_escalier.height - 1);
	txr = (int)(data->s_roofeleven.width * (data->floorx - data->cellx)) &
		(data->s_roofeleven.width - 1);
	tyr = (int)(data->s_roofeleven.height * (data->floory - data->celly)) &
		(data->s_roofeleven.height - 1);
	data->floorx += data->floorstepx;
	data->floory += data->floorstepy;
	color = data->s_escalier.data[tyf * data->s_escalier.width + txf];
	data->img.data[y * data->sort->resw + x] = color;
	data->img.data[(data->sort->resh - y - 1) * data->sort->resw + x] =
		data->s_roofeleven.data[data->s_roofeleven.width * tyr + txr];
}

void
	ft_distpoint(t_mlx_data *data, float raydirxo, int x, int y)
{
	float	raydiryone;
	int		p;
	float	posz;
	float	rowdistance;

	raydiryone = data->diry + data->planey;
	p = y - data->sort->resh / 2;
	posz = 0.5 * data->sort->resh;
	rowdistance = posz / p;
	data->floorstepx = rowdistance * (data->raydirxone - raydirxo)
		/ data->sort->resw;
	data->floorstepy = rowdistance * (raydiryone - data->raydiryo)
		/ data->sort->resw;
	data->floorx = data->posx + rowdistance * raydirxo;
	data->floory = data->posy + rowdistance * data->raydiryo;
	x = -1;
	while (++x < data->sort->resw)
	{
		data->cellx = (int)(data->floorx);
		data->celly = (int)(data->floory);
		ft_get_color_tex(data, x, y);
	}
}

void
	ft_floorcasting(t_mlx_data *data)
{
	float	raydirxo;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (data->showbonus == 1)
	{
		while (y < data->sort->resh)
		{
			raydirxo = data->dirx - data->planex;
			data->raydiryo = data->diry - data->planey;
			data->raydirxone = data->dirx + data->planex;
			ft_distpoint(data, raydirxo, x, y);
			y = y + 1;
		}
	}
	else
		ft_setimg(data);
}

void
	ft_dda(t_mlx_data *data)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->posx - data->mapx) *
			data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->posx) *
			data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->posy - data->mapy) *
			data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->posy) *
			data->deltadisty;
	}
}

void
	ft_walldetection(t_mlx_data *data, int *side, int *hit)
{
	char	this;

	if (data->sidedistx < data->sidedisty)
	{
		data->sidedistx = data->sidedistx + data->deltadistx;
		data->mapx = data->mapx + data->stepx;
		*side = 0;
	}
	else
	{
		data->sidedisty = data->sidedisty + data->deltadisty;
		data->mapy = data->mapy + data->stepy;
		*side = 1;
	}
	this = data->map[data->mapx][data->mapy];
	if (this != '0' && this != 'A' && this != '2'
		&& this != 'N' && this != 'S' && this != 'E' && this != 'W')
	{
		data->what = data->map[data->mapx][data->mapy];
		*hit = 1;
	}
}
