/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 03:41:26 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/24 21:14:47 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_moveleftx(t_mlx_data *data)
{
	if (data->map[(int)(data->posx - data->planex * data->movespeed)]
		[(int)(data->posy)] == '0' ||
		data->map[(int)(data->posx - data->planex * data->movespeed)]
		[(int)(data->posy)] == '2' ||
		data->map[(int)(data->posx - data->planex * data->movespeed)]
		[(int)(data->posy)] == '4' ||
		data->map[(int)(data->posx - data->planex * data->movespeed)]
		[(int)(data->posy)] == '7' ||
		data->map[(int)(data->posx - data->planex * data->movespeed)]
		[(int)(data->posy)] == 'A' ||
		data->map[(int)(data->posx - data->planex * data->movespeed)]
		[(int)(data->posy)] == 'B' ||
		data->map[(int)(data->posx - data->planex * data->movespeed)]
		[(int)(data->posy)] == 'N' ||
		data->map[(int)(data->posx - data->planex * data->movespeed)]
		[(int)(data->posy)] == 'S' ||
		data->map[(int)(data->posx - data->planex * data->movespeed)]
		[(int)(data->posy)] == 'E' ||
		data->map[(int)(data->posx - data->planex * data->movespeed)]
		[(int)(data->posy)] == 'W')
		data->posx -= data->planex * data->movespeed;
}

void
	ft_movelefty(t_mlx_data *data)
{
	if (data->map[(int)(data->posx)]
		[(int)(data->posy - data->planey * data->movespeed)] == '0' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->planey * data->movespeed)] == '2' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->planey * data->movespeed)] == '4' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->planey * data->movespeed)] == '7' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->planey * data->movespeed)] == 'A' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->planey * data->movespeed)] == 'B' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->planey * data->movespeed)] == 'N' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->planey * data->movespeed)] == 'S' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->planey * data->movespeed)] == 'E' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->planey * data->movespeed)] == 'W')
		data->posy -= data->planey * data->movespeed;
}

void
	ft_moverightx(t_mlx_data *data)
{
	if (data->map[(int)(data->posx + data->planex * data->movespeed)]
		[(int)(data->posy)] == '0' ||
		data->map[(int)(data->posx + data->planex * data->movespeed)]
		[(int)(data->posy)] == '2' ||
		data->map[(int)(data->posx + data->planex * data->movespeed)]
		[(int)(data->posy)] == '4' ||
		data->map[(int)(data->posx + data->planex * data->movespeed)]
		[(int)(data->posy)] == '7' ||
		data->map[(int)(data->posx + data->planex * data->movespeed)]
		[(int)(data->posy)] == 'A' ||
		data->map[(int)(data->posx + data->planex * data->movespeed)]
		[(int)(data->posy)] == 'B' ||
		data->map[(int)(data->posx + data->planex * data->movespeed)]
		[(int)(data->posy)] == 'N' ||
		data->map[(int)(data->posx + data->planex * data->movespeed)]
		[(int)(data->posy)] == 'S' ||
		data->map[(int)(data->posx + data->planex * data->movespeed)]
		[(int)(data->posy)] == 'E' ||
		data->map[(int)(data->posx + data->planex * data->movespeed)]
		[(int)(data->posy)] == 'W')
		data->posx += data->planex * data->movespeed;
}

void
	ft_moverighty(t_mlx_data *data)
{
	if (data->map[(int)(data->posx)]
		[(int)(data->posy + data->planey * data->movespeed)] == '0' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->planey * data->movespeed)] == '2' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->planey * data->movespeed)] == '4' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->planey * data->movespeed)] == '7' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->planey * data->movespeed)] == 'A' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->planey * data->movespeed)] == 'B' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->planey * data->movespeed)] == 'N' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->planey * data->movespeed)] == 'S' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->planey * data->movespeed)] == 'E' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy + data->planey * data->movespeed)] == 'W')
		data->posy += data->planey * data->movespeed;
}

void
	ft_movedowny(t_mlx_data *data)
{
	if (data->map[(int)(data->posx)]
		[(int)(data->posy - data->diry * data->movespeed)] == '0' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->diry * data->movespeed)] == '2' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->diry * data->movespeed)] == '4' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->diry * data->movespeed)] == '7' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->diry * data->movespeed)] == 'A' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->diry * data->movespeed)] == 'B' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->diry * data->movespeed)] == 'N' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->diry * data->movespeed)] == 'S' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->diry * data->movespeed)] == 'E' ||
		data->map[(int)(data->posx)]
		[(int)(data->posy - data->diry * data->movespeed)] == 'W')
		data->posy -= data->diry * data->movespeed;
}
