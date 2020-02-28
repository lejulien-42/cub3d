/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycast4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:19:56 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 16:39:31 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_wallcasting(t_mlx_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < data->sort->resw)
	{
		ft_setcamerainfo(data, x);
		ft_getlinenwallx(data);
		ft_init_texx(data);	
		ft_get_texposray(data);
		ft_putwall_pixel(data, x);
		data->zbuffer[x] = data->perpwalldist;
		x++;
	}
}

void
	ft_loadnsort_sprites(t_mlx_data *data)
{
	int i;

	i = 0;
	data->zbuffer = malloc(data->sort->resw * sizeof(double));
	ft_floorcasting(data);
	ft_wallcasting(data);
	data->spriteorder = malloc(data->spritenumber * sizeof(int));
	data->spritedistance = malloc(data->spritenumber * sizeof(double));
	while (i < data->spritenumber)
	{
		data->spriteorder[i] = i;
		data->spritedistance[i] = ((data->posx - data->sprite[i].x) *
			(data->posx - data->sprite[i].x) + (data->posy - data->sprite[i].y)
			* (data->posy - data->sprite[i].y));
		i++;
	}
	sortsprite(data->spriteorder, data->spritedistance, data->spritenumber);
}

static void
	ft_init_sprite2(t_mlx_data *data, int i)
{
	data->spritewidth = abs((int)(data->sort->resh / (data->transformy)));
	data->drawstartx = -data->spritewidth / 2 + data->spritescreenx;
	if (data->drawstartx < 0)
		data->drawstartx = 0;
	data->drawendx = data->spritewidth / 2 + data->spritescreenx;
	if (data->drawendx >= data->sort->resw)
		data->drawendx = data->sort->resw - 1;
	data->stripe = data->drawstartx;
}

void
	ft_init_sprite(t_mlx_data *data, int i)
{
	double  invDet;

	data->spritex = data->sprite[data->spriteorder[i]].x - data->posx;
	data->spritey = data->sprite[data->spriteorder[i]].y - data->posy;
	invDet = 1.0 / (data->planex * data->diry - data->dirx *
		data->planey);
	data->transformx = invDet * (data->diry * data->spritex - data->dirx
		* data->spritey);
	data->transformy = invDet * (-data->planey * data->spritex + data->planex
		* data->spritey);
	data->spritescreenx = (int)((data->sort->resw / 2) * (1 +
		data->transformx / data->transformy));
	data->spriteheight = abs((int)(data->sort->resh / (data->transformy)));
	data->drawstarty = -data->spriteheight / 2 + data->sort->resh / 2;
	if (data->drawstarty < 0)
		data->drawstarty = 0;
	data->drawendy = data->spriteheight / 2 + data->sort->resh / 2;
	if (data->drawendy >= data->sort->resh)
		data->drawendy = data->sort->resh - 1;
	ft_init_sprite2(data, i);
}

void
	ft_getsprite_color(t_mlx_data *data, int i, int y, int texx)
{
	int d = (y) * 256 - data->sort->resh * 128 + data->spriteheight * 128;
	int texy = ((d * texHeight) / data->spriteheight) / 256;
	int color = 0;
	if (texWidth * texy + texx > 0)
	{
		if (data->sprite[data->spriteorder[i]].texture == 0)
			color = data->s_fl.data[texWidth * texy + texx];
		else
			color = data->s_monster.data[texWidth * texy + texx];
		if (color != -16777216)
			data->img.data[y * data->sort->resw + data->stripe] = color;
	}
}