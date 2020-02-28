/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycast2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 01:09:18 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 06:43:31 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_setcamerainfo(t_mlx_data *data, int x)
{
	int hit;

	data->camerax = 2 * x / (double)(data->sort->resw) - 1;
	data->raydirx = data->dirx + data->planex * data->camerax;
	data->raydiry = data->diry + data->planey * data->camerax;
	data->mapx = (int)data->posx;
	data->mapy = (int)data->posy;
	data->deltadistx = fabs(1 / data->raydirx);
	data->deltadisty = fabs(1 / data->raydiry);
	hit = 0;
	ft_dda(data);
	while (hit == 0)
		ft_walldetection(data, &data->side, &hit);
	if (data->side == 0)
		data->perpwalldist = (data->mapx - data->posx + (1 - data->stepx) / 2)
			/ data->raydirx;
	else
		data->perpwalldist = (data->mapy - data->posy + (1 - data->stepy) / 2)
			/ data->raydiry;
}

void
	ft_getlinenwallx(t_mlx_data *data)
{
	data->lineheight = (int)(data->sort->resh / data->perpwalldist);
	data->drawstart = -data->lineheight / 2 + data->sort->resh / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineheight / 2 + data->sort->resh / 2;
	if (data->drawend >= data->sort->resh)
		data->drawend = data->sort->resh - 1;
	if (data->side == 0)
		data->wallx = data->posy + data->perpwalldist * data->raydiry;
	else
		data->wallx = data->posx + data->perpwalldist * data->raydirx;
	data->wallx = data->wallx - floor((data->wallx));
}

static void
	ft_loadsecondside(t_mlx_data *data)
{
	if (data->side == 1 && data->raydiry < 0)
	{
		data->texxs_wallfour = data->s_wallfour.width
			- data->texxs_wallfour - 1;
		data->texxs_arrowtex = data->s_arrowtex.width
			- data->texxs_arrowtex - 1;
		data->texxs_lifeframe = data->s_lifeframe.width
			- data->texxs_lifeframe - 1;
		data->texxs_arrowtexl = data->s_arrowtexl.width
			- data->texxs_arrowtexl - 1;
		data->texxs_walltwo = data->s_walltwo.width
			- data->texxs_walltwo - 1;
		data->texxs_lava = data->s_lava.width
			- data->texxs_lava - 1;
		data->texxs_health = data->s_health.width
			- data->texxs_health - 1;
		data->texxs_fl = data->s_fl.width - data->texxs_fl - 1;
	}
}

static void
	ft_loadfirstside(t_mlx_data *data)
{
	if (data->side == 0 && data->raydirx > 0)
	{
		data->texxs_wallfour = data->s_wallfour.width
			- data->texxs_wallfour - 1;
		data->texxs_wallfour = data->s_lifeframe.width
			- data->texxs_lifeframe - 1;
		data->texxs_arrowtex = data->s_arrowtex.width
			- data->texxs_arrowtex - 1;
		data->texxs_arrowtexl = data->s_arrowtexl.width
			- data->texxs_arrowtexl - 1;
		data->texxs_walltwo = data->s_walltwo.width - data->texxs_walltwo - 1;
		data->texxs_lava = data->s_lava.width - data->texxs_lava - 1;
		data->texxs_health = data->s_health.width - data->texxs_health - 1;
		data->texxs_fl = data->s_fl.width - data->texxs_fl - 1;
	}
	ft_loadsecondside(data);
}

void
	ft_init_texx(t_mlx_data *data)
{
	data->texxs_wallfour = (int)(data->wallx * (double)(data->s_wall.width));
	data->texxs_walltwo = (int)(data->wallx * (double)(data->s_walltwo.width));
	data->texxs_arrowtex = (int)(data->wallx
		* (double)(data->s_arrowtex.width));
	data->texxs_arrowtexl = (int)(data->wallx
		* (double)(data->s_arrowtexl.width));
	data->texxs_lifeframe = (int)(data->wallx
		* (double)(data->s_lifeframe.width));
	data->texxs_lava = (int)(data->wallx * (double)(data->s_lava.width));
	data->texxs_health = (int)(data->wallx * (double)(data->s_health.width));
	data->texxs_fl = (int)(data->wallx * (double)(data->s_fl.width));
	ft_loadfirstside(data);
}
