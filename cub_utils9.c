/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 04:27:45 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/21 18:24:09 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void
	ft_movedownx(t_mlx_data *data)
{
	if (data->map[(int)(data->posx - data->dirx * data->movespeed)]
		[(int)(data->posy)] == '0' ||
		data->map[(int)(data->posx - data->dirx * data->movespeed)]
		[(int)(data->posy)] == '2' ||
		data->map[(int)(data->posx - data->dirx * data->movespeed)]
		[(int)(data->posy)] == '4' ||
		data->map[(int)(data->posx - data->dirx * data->movespeed)]
		[(int)(data->posy)] == '7' ||
		data->map[(int)(data->posx - data->dirx * data->movespeed)]
		[(int)(data->posy)] == 'A' ||
		data->map[(int)(data->posx - data->dirx * data->movespeed)]
		[(int)(data->posy)] == 'B')
		data->posx -= data->dirx * data->movespeed;
}

static void
	ft_moveupx(t_mlx_data *data)
{
	if (data->map[(int)(data->posx + data->dirx * data->movespeed)]
		[(int)(data->posy)] == '0' ||
		data->map[(int)(data->posx + data->dirx * data->movespeed)]
		[(int)(data->posy)] == '2' ||
		data->map[(int)(data->posx + data->dirx * data->movespeed)]
		[(int)(data->posy)] == '4' ||
		data->map[(int)(data->posx + data->dirx * data->movespeed)]
		[(int)(data->posy)] == '7' ||
		data->map[(int)(data->posx + data->dirx * data->movespeed)]
		[(int)(data->posy)] == 'A' ||
		data->map[(int)(data->posx + data->dirx * data->movespeed)]
		[(int)(data->posy)] == 'B')
		data->posx += data->dirx * data->movespeed;
}

static void
	ft_moveupy(t_mlx_data *data)
{
	if (data->map[(int)(data->posx)]
		[(int)(data->posy + data->diry * data->movespeed)] == '0' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->diry * data->movespeed)] == '2' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->diry * data->movespeed)] == '4' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->diry * data->movespeed)] == '7' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->diry * data->movespeed)] == 'A' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->diry * data->movespeed)] == 'B')
		data->posy += data->diry * data->movespeed;
}

void
	ft_handlemove(t_mlx_data *data)
{
	if (data->up == 1 || data->key_up == 1)
	{
		ft_moveupx(data);
		ft_moveupy(data);
	}
	if (data->down == 1 || data->key_down == 1)
	{
		ft_movedownx(data);
		ft_movedowny(data);
	}
	if (data->right == 1)
	{
		ft_moverightx(data);
		ft_moverighty(data);
	}
	if (data->left == 1)
	{
		ft_moveleftx(data);
		ft_movelefty(data);
	}
}

void
	ft_keybr_event(t_mlx_data *data)
{
	ft_key_event(data);
	if (data->health > 0)
	{
		ft_keyr(data);
		ft_keyl(data);
		ft_handlemove(data);
	}
	else
	{
		if (data->r == 1)
		{
			ft_setplayer(12.5, 12.5, data);
			ft_setplayerdir(data, 1);
			data->health = 100;
		}
	}
}
