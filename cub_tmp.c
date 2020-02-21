/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cub_start.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lejulien <lejulien@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/01/01 22:06:24 by lejulien		  #+#	#+#			 */
/*   Updated: 2020/02/20 03:08:11 by lejulien		 ###   ########.fr	   */
/*																			*/
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
	char	*currentline;
	char	*previousline;
	char	*tofree;
	char	*temp;
	static int		isatmap = 0;


	ret = 1;
	previousline = NULL;
	while (ret == 1)
	{
		ret = get_next_line(fd, &currentline);
		if (currentline[0] == '1')
			isatmap = 1;
		if (isatmap)
		{
			if (ret == 0)
			{
				free(currentline);
				return (previousline);
			}
			if (currentline[0] != '1' && ret == 1)
			{
				write(1, "error map\n", 10);
			}
			if (previousline)
			{
				tofree = ft_strjoin(previousline, "~");
				temp = ft_strjoin(tofree, currentline);
				ft_subspace(temp);
				free(tofree);
				free(previousline);
				previousline = ft_subspace(temp);
				free(temp);
				free(currentline);
			}
		}
		else
		{
			previousline = currentline;
			if (ret == 0)
			{
				ft_putstr_fd("Error no map\n", 1);
				exit(0);
			}
			if (currentline[0] == 'R')
			{
				int i = 1;
				if (ft_whitespace(currentline[i]) == 0)
					ft_puterror("ERROR\nResolution");
				while (ft_whitespace(currentline[i]) == 1)
					i++;
				if (ft_isdigit(currentline[i]) == 0)
					ft_puterror("ERROR\nResolution");
				sort->resw = ft_atoi(&currentline[i]);
				while (ft_isdigit(currentline[i]) == 1)
					i++;
				if (ft_whitespace(currentline[i]) == 0)
					ft_puterror("ERROR\nResolution");
				while (ft_whitespace(currentline[i] == 1))
					i++;
				if (ft_isdigit(currentline[i]) == 0)
					ft_puterror("ERROR\nResolution");
				sort->resh = ft_atoi(&currentline[i]);
				while (ft_isdigit(currentline[i]))
					i++;
				if (ft_whitespace(currentline[i]) == 0)
					ft_puterror("ERROR\nResolution");
			}
			else if (currentline[0] == 'B')
			{
				int i = 1;
				if (ft_whitespace(currentline[i]) != 1)
				{
					ft_putstr_fd("Bonus Error\n", 1);
					exit(0);
				}
				while (ft_whitespace(currentline[i]) == 1)
					i++;
				if (currentline[i] == '1')
					sort->isbonus = 1;
			}
		}
	}
	return (NULL);
}

void
	ft_debugmap(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i][j])
	{
		while (map[i][j])
		{
			if (map[i][j] == '1')
			{
				ft_putstr_fd("\e[41m ", 1);
				ft_putstr_fd("\e[41m ", 1);
			}
			else if (map[i][j] == '2')
			{
				ft_putstr_fd("\e[45m ", 1);
				ft_putstr_fd("\e[45m ", 1);
			}
			else if (map[i][j] == '3')
			{
				ft_putstr_fd("\e[102m ", 1);
				ft_putstr_fd("\e[102m ", 1);
			}
			else if (map[i][j] == '0')
			{
				ft_putstr_fd("\e[107m ", 1);
				ft_putstr_fd("\e[107m ", 1);
			}
			else
			{
				ft_putstr_fd("\e[46m ", 1);
				ft_putstr_fd("\e[46m ", 1);
			}
			j++;
		}
		j = 0;
		ft_putstr_fd("\e[49m \n", 1);
		i++;
	}
}

void
	ft_show_enemypos(t_mlx_data *data, int resph)
{
	int i;
	t_square  square;

	i = 0;
	while (i < data->spritenumber)
	{
		if (data->sprite[i].texture == 0)
		{
			square = ft_set_square(5, 5, 8 + data->sprite[i].y * resph, 8 + data->sprite[i].x * resph);
			ft_mlx_drawfilled_square(&square, rgb_int(255, 0, 0), data);
		}
		i++;
	}
}

void
	ft_mlx_show_minimap(t_mlx_data *mlxdata, t_sort *sort)
{
	int		resph = sort->resh * 0.20 / sort->mapheight;
	int	i = 0;
	int	j = 0;
	t_square square;
	while (mlxdata->map[i][j])
	{
		while (mlxdata->map[i][j])
		{
			square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
			if (mlxdata->map[i][j] == '1')
			{
				square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
				ft_mlx_drawfilled_square(&square, rgb_int(0, 204, 153), mlxdata);
			}
			else if (mlxdata->map[i][j] == '2')
			{
				square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
				ft_mlx_drawfilled_square(&square, rgb_int(0, 200, 0), mlxdata);
			}
			else if (mlxdata->map[i][j] == '3')
			{
				square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
				ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 200), mlxdata);
			}
			else if (mlxdata->map[i][j] == '0' || mlxdata->map[i][j] == 'A' || mlxdata->map[i][j] == 'B')
			{
				square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
				ft_mlx_drawfilled_square(&square, rgb_int(255, 255, 255), mlxdata);
			}
			else
			{
				square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
				ft_mlx_drawfilled_square(&square, rgb_int(255, 0, 0), mlxdata);
			}
			j++;
		}
		j = 0;
		i++;
	}
	ft_show_enemypos(mlxdata, resph);
	square = ft_set_square(5, 5, 8 + mlxdata->posy * resph, 8 + mlxdata->posx * resph);
	ft_mlx_drawfilled_square(&square, rgb_int(255, 127, 80), mlxdata);
	square = ft_set_square(3, 3, 9 + mlxdata->posy * resph + 2 * mlxdata->diry, 9 + mlxdata->posx * resph + 2 * mlxdata->dirx);
	ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 0), mlxdata);
}





t_mlx_data
	ft_set_mlx_data(char **map, t_data *data, t_sort *sort, t_player *player)
{
	t_mlx_data  mlx_data;
	mlx_data.numesprite = 2;
	double	  zbuffer[sort->resw];
	int		 spriteorder[mlx_data.numesprite];
	double	  spritedistance[mlx_data.numesprite];

	mlx_data.map = map;
	mlx_data.data = data;
	mlx_data.sort = sort;
	mlx_data.player = player;
	mlx_data.up = 0;
	mlx_data.left = 0;
	mlx_data.down = 0;
	mlx_data.right = 0;
	mlx_data.esc = 0;
	mlx_data.mkey = 0;
	mlx_data.r = 0;
	mlx_data.key_left = 0;
	mlx_data.key_right = 0;
	mlx_data.key_up = 0;
	mlx_data.key_down = 0;
	mlx_data.shift = 0;
	mlx_data.spritenumber = 0;
	mlx_data.posx = 1.5;
	mlx_data.posy = 1.5;
	mlx_data.dirx = -1;
	mlx_data.diry = 0;
	mlx_data.planex = 0;
	mlx_data.planey = 0.66;
	mlx_data.promton = 0;
	mlx_data.isdead = 0;
	mlx_data.health = 100;
	mlx_data.stamina = 100;
	mlx_data.hasstamina = 1;
	mlx_data.img.img_ptr = NULL;
	mlx_data.s_wall.img_ptr = NULL;
	mlx_data.s_walltwo.img_ptr = NULL;
	mlx_data.s_wallthree.img_ptr = NULL;
	mlx_data.s_wallfour.img_ptr = NULL;
	mlx_data.s_lava.img_ptr = NULL;
	mlx_data.s_arrowtex.img_ptr = NULL;
	mlx_data.zbuffer = zbuffer;
	mlx_data.spriteorder = spriteorder;
	mlx_data.spritedistance = spritedistance;
	mlx_data.showbonus = 0;
	return (mlx_data);
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
	{
		ft_setimg(data);
	}
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
			if (this != '0' && this != 'A' && this != 'B')
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
		int texxs_arrowtex = (int)(wallx * (double)(data->s_arrowtex.width));
		int texxs_arrowtexl = (int)(wallx * (double)(data->s_arrowtexl.width));
		int texxs_lifeframe = (int)(wallx * (double)(data->s_lifeframe.width));
		int texxs_fl = (int)(wallx * (double)(data->s_fl.width));
		if (side == 0 && rayDirX > 0)
		{
			texxs_wallfour = data->s_wallfour.width - texxs_wallfour - 1;
			texxs_wallfour = data->s_lifeframe.width - texxs_lifeframe - 1;
			texxs_arrowtex = data->s_arrowtex.width - texxs_arrowtex - 1;
			texxs_arrowtexl = data->s_arrowtexl.width - texxs_arrowtexl - 1;
			texxs_fl = data->s_fl.width - texxs_fl - 1;
		}
		if (side == 1 && rayDirY < 0)
		{
			texxs_wallfour = data->s_wallfour.width - texxs_wallfour - 1;
			texxs_arrowtex = data->s_arrowtex.width - texxs_arrowtex - 1;
			texxs_lifeframe = data->s_lifeframe.width - texxs_lifeframe - 1;
			texxs_arrowtexl = data->s_arrowtexl.width - texxs_arrowtexl - 1;
			texxs_fl = data->s_fl.width - texxs_fl - 1;
		}

		double steps_wallfour = 1.0 * data->s_wallfour.height / lineheight;
		double steps_arrowtex = 1.0 * data->s_arrowtex.height / lineheight;
		double steps_lifeframe = 1.0 * data->s_lifeframe.height / lineheight;
		double steps_arrowtexl = 1.0 * data->s_arrowtexl.height / lineheight;
		double steps_fl = 1.0 * data->s_fl.height / lineheight;


		double texposs_wallfour = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_wallfour;
		double texposs_arrowtex = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_arrowtex;
		double texposs_lifeframe = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_lifeframe;
		double texposs_arrowtexl = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_arrowtexl;
		double texposs_fl = (drawstart - data->sort->resh / 2 + lineheight / 2) * steps_fl;
		
		int y = drawstart;
		while (y < drawend)
		{
			texposs_wallfour = texposs_wallfour + steps_wallfour;
			texposs_arrowtex = texposs_arrowtex + steps_arrowtex;
			texposs_arrowtexl = texposs_arrowtexl + steps_arrowtexl;
			texposs_lifeframe = texposs_lifeframe + steps_lifeframe;
			texposs_fl = texposs_fl + steps_fl;
			int color = 0;
			if (what == '1')
			{
				if (side == 1)
				{
					if (rayDirY < 0)
						color = data->s_wallfour.data[((int)texposs_wallfour & (data->s_wallfour.height - 1)) * data->s_wallfour.height + texxs_wallfour]; //TEX_NORTH
					else
						color = data->s_wallfour.data[((int)texposs_wallfour & (data->s_wallfour.height - 1)) * data->s_wallfour.height + texxs_wallfour]; //TEX_SOUTH
				}
				else
				{
					if (rayDirX < 0)
						color = data->s_wallfour.data[((int)texposs_wallfour & (data->s_wallfour.height - 1)) * data->s_wallfour.height + texxs_wallfour]; //TEX_WEST
					else
						color = data->s_wallfour.data[((int)texposs_wallfour & (data->s_wallfour.height - 1)) * data->s_wallfour.height + texxs_wallfour]; //TEX_EAST
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
							color = data->s_health.data[texWidth * texY + texX];
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
	draw(t_mlx_data *data)
{
	t_square	square;
	data->movespeed = 0.05;
	double rotSpeed = 0.05;

	ft_key_event(data);
	if (data->health > 0)
	{
		ft_keyr(data);
		ft_keyl(data);
		if (data->up == 1 || data->key_up == 1)
		{
			if (data->map[(int)(data->posx + data->dirx * data->movespeed)][(int)(data->posy)] == '0' ||
				data->map[(int)(data->posx + data->dirx * data->movespeed)][(int)(data->posy)] == '2' ||
				data->map[(int)(data->posx + data->dirx * data->movespeed)][(int)(data->posy)] == '4' ||
				data->map[(int)(data->posx + data->dirx * data->movespeed)][(int)(data->posy)] == '7' ||
				data->map[(int)(data->posx + data->dirx * data->movespeed)][(int)(data->posy)] == 'A' ||
				data->map[(int)(data->posx + data->dirx * data->movespeed)][(int)(data->posy)] == 'B')
				data->posx += data->dirx * data->movespeed;
			if (data->map[(int)(data->posx)][(int)(data->posy + data->diry * data->movespeed)] == '0' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->diry * data->movespeed)] == '2'  ||
				data->map[(int)(data->posx)][(int)(data->posy + data->diry * data->movespeed)] == '4' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->diry * data->movespeed)] == '7'||
				data->map[(int)(data->posx)][(int)(data->posy + data->diry * data->movespeed)] == 'A' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->diry * data->movespeed)] == 'B')
				data->posy += data->diry * data->movespeed;
		}
		if (data->down == 1 || data->key_down == 1)
		{
			if (data->map[(int)(data->posx - data->dirx * data->movespeed)][(int)(data->posy)] == '0' ||
				data->map[(int)(data->posx - data->dirx * data->movespeed)][(int)(data->posy)] == '2'  ||
				data->map[(int)(data->posx - data->dirx * data->movespeed)][(int)(data->posy)] == '4' ||
				data->map[(int)(data->posx - data->dirx * data->movespeed)][(int)(data->posy)] == '7'||
				data->map[(int)(data->posx - data->dirx * data->movespeed)][(int)(data->posy)] == 'A' ||
				data->map[(int)(data->posx - data->dirx * data->movespeed)][(int)(data->posy)] == 'B')
				data->posx -= data->dirx * data->movespeed;
			if (data->map[(int)(data->posx)][(int)(data->posy - data->diry * data->movespeed)] == '0' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->diry * data->movespeed)] == '2'  ||
				data->map[(int)(data->posx)][(int)(data->posy - data->diry * data->movespeed)] == '4' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->diry * data->movespeed)] == '7'||
				data->map[(int)(data->posx)][(int)(data->posy - data->diry * data->movespeed)] == 'A' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->diry * data->movespeed)] == 'B')
				data->posy -= data->diry * data->movespeed;
		}
		if (data->right == 1)
		{
			ft_moverightx(data);
			ft_moverighty(data);
		}
		if (data->left == 1)
		{
			ft_moveleftx(data);
			ft_movelefty(data);
		}
	}
	else
	{
		if (data->r == 1)
		{
			ft_setplayer(12.5, 12.5, data);
			ft_setplayerdir(data, 1);
			data->health = 100;
		}
	}

   // ft_setimg(data);
	ft_raycast(data);
	if (data->showbonus == 1)
		ft_mlx_show_minimap(data, data->sort);
	//printf("x = %d, y = %d\n", (int)data->posx, (int)data->posy);
	ft_teleport(data);
	//health
		data->ord = 0;
		while (data->ord < data->spritenumber)
		{
			ft_spookia(data);
		}
	ft_lifecheck(data);
	if (data->showbonus == 1)
	{
		//printf("planex = %f planey = %f\n", data->planeX, data->planeY);
		square = ft_set_square(112, 22, data->sort->resw - (data->sort->resh * 0.25) - 6, 14);
		ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 0), data);
		square = ft_set_square(108, 18, data->sort->resw - (data->sort->resh * 0.25) - 4, 16);
		ft_mlx_drawfilled_square(&square, rgb_int(180, 0, 0), data);
		square = ft_set_square(100, 10, data->sort->resw - data->sort->resh * 0.25, 20);
		ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 0), data);
		square = ft_set_square(data->health, 10, data->sort->resw - data->sort->resh * 0.25, 20);
		ft_mlx_drawfilled_square(&square, rgb_int(255, 0, 0), data);

		//stamina bar
		square = ft_set_square(112, 22, data->sort->resw - (data->sort->resh * 0.25) - 6, 14 + 24);
		ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 0), data);
		square = ft_set_square(108, 18, data->sort->resw - (data->sort->resh * 0.25) - 4, 16 + 24);
		ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 180), data);
		square = ft_set_square(100, 10, data->sort->resw - data->sort->resh * 0.25, 20 + 24);
		ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 0), data);
		square = ft_set_square(data->stamina, 10, data->sort->resw - data->sort->resh * 0.25, 20 + 24);
		ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 255), data);
	}
//  Updating actual image
	mlx_put_image_to_window(data->data->mlx_ptr, data->data->mlx_win, data->img.img_ptr, 0, 0);
	screenshot(data);
//  text HUD
	ft_die(data);
	return (1);
}

int
	ft_sort_and_rend(int fd, t_sort *sort)
{

	char		*compressedmap;
	t_data		data;
	t_mlx_data  mlx_data;
	t_player	player;
	char		**map;

	compressedmap = ft_compressmap(fd, sort);
	ft_debug_sort(sort);
	map = ft_split(compressedmap, '~');
	free(compressedmap);
	mlx_data = ft_set_mlx_data(map, &data, sort, &player);
	ft_setplayer(3.5, 22.5, &mlx_data);
	ft_setplayerdir(&mlx_data, 3);
	if (!(ft_count_sprite(&mlx_data)))
		return (EXIT_FAILURE);
	if (!(ft_attrib_sprite(&mlx_data)))
		return (EXIT_FAILURE);
	ft_debugmap(map);
	if (!(data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, sort->resw, sort->resh, "cub3d")))
		return (EXIT_FAILURE);
	if (sort->isbonus == 1)
		mlx_data.showbonus = 1;
	mlx_data.img.img_ptr = mlx_new_image(data.mlx_win, mlx_data.sort->resw, mlx_data.sort->resh);
	mlx_data.s_wall.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/WALL_01.xpm", &mlx_data.s_wall.width, &mlx_data.s_wall.height);
	mlx_data.s_walltwo.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/WALL_02.xpm", &mlx_data.s_walltwo.width, &mlx_data.s_walltwo.height);
	mlx_data.s_wallthree.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/WALL_03.xpm", &mlx_data.s_wallthree.width, &mlx_data.s_wallthree.height);
	mlx_data.s_wallfour.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/WALL_04.xpm", &mlx_data.s_wallfour.width, &mlx_data.s_wallfour.height);
	mlx_data.s_escalier.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/hadhio.xpm", &mlx_data.s_escalier.width, &mlx_data.s_escalier.height);
	mlx_data.s_fl.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/spritecute.xpm", &mlx_data.s_fl.width, &mlx_data.s_fl.height);
	mlx_data.s_lava.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/lava.XPM", &mlx_data.s_lava.width, &mlx_data.s_lava.height);
	mlx_data.s_floorfour.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/FLOOR_04.xpm", &mlx_data.s_floorfour.width, &mlx_data.s_floorfour.height);
	mlx_data.s_roofeleven.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/ROOF_11.xpm", &mlx_data.s_roofeleven.width, &mlx_data.s_roofeleven.height);
	mlx_data.s_arrowtex.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/right.xpm", &mlx_data.s_arrowtex.width, &mlx_data.s_arrowtex.height);
	mlx_data.s_arrowtexl.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/left.xpm", &mlx_data.s_arrowtexl.width, &mlx_data.s_arrowtexl.height);
	mlx_data.s_lifeframe.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/frame.xpm", &mlx_data.s_lifeframe.width, &mlx_data.s_lifeframe.height);
	mlx_data.s_health.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/spookias.xpm", &mlx_data.s_health.width, &mlx_data.s_health.height);
	mlx_data.s_monster.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/healing.xpm", &mlx_data.s_monster.width, &mlx_data.s_monster.height);


	mlx_data.img.data = (int *)mlx_get_data_addr(mlx_data.img.img_ptr, &mlx_data.img.bpp, &mlx_data.img.size_l,
			&mlx_data.img.endian);
	mlx_data.s_wall.data = (int *)mlx_get_data_addr(mlx_data.s_wall.img_ptr, &mlx_data.s_wall.bpp, &mlx_data.s_wall.size_l,
			&mlx_data.s_wall.endian);
	mlx_data.s_walltwo.data = (int *)mlx_get_data_addr(mlx_data.s_walltwo.img_ptr, &mlx_data.s_walltwo.bpp, &mlx_data.s_walltwo.size_l,
			&mlx_data.s_walltwo.endian);
	mlx_data.s_wallthree.data = (int *)mlx_get_data_addr(mlx_data.s_wallthree.img_ptr, &mlx_data.s_wallthree.bpp, &mlx_data.s_wallthree.size_l,
			&mlx_data.s_wallthree.endian);
	mlx_data.s_wallfour.data = (int *)mlx_get_data_addr(mlx_data.s_wallfour.img_ptr, &mlx_data.s_wallfour.bpp, &mlx_data.s_wallfour.size_l,
			&mlx_data.s_wallfour.endian);
	mlx_data.s_lava.data = (int *)mlx_get_data_addr(mlx_data.s_lava.img_ptr, &mlx_data.s_lava.bpp, &mlx_data.s_lava.size_l,
			&mlx_data.s_lava.endian);
	mlx_data.s_floorfour.data = (int *)mlx_get_data_addr(mlx_data.s_floorfour.img_ptr, &mlx_data.s_floorfour.bpp, &mlx_data.s_floorfour.size_l,
			&mlx_data.s_floorfour.endian);
	mlx_data.s_roofeleven.data = (int *)mlx_get_data_addr(mlx_data.s_roofeleven.img_ptr, &mlx_data.s_roofeleven.bpp, &mlx_data.s_roofeleven.size_l,
			&mlx_data.s_roofeleven.endian);
	mlx_data.s_escalier.data = (int *)mlx_get_data_addr(mlx_data.s_escalier.img_ptr, &mlx_data.s_escalier.bpp, &mlx_data.s_escalier.size_l,
			&mlx_data.s_escalier.endian);
	mlx_data.s_fl.data = (int *)mlx_get_data_addr(mlx_data.s_fl.img_ptr, &mlx_data.s_fl.bpp, &mlx_data.s_fl.size_l,
			&mlx_data.s_fl.endian);
	mlx_data.s_arrowtexl.data = (int *)mlx_get_data_addr(mlx_data.s_arrowtexl.img_ptr, &mlx_data.s_arrowtexl.bpp, &mlx_data.s_arrowtexl.size_l,
			&mlx_data.s_arrowtexl.endian);
	mlx_data.s_arrowtex.data = (int *)mlx_get_data_addr(mlx_data.s_arrowtex.img_ptr, &mlx_data.s_arrowtex.bpp, &mlx_data.s_arrowtex.size_l,
			&mlx_data.s_arrowtex.endian);
	mlx_data.s_lifeframe.data = (int *)mlx_get_data_addr(mlx_data.s_lifeframe.img_ptr, &mlx_data.s_lifeframe.bpp, &mlx_data.s_lifeframe.size_l,
			&mlx_data.s_lifeframe.endian);
	mlx_data.s_health.data = (int *)mlx_get_data_addr(mlx_data.s_health.img_ptr, &mlx_data.s_health.bpp, &mlx_data.s_health.size_l,
			&mlx_data.s_health.endian);
	mlx_data.s_monster.data = (int *)mlx_get_data_addr(mlx_data.s_monster.img_ptr, &mlx_data.s_monster.bpp, &mlx_data.s_monster.size_l,
			&mlx_data.s_monster.endian);
	ft_setimg(&mlx_data);
	ft_do_mlx(&mlx_data);
	//int game = 1;
	//while (game)
	//{
		// mlx_hook(data.mlx_win, 17, 0L, closeit, NULL);
		// mlx_hook(data.mlx_win, 2, 1L<<0, key_press, &mlx_data);
		// mlx_key_hook(data.mlx_win, key_release, &mlx_data);
		// mlx_loop_hook(data.mlx_ptr, draw, &mlx_data);
		// mlx_loop(data.mlx_ptr);
	//}
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
