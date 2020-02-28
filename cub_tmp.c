/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:11:38 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 14:59:11 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "cub.h"
#include "get_next_line.h"
#include "./libft-42/libft.h"

void
	ft_raycast(t_mlx_data *data)
{
	int		x;
	int		y;

	data->zbuffer = malloc(data->sort->resw * sizeof(double));
	y = 0;
	x = 0;
	ft_floorcasting(data);
	ft_wallcasting(data);
	//sprite casting
	int	i = 0;
	int numSprite = data->spritenumber;
	int spriteOrder[numSprite];
	double  spriteDistance[numSprite];
	while (i < numSprite)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((data->posx - data->sprite[i].x) * (data->posx - data->sprite[i].x) + (data->posy - data->sprite[i].y) * (data->posy - data->sprite[i].y));
		i++;
	}
	sortsprite(spriteOrder, spriteDistance, numSprite);
	i = 0;
	while (i < numSprite)
	{
		double  spriteX = data->sprite[spriteOrder[i]].x - data->posx;
		double  spriteY = data->sprite[spriteOrder[i]].y - data->posy;

		double  invDet = 1.0 / (data->planex * data->diry - data->dirx * data->planey);

		double  transformX = invDet * (data->diry * spriteX - data->dirx * spriteY);
		double  transformY = invDet * (-data->planey * spriteX + data->planex * spriteY);

		int	 spriteScreenX = (int)((data->sort->resw / 2) * (1 + transformX / transformY));

		int	 spriteHeight = abs((int)(data->sort->resh / (transformY)));
		int	 drawStartY = -spriteHeight / 2 + data->sort->resh / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int	 drawEndY = spriteHeight / 2 + data->sort->resh / 2;
		if (drawEndY >= data->sort->resh)
			drawEndY = data->sort->resh - 1;

		int	 spriteWidth = abs((int)(data->sort->resh / (transformY)));
		int	 drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int	 drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= data->sort->resw)
			drawEndX = data->sort->resw - 1;

		int stripe = drawStartX;
		while (stripe < drawEndX)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;

			if (transformY > 0 && stripe > 0 && stripe < data->sort->resw && transformY < data->zbuffer[stripe])
			{
				int y = drawStartY;
				while (y < drawEndY)
				{
					int d = (y) * 256 - data->sort->resh * 128 + spriteHeight * 128;
					int texY = ((d * texHeight) / spriteHeight) / 256;
					int color = 0;
					if (texWidth * texY + texX > 0)
					{
						if (data->sprite[spriteOrder[i]].texture == 0)
							color = data->s_fl.data[texWidth * texY + texX];
						else
							color = data->s_monster.data[texWidth * texY + texX];
						if (color != -16777216)
							data->img.data[y * data->sort->resw + stripe] = color;
					}
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
	free(data->zbuffer);
}


int main(int argc, const char *argv[])
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
		if (argc == 3 && (ft_strncmp(argv[2], "-save", 6) == 0 || ft_strncmp(argv[2], "--save", 6) == 0))
			sort.issave = 1;
		else if (argc == 3)
			error = 1;
		if (error)
			ft_puterror("Error  bad arguments\n");
		ft_sort_and_rend(fd, &sort);
	}
	return (0);
}
