/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycast4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:19:56 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 14:58:04 by lejulien         ###   ########.fr       */
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
	
}
