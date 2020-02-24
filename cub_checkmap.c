/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_checkmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 06:08:25 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/24 22:28:46 by lejulien         ###   ########.fr       */
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
}

static void
	ft_setplayerdirnpos(t_mlx_data *data, int i, int j)
{
	char c;

	c = data->map[j][i];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (data->playercount == 0)
		{
			ft_setplayer(j + 0.5, i + 0.5, data);
			if (c == 'N')
				ft_setplayerdir(data, 0);
			else if (c == 'S')
				ft_setplayerdir(data, 1);
			else if (c == 'E')
				ft_setplayerdir(data, 2);
			else
				ft_setplayerdir(data, 3);
		}
		data->playercount++;
	}
}

static void
	ft_count_player(t_mlx_data *data)
{
	int i;
	int j;
	char c;

	j = 0;
	data->playercount = 0;
	while (ft_strlen(data->map[j]) != 0)
	{
		i = 0;
		while (data->map[j][i] != '\0')
		{
			ft_setplayerdirnpos(data, i, j);
			i++;
		}
		j++;
	}
	if (data->playercount == 0)
		ft_puterror("\e[31mError no player on map\n");
	else if (data->playercount > 1)
		ft_puterror("\e[31mError too much player on map\n");
}

void
	ft_checkmap(t_mlx_data *data)
{
	ft_count_mapsize(data);
	ft_count_player(data);
	ft_checkmapborder(data);
}
