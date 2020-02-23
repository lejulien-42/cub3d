/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_checkmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 06:08:25 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/23 06:55:16 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void
	ft_get_bigger(int i, t_mlx_data *data)
{	
	if (data->biggest < i)
		data->biggest = i;
}

static void
	ft_count_mapsize(t_mlx_data *data)
{
	int	i;
	
	i = 0;
	while (ft_strlen(data->map[i]) != 0)
	{
		ft_get_bigger(ft_strlen(data->map[i]), data);
		i++;
	}
	data->sort->mapheight = i;
	data->sort->mapwidth = data->biggest + 1;
	printf("data=>%d|%d\n", i, data->biggest + 1);
}

void
	ft_checkmap(t_mlx_data *data)
{
	ft_count_mapsize(data);
}