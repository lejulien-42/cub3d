/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 05:28:01 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/26 07:10:47 by lejulien         ###   ########.fr       */
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
	float	raydiryone = data->diry + data->planey;

	int p = y - data->sort->resh / 2;

	float posZ = 0.5 * data->sort->resh;

	float rowDistance = posZ / p;

	data->floorstepx = rowDistance * (data->raydirxone - raydirxo) / data->sort->resw;
	data->floorstepy = rowDistance * (raydiryone - data->raydiryo) / data->sort->resw;

	data->floorx = data->posx + rowDistance * raydirxo;
	data->floory = data->posy + rowDistance * data->raydiryo;
	x = -1;
	while (++x < data->sort->resw)
	{
		data->cellx = (int)(data->floorx);
		data->celly = (int)(data->floory);
		ft_get_color_tex(data, x, y);
	}
}
