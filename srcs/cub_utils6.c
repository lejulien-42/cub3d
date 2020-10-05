/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 00:28:27 by lejulien          #+#    #+#             */
/*   Updated: 2020/10/05 17:01:02 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void
	ft_second_brain(t_mlx_data *data)
{
	if (data->posx > data->sprite[data->ord].x - 0.5 && data->posx
		< data->sprite[data->ord].x + 0.5
			&& data->posy > data->sprite[data->ord].y - 0.5 && data->posy
				< data->sprite[data->ord].y + 0.5)
		data->health++;
}

void
	ft_spookia(t_mlx_data *data)
{
	double	reached_pos = data->movespeed / 3;
	double	lposx = data->sprite[data->ord].x;
	double	lposy = data->sprite[data->ord].y;
	if (data->sprite[data->ord].texture == 0)
	{
		if (data->sprite[data->ord].x < data->posx && lposx + reached_pos)
			data->sprite[data->ord].x = data->sprite[data->ord].x
				+ data->movespeed / 3;
		if (data->sprite[data->ord].x > data->posx && lposx - reached_pos)
			data->sprite[data->ord].x = data->sprite[data->ord].x
				- data->movespeed / 3;
		if (data->sprite[data->ord].y < data->posy && lposy + reached_pos)
			data->sprite[data->ord].y = data->sprite[data->ord].y
				+ data->movespeed / 3;
		if (data->sprite[data->ord].y > data->posy)
			data->sprite[data->ord].y = data->sprite[data->ord].y
				- data->movespeed / 3;
		if (data->posx > data->sprite[data->ord].x - 0.5 && data->posx
			< data->sprite[data->ord].x + 0.5
				&& data->posy > data->sprite[data->ord].y - 0.5 && data->posy
					< data->sprite[data->ord].y + 0.5)
			data->health--;
	}
	else
		ft_second_brain(data);
	data->ord++;
}

static void
	ft_do_north(t_mlx_data *data)
{
	data->dirx = -1;
	data->diry = 0;
	data->planex = 0;
	data->planey = 0.66;
}

void
	ft_setplayerdir(t_mlx_data *data, int dir)
{
	if (dir == 0)
		ft_do_north(data);
	if (dir == 1)
	{
		data->dirx = 1;
		data->diry = 0;
		data->planex = 0;
		data->planey = -0.66;
	}
	if (dir == 2)
	{
		data->dirx = 0;
		data->diry = 1;
		data->planex = 0.66;
		data->planey = 0;
	}
	if (dir == 3)
	{
		data->dirx = 0;
		data->diry = -1;
		data->planex = -0.66;
		data->planey = 0;
	}
}

void
	ft_sprint(t_mlx_data *data)
{
	if (data->shift == 1 && data->hasstamina == 1 && data->health > 0)
	{
		data->movespeed = 0.1;
		data->stamina--;
		if (data->stamina <= 0)
		{
			data->hasstamina = 0;
			data->stamina = 0;
		}
	}
	else
	{
		data->stamina++;
		if (data->stamina == 100)
			data->hasstamina = 1;
	}
}
