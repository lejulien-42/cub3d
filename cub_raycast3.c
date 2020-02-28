/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycast3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:26:41 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 14:08:09 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_get_texposray(t_mlx_data *data)
{
	data->steps_wallfour = 1.0 * data->s_wallfour.height / data->lineheight;
	data->steps_arrowtex = 1.0 * data->s_arrowtex.height / data->lineheight;
	data->steps_lifeframe = 1.0 * data->s_lifeframe.height / data->lineheight;
	data->steps_arrowtexl = 1.0 * data->s_arrowtexl.height / data->lineheight;
	data->steps_walltwo = 1.0 * data->s_walltwo.height / data->lineheight;
	data->steps_lava = 1.0 * data->s_lava.height / data->lineheight;
	data->steps_health = 1.0 * data->s_health.height / data->lineheight;
	data->steps_fl = 1.0 * data->s_fl.height / data->lineheight;
	data->texposs_wallfour = (data->drawstart - data->sort->resh / 2
		+ data->lineheight / 2) * data->steps_wallfour;
	data->texposs_arrowtex = (data->drawstart - data->sort->resh / 2
		+ data->lineheight / 2) * data->steps_arrowtex;
	data->texposs_lifeframe = (data->drawstart - data->sort->resh / 2
		+ data->lineheight / 2) * data->steps_lifeframe;
	data->texposs_arrowtexl = (data->drawstart - data->sort->resh / 2
		+ data->lineheight / 2) * data->steps_arrowtexl;
	data->texposs_walltwo = (data->drawstart - data->sort->resh / 2
		+ data->lineheight / 2) * data->steps_walltwo;
	data->texposs_lava = (data->drawstart - data->sort->resh / 2
		+ data->lineheight / 2) * data->steps_lava;
	data->texposs_fl = (data->drawstart - data->sort->resh / 2
		+ data->lineheight / 2) * data->steps_fl;
	data->texposs_health = (data->drawstart - data->sort->resh / 2
		+ data->lineheight / 2) * data->steps_health;
}

void
	ft_reset_poss(t_mlx_data *data)
{
	data->texposs_wallfour = data->texposs_wallfour + data->steps_wallfour;
	data->texposs_arrowtex = data->texposs_arrowtex + data->steps_arrowtex;
	data->texposs_arrowtexl = data->texposs_arrowtexl + data->steps_arrowtexl;
	data->texposs_lifeframe = data->texposs_lifeframe + data->steps_lifeframe;
	data->texposs_walltwo = data->texposs_walltwo + data->steps_walltwo;
	data->texposs_lava = data->texposs_lava + data->steps_lava;
	data->texposs_health = data->texposs_health + data->steps_health;
	data->texposs_fl = data->texposs_fl + data->steps_fl;
}

int
	ft_fourtexcube(t_mlx_data *data)
{
	int color;

	if (data->side == 1)
	{
		if (data->raydiry < 0)
			color = data->s_lava.data[((int)data->texposs_lava
				& (data->s_lava.height - 1)) * data->s_lava.height
				+ data->texxs_lava];
		else
			color = data->s_health.data[((int)data->texposs_health
				& (data->s_health.height - 1)) * data->s_health.height
				+ data->texxs_health];
	}
	else
	{
		if (data->raydirx < 0)
			color = data->s_wallfour.data[((int)data->texposs_wallfour
				& (data->s_wallfour.height - 1)) * data->s_wallfour.height
				+ data->texxs_wallfour];
		else
			color = data->s_walltwo.data[((int)data->texposs_walltwo
				& (data->s_walltwo.height - 1)) * data->s_walltwo.height
				+ data->texxs_walltwo];
	}
	return (color);
}

int
	ft_set_texture(t_mlx_data *data)
{
	int color;
	
	color = 0;
	if (data->what == '1')
		color = ft_fourtexcube(data);
	else if (data->what == '3')
		color = data->s_wallfour.data[((int)data->texposs_wallfour & (data->s_wallfour.height - 1)) * data->s_wallfour.height + data->texxs_wallfour];
	else if (data->what == '2')
		color = data->s_fl.data[((int)data->texposs_fl & (data->s_fl.height - 1)) * data->s_fl.height + data->texxs_fl];
	else if (data->what == '7')
		color = data->s_arrowtex.data[((int)data->texposs_arrowtex & (data->s_arrowtex.height - 1)) * data->s_arrowtex.height + data->texxs_arrowtex];
	else if (data->what == '8')
		color = data->s_arrowtexl.data[((int)data->texposs_arrowtexl & (data->s_arrowtexl.height - 1)) * data->s_arrowtexl.height + data->texxs_arrowtexl];
	else if (data->what == '9')
		color = data->s_lifeframe.data[((int)data->texposs_lifeframe & (data->s_lifeframe.height - 1)) * data->s_lifeframe.height + data->texxs_lifeframe];
	else
		color = data->s_wallfour.data[((int)data->texposs_wallfour & (data->s_wallfour.height - 1)) * data->s_wallfour.height + data->texxs_wallfour];
	return (color);
}

void
	ft_putwall_pixel(t_mlx_data *data, int x)
{
	int y;
	
	y = data->drawstart;	
	while (y < data->drawend)
	{
		ft_reset_poss(data);
		data->img.data[y * data->sort->resw + x] = ft_set_texture(data);
		y++;
	}
}
