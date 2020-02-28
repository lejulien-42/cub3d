/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:11:38 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 21:17:29 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "cub.h"
#include "get_next_line.h"
#include "./libft-42/libft.h"

static void
	ft_raycast2(t_mlx_data *data, int i)
{
	int texx;
	int y;

	while (data->stripe < data->drawendx)
	{
		texx = (int)(256 * (data->stripe - (-data->spritewidth / 2 +
		data->spritescreenx)) * TEXWIDTH / data->spritewidth) / 256;
		if (data->transformy > 0 && data->stripe > 0 && data->stripe <
		data->sort->resw && data->transformy < data->zbuffer[data->stripe])
		{
			y = data->drawstarty;
			while (y < data->drawendy)
			{
				ft_getsprite_color(data, i, y, texx);
				y++;
			}
		}
		data->stripe++;
	}
}

void
	ft_raycast(t_mlx_data *data)
{
	int	i;

	ft_loadnsort_sprites(data);
	i = 0;
	while (i < data->spritenumber)
	{
		ft_init_sprite(data, i);
		ft_raycast2(data, i);
		i++;
	}
	free(data->zbuffer);
	free(data->spriteorder);
	free(data->spritedistance);
}

int
	main(int argc, const char *argv[])
{
	t_sort	sort;
	int		fd;
	int		error;

	error = 0;
	sort = ft_initialaze_sort();
	fd = 0;
	if (argc == 2 || argc == 3)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			error = 1;
		if (argc == 3 && (ft_strncmp(argv[2], "-save", 6) == 0
			|| ft_strncmp(argv[2], "--save", 6) == 0))
			sort.issave = 1;
		else if (argc == 3)
			error = 1;
		if (error)
			ft_puterror("Error  bad arguments\n");
		ft_sort_and_rend(fd, &sort);
	}
	return (0);
}
