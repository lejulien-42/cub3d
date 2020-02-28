/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 01:04:04 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 21:59:10 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_puterror(char *text)
{
	ft_putstr_fd("\e[34m", 2);
	ft_putstr_fd(text, 2);
	exit(0);
}

t_sort
	ft_initialaze_sort(void)
{
	t_sort	sort;

	sort.issave = 0;
	sort.isbonus = 0;
	sort.northpath = NULL;
	sort.southpath = NULL;
	sort.eastpath = NULL;
	sort.westpath = NULL;
	sort.resw = 700;
	sort.resh = 500;
	sort.sprite = NULL;
	sort.rgbf = 0;
	sort.rgbc = 0;
	sort.mapwidth = 33;
	sort.mapheight = 33;
	sort.currentline = NULL;
	sort.previousline = NULL;
	return (sort);
}

static void
	ft_attrib2(int x, int y, char type, t_mlx_data *data)
{
	int s;

	s = data->s;
	data->sprite[s].y = x + 0.5;
	data->sprite[s].x = y + 0.5;
	if (type == 'A')
		data->sprite[s].texture = 0;
	else
		data->sprite[s].texture = 1;
}

int
	ft_attrib_sprite(t_mlx_data *data)
{
	int		s;
	int		y;
	int		x;
	char	type;

	s = 0;
	y = 0;
	while (ft_strlen(data->map[y]) != 0)
	{
		x = 0;
		while (x < ft_strlen(data->map[y]))
		{
			type = data->map[y][x];
			if (type == 'A' || type == 'B')
			{
				data->s = s;
				ft_attrib2(x, y, type, data);
				s++;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int
	rgb_int(int red, int green, int blue)
{
	int	rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}
