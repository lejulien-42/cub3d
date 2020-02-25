/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_getdata_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 05:55:34 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/25 06:04:49 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void
	ft_get_data_img(t_mlx_data *data)
{
	data->s_fl.data = (int *)mlx_get_data_addr(data->s_fl.img_ptr,
		&data->s_fl.bpp, &data->s_fl.size_l, &data->s_fl.endian);
	data->s_arrowtexl.data = (int *)mlx_get_data_addr(data->s_arrowtexl.img_ptr,
		&data->s_arrowtexl.bpp, &data->s_arrowtexl.size_l,
		&data->s_arrowtexl.endian);
	data->s_arrowtex.data = (int *)mlx_get_data_addr(data->s_arrowtex.img_ptr,
		&data->s_arrowtex.bpp, &data->s_arrowtex.size_l,
		&data->s_arrowtex.endian);
	data->s_lifeframe.data = (int *)mlx_get_data_addr(data->s_lifeframe.img_ptr,
		&data->s_lifeframe.bpp, &data->s_lifeframe.size_l,
		&data->s_lifeframe.endian);
	data->s_health.data = (int *)mlx_get_data_addr(data->s_health.img_ptr,
		&data->s_health.bpp, &data->s_health.size_l, &data->s_health.endian);
	data->s_monster.data = (int *)mlx_get_data_addr(data->s_monster.img_ptr,
		&data->s_monster.bpp, &data->s_monster.size_l, &data->s_monster.endian);
}

void
	ft_cub_getdata_img(t_mlx_data *data)
{
	data->img.data = (int *)mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
		&data->img.size_l, &data->img.endian);
	data->s_wall.data = (int *)mlx_get_data_addr(data->s_wall.img_ptr,
		&data->s_wall.bpp, &data->s_wall.size_l, &data->s_wall.endian);
	data->s_walltwo.data = (int *)mlx_get_data_addr(data->s_walltwo.img_ptr,
		&data->s_walltwo.bpp, &data->s_walltwo.size_l, &data->s_walltwo.endian);
	data->s_wallthree.data = (int *)mlx_get_data_addr(data->s_wallthree.img_ptr,
		&data->s_wallthree.bpp, &data->s_wallthree.size_l,
		&data->s_wallthree.endian);
	data->s_wallfour.data = (int *)mlx_get_data_addr(data->s_wallfour.img_ptr,
		&data->s_wallfour.bpp, &data->s_wallfour.size_l,
		&data->s_wallfour.endian);
	data->s_lava.data = (int *)mlx_get_data_addr(data->s_lava.img_ptr,
		&data->s_lava.bpp, &data->s_lava.size_l, &data->s_lava.endian);
	data->s_floorfour.data = (int *)mlx_get_data_addr(data->s_floorfour.img_ptr,
		&data->s_floorfour.bpp, &data->s_floorfour.size_l,
		&data->s_floorfour.endian);
	data->s_roofeleven.data = (int *)mlx_get_data_addr(
			data->s_roofeleven.img_ptr, &data->s_roofeleven.bpp,
			&data->s_roofeleven.size_l, &data->s_roofeleven.endian);
	data->s_escalier.data = (int *)mlx_get_data_addr(data->s_escalier.img_ptr,
		&data->s_escalier.bpp, &data->s_escalier.size_l,
		&data->s_escalier.endian);
	ft_get_data_img(data);
}
