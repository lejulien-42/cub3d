/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:11:38 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/25 07:10:21 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "cub.h"
#include "get_next_line.h"
#include "./libft-42/libft.h"
#define texWidth 512
#define texHeight 512

char
	*ft_compressmap(int fd, t_sort *sort)
{
	int		ret;
	int	isatmap;
	char *tofree;
	char *temp;

	ret = 1;
	isatmap = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &sort->currentline);
		if (sort->currentline[0] == '1')
			isatmap = 1;
		if (isatmap)
		{
			if (ret == 0)
			{
				free(sort->currentline);
				return (sort->previousline);
			}
			check_line_start(&sort->currentline, ret);
			if (sort->previousline)
			{
				tofree = ft_strjoin(sort->previousline, "~");
				temp = ft_strjoin(tofree, sort->currentline);
				ft_subspace(temp);
				free(tofree);
				free(sort->previousline);
				sort->previousline = ft_subspace(temp);
				free(temp);
				free(sort->currentline);
			}
		}
		else
		{
			sort->previousline = sort->currentline;
			ft_check_types(sort->currentline, sort, ret);
		}
	}
	return (NULL);
}

void
	ft_raycast(t_mlx_data *data)
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		x = 0;
	int		y = 0;
	char	zbuffer[data->sort->resw];

	if (data->showbonus == 1)
	{
		while (y < data->sort->resh)
		{
			float	rayDirX0 = data->dirx - data->planex;
			float	rayDirY0 = data->diry - data->planey;
			float	rayDirX1 = data->dirx + data->planex;
			float	rayDirY1 = data->diry + data->planey;

			int p = y - data->sort->resh / 2;

			float posZ = 0.5 * data->sort->resh;

			float rowDistance = posZ / p;

			float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / data->sort->resw;
			float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / data->sort->resw;

			float floorX = data->posx + rowDistance * rayDirX0;
			float floorY = data->posy + rowDistance * rayDirY0;
			x = 0;
			while (++x < data->sort->resw)
			{
				int cellX = (int)(floorX);
				int cellY = (int)(floorY);

				int txf = (int)(data->s_escalier.width * (floorX - cellX)) & (data->s_escalier.width - 1);
				int tyf = (int)(data->s_escalier.height * (floorY - cellY)) & (data->s_escalier.height - 1);
				int txr = (int)(data->s_roofeleven.width * (floorX - cellX)) & (data->s_roofeleven.width - 1);
				int tyr = (int)(data->s_roofeleven.height * (floorY - cellY)) & (data->s_roofeleven.height - 1);
				floorX += floorStepX;
				floorY += floorStepY;
				int color =  data->s_escalier.data[tyf * data->s_escalier.width + txf];
				data->img.data[y * data->sort->resw + x] = color;
				data->img.data[(data->sort->resh - y - 1) * data->sort->resw + x] = data->s_roofeleven.data[data->s_roofeleven.width * tyr + txr];
			}
			y++;
		}
	}
	else
		ft_setimg(data);
	y = 0;
	x = 0;
	while (x < data->sort->resw)
	{
		cameraX = 2 * x / (double)(data->sort->resw) - 1;
		rayDirX = data->dirx + data->planex * cameraX;
		rayDirY = data->diry + data->planey * cameraX;
		int mapX = (int)data->posx;
		int mapY = (int)data->posy;
		double sideDistX;
		double sideDistY;
		char	what;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWalldist;

		int	stepX;
		int	stepY;

		int	hit = 0;
		int	side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->posx - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posx) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->posy - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posy) * deltaDistY;
		}

		//detection des murs
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX = sideDistX + deltaDistX;
				mapX = mapX + stepX;
				side = 0;
			}
			else
			{
				sideDistY = sideDistY + deltaDistY;
				mapY = mapY + stepY;
				side = 1;
			}
			char this = data->map[mapX][mapY];
			if (this != '0' && this != 'A' && this != 'B'
				&& this != 'N' && this != 'S' && this != 'E' && this != 'W')
			{
				what = data->map[mapX][mapY];
				hit = 1;
			}
		}

		if (side == 0)
			perpWalldist = (mapX - data->posx + (1 - stepX) / 2) / rayDirX;
		else
			perpWalldist = (mapY - data->posy + (1 - stepY) / 2) / rayDirY;


		int lineheight = (int)(data->sort->resh / perpWalldist);


		int drawstart = -lineheight / 2 + data->sort->resh / 2;

		if (drawstart < 0)
			drawstart = 0;

		int drawend = lineheight / 2 + data->sort->resh / 2;
		if (drawend >= data->sort->resh)
			drawend = data->sort->resh - 1;

		double wallx;
		if (side == 0)
			wallx = data->posy + perpWalldist * rayDirY;
		else
			wallx = data->posx + perpWalldist * rayDirX;
		wallx = wallx - floor((wallx));


		int texxs_wallfour = (int)(wallx * (double)(data->s_wall.width));
		int texxs_walltwo = (int)(wallx * (double)(data->s_walltwo.width));
		int texxs_arrowtex = (int)(wallx * (double)(data->s_arrowtex.width));
		int texxs_arrowtexl = (int)(wallx * (double)(data->s_arrowtexl.width));
		int texxs_lifeframe = (int)(wallx * (double)(data->s_lifeframe.width));
		int texxs_lava = (int)(wallx * (double)(data->s_lava.width));
		int texxs_health = (int)(wallx * (double)(data->s_health.width));
		int texxs_fl = (int)(wallx * (double)(data->s_fl.width));
		if (side == 0 && rayDirX > 0)
		{
			texxs_wallfour = data->s_wallfour.width - texxs_wallfour - 1;
			texxs_wallfour = data->s_lifeframe.width - texxs_lifeframe - 1;
			texxs_arrowtex = data->s_arrowtex.width - texxs_arrowtex - 1;
			texxs_arrowtexl = data->s_arrowtexl.width - texxs_arrowtexl - 1;
			texxs_walltwo = data->s_walltwo.width - texxs_walltwo - 1;
			texxs_lava = data->s_lava.width - texxs_lava - 1;
			texxs_health = data->s_health.width - texxs_health - 1;
			texxs_fl = data->s_fl.width - texxs_fl - 1;
		}
		if (side == 1 && rayDirY < 0)
		{
			texxs_wallfour = data->s_wallfour.width - texxs_wallfour - 1;
			texxs_arrowtex = data->s_arrowtex.width - texxs_arrowtex - 1;
			texxs_lifeframe = data->s_lifeframe.width - texxs_lifeframe - 1;
			texxs_arrowtexl = data->s_arrowtexl.width - texxs_arrowtexl - 1;
			texxs_walltwo = data->s_walltwo.width - texxs_walltwo - 1;
			texxs_lava = data->s_lava.width - texxs_lava - 1;
			texxs_health = data->s_health.width - texxs_health - 1;
			texxs_fl = data->s_fl.width - texxs_fl - 1;
		}

		double steps_wallfour = 1.0 * data->s_wallfour.height / lineheight;
		double steps_arrowtex = 1.0 * data->s_arrowtex.height / lineheight;
		double steps_lifeframe = 1.0 * data->s_lifeframe.height / lineheight;
		double steps_arrowtexl = 1.0 * data->s_arrowtexl.height / lineheight;
		double steps_walltwo = 1.0 * data->s_walltwo.height / lineheight;
		double steps_lava = 1.0 * data->s_lava.height / lineheight;
		double steps_health = 1.0 * data->s_health.height / lineheight;
		double steps_fl = 1.0 * data->s_fl.height / lineheight;


		double texposs_wallfour = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_wallfour;
		double texposs_arrowtex = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_arrowtex;
		double texposs_lifeframe = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_lifeframe;
		double texposs_arrowtexl = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_arrowtexl;
		double texposs_walltwo = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_walltwo;
		double texposs_lava = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_lava;
		double texposs_fl = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_fl;
		double texposs_health = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_health;
		
		int y = drawstart;
		while (y < drawend)
		{
			texposs_wallfour = texposs_wallfour + steps_wallfour;
			texposs_arrowtex = texposs_arrowtex + steps_arrowtex;
			texposs_arrowtexl = texposs_arrowtexl + steps_arrowtexl;
			texposs_lifeframe = texposs_lifeframe + steps_lifeframe;
			texposs_walltwo = texposs_walltwo + steps_walltwo;
			texposs_lava = texposs_lava + steps_lava;
			texposs_health = texposs_health + steps_health;
			texposs_fl = texposs_fl + steps_fl;
			int color = 0;
			if (what == '1')
			{
				if (side == 1)
				{
					if (rayDirY < 0)
						color = data->s_lava.data[((int)texposs_lava & (data->s_lava.height - 1)) * data->s_lava.height + texxs_lava]; //TEX_WEST
					else
						color = data->s_health.data[((int)texposs_health & (data->s_health.height - 1)) * data->s_health.height + texxs_health]; //TEX_SOUTH
				}
				else
				{
					if (rayDirX < 0)
						color = data->s_wallfour.data[((int)texposs_wallfour & (data->s_wallfour.height - 1)) * data->s_wallfour.height + texxs_wallfour]; //TEX_EAST
					else
						color = data->s_walltwo.data[((int)texposs_walltwo & (data->s_walltwo.height - 1)) * data->s_walltwo.height + texxs_walltwo]; //TEX_NORTH
				}
			}
			else if (what == '3')
			{
				color = data->s_wallfour.data[((int)texposs_wallfour & (data->s_wallfour.height - 1)) * data->s_wallfour.height + texxs_wallfour];
			}
			else if (what == '2')
				color = data->s_fl.data[((int)texposs_fl & (data->s_fl.height - 1)) * data->s_fl.height + texxs_fl];
			else if (what == '7')
				color = data->s_arrowtex.data[((int)texposs_arrowtex & (data->s_arrowtex.height - 1)) * data->s_arrowtex.height + texxs_arrowtex];
			else if (what == '8')
				color = data->s_arrowtexl.data[((int)texposs_arrowtexl & (data->s_arrowtexl.height - 1)) * data->s_arrowtexl.height + texxs_arrowtexl];
			else if (what == '9')
				color = data->s_lifeframe.data[((int)texposs_lifeframe & (data->s_lifeframe.height - 1)) * data->s_lifeframe.height + texxs_lifeframe];
			else
			{
				color = data->s_wallfour.data[((int)texposs_wallfour & (data->s_wallfour.height - 1)) * data->s_wallfour.height + texxs_wallfour];
			}
			data->img.data[y * data->sort->resw + x] = color;
			y++;
		}
		zbuffer[x] = perpWalldist;
		x++;
	}
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

			if (transformY > 0 && stripe > 0 && stripe < data->sort->resw && transformY < zbuffer[stripe])
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
}

int
	ft_sort_and_rend(int fd, t_sort *sort)
{
	char		*compressedmap;
	t_data		data;
	t_mlx_data	mlx_data;
	t_player	player;
	char		**map;

	compressedmap = ft_compressmap(fd, sort);
	if (sort->isbonus)
		ft_debug_sort(sort);
	map = ft_split(compressedmap, '~');
	free(compressedmap);
	mlx_data = ft_set_mlx_data(map, &data, sort, &player);
	ft_checkmap(&mlx_data);
	if (!(ft_count_sprite(&mlx_data)))
		return (EXIT_FAILURE);
	if (!(ft_attrib_sprite(&mlx_data)))
		return (EXIT_FAILURE);
	if (sort->isbonus)
		ft_debugmap(map);
	ft_loadmlx(&mlx_data);
	return (1);
}

int main(int argc, const char *argv[])
{
	t_sort	sort;
	int		fd;
	int		error;

	error = 0;
	sort = ft_initialaze_sort();
	if (argc == 2 || argc == 3)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			error = 1;
		if (argc == 3 && (ft_strncmp(argv[2], "-save", 6) == 0 || ft_strncmp(argv[2], "--save", 6) == 0))
			sort.issave = 1;
		else if (argc == 3)
			error = 1;
		if (error)
		{
			write(1, "Error\nBad Argument\n", 19);
			return (0);
		}
		ft_sort_and_rend(fd, &sort);
	}
	return (0);
}
