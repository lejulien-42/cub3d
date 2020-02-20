/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 03:07:42 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/20 05:50:14 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

int
	ft_count_sprite(t_mlx_data *data)
{
	int		i;
	int		j;
	int		count;
	char	texture;

	i = 0;
	count = 0;
	while (i < data->sort->mapwidth)
	{
		j = 0;
		while (j < data->sort->mapheight)
		{
			texture = data->map[i][j];
			if (texture == 'A' || texture == 'B')
				count++;
			j++;
		}
		i++;
	}
	if (!(data->sprite = malloc(count * sizeof(t_sprite))))
		return (-1);
	data->spritenumber = count;
	return (1);
}

void
	ft_putvalues(char *desc, int value)
{
	ft_putstr_fd("\e[95m", 1);
	ft_putstr_fd(desc, 1);
	ft_putstr_fd("\e[34m", 1);
	ft_putnbr_fd(value, 1);
	ft_putstr_fd("\n", 1);
}

void
	ft_putchardesc(char *desc, char *str)
{
	ft_putstr_fd("\e[95m", 1);
	ft_putstr_fd(desc, 1);
	ft_putstr_fd("\e[34m", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
}

void
	ft_debug_sort(t_sort *sort)
{
	ft_putvalues("is_save = ", sort->issave);
	ft_putchardesc("northpath = ", sort->northpath);
	ft_putchardesc("southpath = ", sort->southpath);
	ft_putchardesc("eastpath = ", sort->eastpath);
	ft_putchardesc("westpath = ", sort->westpath);
	ft_putvalues("resw = ", sort->resw);
	ft_putvalues("resh = ", sort->resh);
	ft_putchardesc("sprite = ", sort->sprite);
	ft_putvalues("rgbf = ", sort->rgbf);
	ft_putvalues("rgbc = ", sort->rgbc);
	ft_putvalues("mapwidth = ", sort->mapwidth);
	ft_putvalues("mapheight = ", sort->mapheight);
	write(1, "map = \\/\n", 9);
}

int
	strlennspace(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str != ' ')
			i++;
		str++;
	}
	return (i);
}
