/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 03:06:42 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 04:38:37 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"
#include <math.h>

void
	ft_key_event(t_mlx_data *data)
{
	if (data->esc == 1)
		closeit(NULL);
	ft_sprint(data);
	if (data->stamina > 100)
		data->stamina = 100;
	if (data->mkey == 1)
	{
		data->promton = 1;
	}
}

void
	ft_keyr(t_mlx_data *data)
{
	double rotspeed;
	double olddirx;
	double oldplanex;

	oldplanex = data->planex;
	olddirx = data->dirx;
	rotspeed = 0.05;
	if (data->key_right == 1)
	{
		data->dirx = data->dirx * cos(-rotspeed) - data->diry * sin(-rotspeed);
		data->diry = olddirx * sin(-rotspeed) + data->diry * cos(-rotspeed);
		data->planex = data->planex * cos(-rotspeed)
			- data->planey * sin(-rotspeed);
		data->planey = oldplanex * sin(-rotspeed)
			+ data->planey * cos(-rotspeed);
	}
}

void
	ft_keyl(t_mlx_data *data)
{
	double rotspeed;
	double olddiry;
	double oldplanex;

	oldplanex = data->planex;
	olddiry = data->dirx;
	rotspeed = 0.07;
	if (data->key_left == 1)
	{
		data->dirx = data->dirx * cos(rotspeed) - data->diry * sin(rotspeed);
		data->diry = olddiry * sin(rotspeed) + data->diry * cos(rotspeed);
		data->planex = data->planex * cos(rotspeed)
			- data->planey * sin(rotspeed);
		data->planey = oldplanex * sin(rotspeed) + data->planey * cos(rotspeed);
	}
}

void
	ft_teleport(t_mlx_data *data)
{
	if ((int)data->posx == 18 && (int)data->posy == 8)
	{
		data->posx = 20.0 + (data->posx - (int)data->posx);
		data->posy = 20.0 + (data->posy - (int)data->posy);
	}
	if ((int)data->posx == 20 && (int)data->posy == 24)
	{
		data->posx = 4.0 + (data->posx - (int)data->posx);
		data->posy = 13.0 + (data->posy - (int)data->posy);
	}
	if ((int)data->posx == 18 && (int)data->posy == 16)
	{
		data->posx = 20.0 + (data->posx - (int)data->posx);
		data->posy = 20.0 + (data->posy - (int)data->posy);
	}
}
