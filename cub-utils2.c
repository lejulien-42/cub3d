/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub-utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 03:07:42 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/20 05:20:30 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

int
	ft_count_sprite(t_mlx_data *data)
{
	int i;
	int j;
	int count;
	char texture;

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
