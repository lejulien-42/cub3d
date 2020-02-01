/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 22:06:24 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/01 14:13:50 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "cub.h"
#include "get_next_line.h"
#include "./libft-42/libft.h"

static sort_t
	ft_initialaze_sort(void)
{
	sort_t	sort;

	sort.issave = 0;
	sort.northpath = NULL;
	sort.southpath = NULL;
	sort.eastpath = NULL;
	sort.westpath = NULL;
	sort.resw = 700;
	sort.resh = 500;
	sort.sprite = NULL;
	sort.rgbf = 0;
	sort.rgbc = 0;
	sort.mapwidth = 29;
	sort.mapheight = 19;
	return (sort);
}

int     rgb_int(int red, int green, int blue)
{
    int     rgb;

    rgb = red;
    rgb = (rgb << 8) + green;
    rgb = (rgb << 8) + blue;
    return (rgb);
}
																				#include <stdio.h>

static void
	ft_debug_sort(sort_t *sort)
{
	printf("is_save = %d\n", sort->issave);
	printf("northpath = %s\n", sort->northpath);
	printf("southpath = %s\n", sort->southpath);
	printf("eastpath = %s\n", sort->eastpath);
	printf("westpath = %s\n", sort->westpath);
	printf("resw = %d\n", sort->resw);
	printf("resh = %d\n", sort->resh);
	printf("sprite = %s\n", sort->sprite);
	printf("rgbf = %d\n", sort->rgbf);
	printf("rgbc = %d\n",  sort->rgbc);
	printf("mapwidth = %d\n",  sort->mapwidth);
	printf("mapheight = %d\n",  sort->mapheight);
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

char
	*ft_subspace(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = malloc((strlennspace(str) + 1) * sizeof(char));
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		temp[j] = str[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

char
	*ft_compressmap(int fd)
{
	int		ret;
	char	*currentline;
	char	*previousline;
	char	*tofree;
	char	*temp;


	ret = 1;
	previousline = NULL;
	while (ret == 1)
	{
		ret = get_next_line(fd, &currentline);
		if (ret == 0)
			return (previousline);
		if (currentline[0] != '1' && ret == 1)
		{
			write(1, "error\n", 6);
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
		else
			previousline = currentline;
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
			write(1, &map[i][j], 1);
			j++;
		}
		j = 0;
		write(1, "\n", 1);
		i++;
	}
}

void
	ft_mlx_show_minimap(data_t *data, mlx_data_t *mlxdata, sort_t *sort, square_t square)
{
	int		resph = sort->resh * 0.20 / sort->mapheight;
	int	i;
	int	j;
	int playerx;
	int playery;

	i = 0;
	j = 0;
	playerx = mlxdata->posx;
	playery = mlxdata->posy;
	square = ft_set_square(resph - 2, resph - 2, 10, 10 );
	ft_mlx_drawfilled_square(&square, data, rgb_int(0, 0, 0), mlxdata);
	if (playerx > 20)
	    playerx = 20;
	if (playery > 20)
	    playerx = 20;
	while (mlxdata->map[i][j])
	{
		while (mlxdata->map[i][j])
		{
			if (mlxdata->map[i][j] == '1')
			{
				square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
				ft_mlx_drawfilled_square(&square, data, rgb_int(0, 204, 153), mlxdata);
			}
			else if (mlxdata->map[i][j] == '2')
            {
                square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
                ft_mlx_drawfilled_square(&square, data, rgb_int(0, 200, 0), mlxdata);
            }
			else if (mlxdata->map[i][j] == '3')
            {
                square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
                ft_mlx_drawfilled_square(&square, data, rgb_int(0, 0, 200), mlxdata);
            }
			else
            {
			    square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
                ft_mlx_drawfilled_square(&square, data, rgb_int(255, 255, 255), mlxdata);
            }
		    j++;
		}
		j = 0;
		i++;
	}
    square = ft_set_square(5, 5, 8 + mlxdata->posy * resph, 8 + mlxdata->posx * resph);
	ft_mlx_drawfilled_square(&square, data, rgb_int(255, 127, 80), mlxdata);
    square = ft_set_square(3, 3, 9 + mlxdata->posy * resph + 2 * mlxdata->diry, 9 + mlxdata->posx * resph + 2 * mlxdata->dirx);
	ft_mlx_drawfilled_square(&square, data, rgb_int(0, 0, 0), mlxdata);
	/*
	** Set point in player view dir
	**
	**North	dirx = -1	&& 	diry = 0
	**East 	dirx = 0	&&	diry = 1
	**West	dirx = 0	&&	diry = -1
	**South	dirx = 1	&&	diry = 0
	*/
}

int
	closeit(void *param) {
    (void) *param;
    exit(0);
    return (0);
}

pos_t   ft_setpoint(x, y)
{
    pos_t point;

    point.x = x;
    point.y = y;
    return (point);
}

mlx_data_t
    ft_set_mlx_data(char **map, data_t *data, sort_t *sort, player_t *player)
{
    mlx_data_t  mlx_data;

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
	mlx_data.key_left = 0;
	mlx_data.key_right = 0;
    mlx_data.posx = 1.5;
    mlx_data.posy = 1.5;
    mlx_data.dirx = -1;
    mlx_data.diry = 0;
    mlx_data.planeX = 0;
    mlx_data.planeY = 0.66;
    mlx_data.promton = 0;
    mlx_data.health = 100;
	mlx_data.img.img_ptr = NULL;
	mlx_data.s_wall.img_ptr = NULL;
	mlx_data.s_walltwo.img_ptr = NULL;
	mlx_data.s_wallthree.img_ptr = NULL;
	mlx_data.s_wallfour.img_ptr = NULL;
	mlx_data.s_lava.img_ptr = NULL;
    return (mlx_data);
}
player_t
    ft_setplayer(int x, int y, int o)
{
    player_t    player;

    player.x = x;
    player.y = y;
    player.o = o;
    return (player);
}

int
    key_press(int key, mlx_data_t *data)
{
    //printf("%d\n", key);
    if (key == 0)
        data->left = 1;
    if (key == 2)
        data->right = 1;
    if (key == 13)
        data->up = 1;
    if (key == 1)
        data->down = 1;
    if (key == 53)
        data->esc = 1;
    if (key == 46)
        data->mkey = 1;
    if (key == 123)
        data->key_left = 1;
    if (key == 124)
        data->key_right = 1;
    return (1);
}

int
key_release(int key, mlx_data_t *data)
{
    if (key == 0)
        data->left = 0;
    if (key == 2)
        data->right = 0;
    if (key == 13)
        data->up = 0;
    if (key == 1)
        data->down = 0;
    if (key == 53)
        data->esc = 0;
    if (key == 46)
        data->mkey = 0;
    if (key == 123)
        data->key_left = 0;
    if (key == 124)
        data->key_right = 0;
    return (1);
}

int
    get_click(int button, int x, int y, mlx_data_t *data)
{
    if (button == 1)
    {
        data->posx = x * 0.20 / data->sort->mapheight;
        data->posy = y * 0.20 / data->sort->mapheight;
    }
	return (1);
}


void
ft_setimg(mlx_data_t *data)
{
    int count_h = -1;
    int count_w = -1;

    while (++count_h < data->sort->resh)
    {
        count_w = -1;
        while (++count_w < data->sort->resw)
        {
            if (count_h < (data->sort->resh / 2))
                data->img.data[count_h * data->sort->resw + count_w] = rgb_int(0, 0, 255);
            else
                data->img.data[count_h * data->sort->resw + count_w] = rgb_int(205,133,63);
        }
    }
}

void
    ft_raycast(mlx_data_t *data)
{
    double	cameraX;
    double	rayDirX;
    double	rayDirY;
    int		x = 0;
	int		y = 0;
	char	zbuffer[data->sort->resw];

	while (y < data->sort->resh)
	{
		float	rayDirX0 = data->dirx - data->planeX;
		float	rayDirY0 = data->diry - data->planeY;
		float	rayDirX1 = data->dirx + data->planeX;
		float	rayDirY1 = data->diry + data->planeY;

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

			int tx = (int)(data->texwidth * (floorX - cellX)) & (data->texwidth - 1);
			int ty = (int)(data->texheight * (floorY - cellY)) & (data->texheight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			int color =  data->s_floorfour.data[ty * data->texwidth + tx];

//			if (data->map[cellX][cellY] == '2')
//			    color = data->s_lava.data[ty * data->texwidth + tx];

			data->img.data[y * data->sort->resw + x] = color;
			data->img.data[(data->sort->resh - y - 1) * data->sort->resw + x] = data->s_roofeleven.data[data->texwidth * ty + tx];
			//x++;)
		}
		y++;
	}
	y = 0;
	x = 0;
    while (x < data->sort->resw)
    {
        cameraX = 2 * x / (double)(data->sort->resw) - 1;
        rayDirX = data->dirx + data->planeX * cameraX;
        rayDirY = data->diry + data->planeY * cameraX;
        int mapX = (int)data->posx;
        int mapY = (int)data->posy;
        double sideDistX;
        double sideDistY;
		char	what;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWalldist;

        int    stepX;
        int    stepY;

        int    hit = 0;
        int    side;

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
            if (data->map[mapX][mapY] == '1' || data->map[mapX][mapY] == '3')
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

		char textNum = data->map[mapX][mapY];
		double wallx;
		if (side == 0)
			wallx = data->posy + perpWalldist * rayDirY;
		else
			wallx = data->posx + perpWalldist * rayDirX;
		wallx = wallx - floor((wallx));

		//x of the texture
		int texx = (int)(wallx * (double)(data->texwidth));
		if (side == 0 && rayDirX > 0)
			texx = data->texwidth - texx - 1;
		if (side == 1 && rayDirY < 0)
			texx = data->texwidth - texx - 1;

		double step = 1.0 * data->texheight / lineheight;

		double texpos = (drawstart - data->sort->resh / 2 + lineheight / 2) * step;
		int y = drawstart;
		while (y < drawend)
		{
			int texy = (int)texpos & (data->texheight - 1);
			texpos = texpos + step;
			int color = 0;
			if (what == '1')
			{
				if (side == 1)
				{
					if (rayDirY < 0)
						color = data->s_wall.data[texy * data->texheight + texx]; //TEX_NORTH
					else
						color = data->s_walltwo.data[texy * data->texheight + texx]; //TEX_SOUTH
				}
				else
				{
					if (rayDirX < 0)
						color = data->s_wallfour.data[texy * data->texheight + texx]; //TEX_WEST
					else
						color = data->s_wallthree.data[texy * data->texheight + texx]; //TEX_EAST
				}
			}
			else
			{
				color = data->s_wallthree.data[texy * data->texheight + texx];
			}
			data->img.data[y * data->sort->resw + x] = color;
			y++;
		}
		zbuffer[x] = perpWalldist;
        x++;
    }
	//sprite casting
	
}

int
    draw(mlx_data_t *data)
{
    square_t    square;
    double moveSpeed = 0.05;
    double playerspeed = 0.1;
    double rotSpeed = 0.1;
	int youdied = 0;

    if (data->esc == 1)
        closeit(NULL);
    if (data->mkey == 1)
    {
        data->promton = 1;
    }
	//printf("%f|%f\n", data->dirx, data->diry);
	if (data->health > 0)
	{
		if (data->key_right == 1)
		{
			double oldDirX = data->dirx;
			data->dirx = data->dirx * cos(-rotSpeed) - data->diry * sin(-rotSpeed);
			data->diry = oldDirX * sin(-rotSpeed) + data->diry * cos(-rotSpeed);
			double oldPlaneX = data->planeX;
			data->planeX = data->planeX * cos(-rotSpeed) - data->planeY * sin(-rotSpeed);
			data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);
		}
		if (data->key_left == 1)
		{
			double oldDirX = data->dirx;
			data->dirx = data->dirx * cos(rotSpeed) - data->diry * sin(rotSpeed);
			data->diry = oldDirX * sin(rotSpeed) + data->diry * cos(rotSpeed);
			double oldPlaneX = data->planeX;
			data->planeX = data->planeX * cos(rotSpeed) - data->planeY * sin(rotSpeed);
			data->planeY = oldPlaneX * sin(rotSpeed) + data->planeY * cos(rotSpeed);
		}
		if (data->up == 1)
		{
			if (data->map[(int)(data->posx + data->dirx * moveSpeed)][(int)(data->posy)] == '0' ||
				data->map[(int)(data->posx + data->dirx * moveSpeed)][(int)(data->posy)] == '2' ||
				data->map[(int)(data->posx + data->dirx * moveSpeed)][(int)(data->posy)] == '4')
				data->posx += data->dirx * moveSpeed;
			if (data->map[(int)(data->posx)][(int)(data->posy + data->diry * moveSpeed)] == '0' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->diry * moveSpeed)] == '2' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->diry * moveSpeed)] == '4')
				data->posy += data->diry * moveSpeed;
		}
		if (data->down == 1)
		{
			if (data->map[(int)(data->posx - data->dirx * moveSpeed)][(int)(data->posy)] == '0' ||
				data->map[(int)(data->posx - data->dirx * moveSpeed)][(int)(data->posy)] == '2' ||
				data->map[(int)(data->posx - data->dirx * moveSpeed)][(int)(data->posy)] == '4')
				data->posx -= data->dirx * moveSpeed;
			if (data->map[(int)(data->posx)][(int)(data->posy - data->diry * moveSpeed)] == '0' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->diry * moveSpeed)] == '2' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->diry * moveSpeed)] == '4')
				data->posy -= data->diry * moveSpeed;
		}
		if (data->right == 1)
		{
			if (data->map[(int)(data->posx + data->planeX * moveSpeed)][(int)(data->posy)] == '0' ||
				data->map[(int)(data->posx + data->planeX * moveSpeed)][(int)(data->posy)] == '2' ||
				data->map[(int)(data->posx + data->planeX * moveSpeed)][(int)(data->posy)] == '4')
				data->posx += data->planeX * moveSpeed;
			if (data->map[(int)(data->posx)][(int)(data->posy + data->planeY * moveSpeed)] == '0' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->planeY * moveSpeed)] == '2' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->planeY * moveSpeed)] == '4')
				data->posy += data->planeY * moveSpeed;
		}
		if (data->left == 1)
		{
			if (data->map[(int)(data->posx - data->planeX * moveSpeed)][(int)(data->posy)] == '0' ||
				data->map[(int)(data->posx - data->planeX * moveSpeed)][(int)(data->posy)] == '2' ||
				data->map[(int)(data->posx - data->planeX * moveSpeed)][(int)(data->posy)] == '4')
				data->posx -= data->planeX * moveSpeed;
			if (data->map[(int)(data->posx)][(int)(data->posy - data->planeY * moveSpeed)] == '0' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->planeY * moveSpeed)] == '2' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->planeY * moveSpeed)] == '4')
				data->posy -= data->planeY * moveSpeed;
		}
	}

   // ft_setimg(data);
    ft_raycast(data);
    ft_mlx_show_minimap(data->data, data, data->sort, square);
    if (data->map[(int)data->posx][(int)data->posy] == '2')
		data->health = data->health - 5;
    if (data->map[(int)data->posx][(int)data->posy] == '4')
	{
		data->posx = 2.5;
		data->posy = 1.5;
	}
	//health
    if (data->health <= 0)
    {
		data->health = 0;
        youdied = 1;
    }
    square = ft_set_square(112, 22, data->sort->resw - (data->sort->resh * 0.25) - 6, 14);
    ft_mlx_drawfilled_square(&square, data->data, rgb_int(0, 0, 0), data);
    square = ft_set_square(108, 18, data->sort->resw - (data->sort->resh * 0.25) - 4, 16);
    ft_mlx_drawfilled_square(&square, data->data, rgb_int(180, 0, 0), data);
    square = ft_set_square(100, 10, data->sort->resw - data->sort->resh * 0.25, 20);
    ft_mlx_drawfilled_square(&square, data->data, rgb_int(255, 255, 255), data);
    square = ft_set_square(data->health, 10, data->sort->resw - data->sort->resh * 0.25, 20);
    ft_mlx_drawfilled_square(&square, data->data, rgb_int(255, 0, 0), data);
	//
	mlx_put_image_to_window(data->data->mlx_ptr, data->data->mlx_win, data->img.img_ptr, 0, 0);
	if (youdied)
		mlx_string_put(data->data->mlx_ptr, data->data->mlx_win, data->sort->resw * 0.5 - 40,  data->sort->resh * 0.5, rgb_int(0, 0 , 0), "YOU DIED");
    return (1);
}

void
	ft_setplayerdir(mlx_data_t *data, int dir)
{
	if (dir == 0)
	{
		data->dirx = -1;
		data->diry = 0;
	}
	if (dir == 1)
	{
		data->dirx = 1;
		data->diry = 0;
	}
	if (dir == 2)
	{
		data->dirx = 0;
		data->diry = 1;
	}
	if (dir == 3)
	{
		data->dirx = 0;
		data->diry = -1;
	}
}

int
	ft_sort_and_rend(int fd, sort_t *sort)
{

	char		*compressedmap;
	data_t		data;
	mlx_data_t  mlx_data;
	player_t    player;
	char        **map;
	int			wallresX;
	int			wallresY;

	compressedmap = ft_compressmap(fd);
	map = ft_split(compressedmap, '~');
	free(compressedmap);
    mlx_data = ft_set_mlx_data(map, &data, sort, &player);
	ft_setplayerdir(&mlx_data, 0);
    ft_debugmap(map);
	if (!(data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, sort->resw, sort->resh, "cub3d")))
		return (EXIT_FAILURE);
	mlx_data.img.img_ptr = mlx_new_image(data.mlx_win, mlx_data.sort->resw, mlx_data.sort->resh);
	mlx_data.s_wall.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/WALL_01.xpm", &mlx_data.texwidth, &mlx_data.texheight);
	mlx_data.s_walltwo.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/WALL_02.xpm", &mlx_data.texwidth, &mlx_data.texheight);
	mlx_data.s_wallthree.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/WALL_03.xpm", &mlx_data.texwidth, &mlx_data.texheight);
	mlx_data.s_wallfour.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/WALL_04.xpm", &mlx_data.texwidth, &mlx_data.texheight);
	mlx_data.s_lava.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/lava.XPM", &mlx_data.texwidth, &mlx_data.texheight);
	mlx_data.s_floorfour.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/FLOOR_04.xpm", &mlx_data.texwidth, &mlx_data.texheight);
	mlx_data.s_roofeleven.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/ROOF_11.xpm", &mlx_data.texwidth, &mlx_data.texheight);
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
	ft_setimg(&mlx_data);
	int game = 1;
	while (game)
	{
		mlx_hook(data.mlx_win, 17, 0L, closeit, NULL);
		mlx_hook(data.mlx_win, 2, 1L, key_press, &mlx_data);
		mlx_key_hook(data.mlx_win, key_release, &mlx_data);
		mlx_loop_hook(data.mlx_ptr, draw, &mlx_data);
		mlx_loop(data.mlx_ptr);
	}
	return (1);
}

int main(int argc, const char *argv[])
{
	sort_t	sort;
	int		fd;
	int		error;

	error = 0;
	sort = ft_initialaze_sort();
	if (argc == 2 || argc == 3)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			error = 1;
		if (argc == 3 && ft_strncmp(argv[2], "-save", 6) == 0)
			sort.issave = 1;
		else if (argc == 3)
			error = 1;
		if (error)
		{
			write(1, "Error\nBad Argument\n", 19);
			return (0);
		}
		ft_debug_sort(&sort);
		ft_sort_and_rend(fd, &sort);
	}
	return (0);
}
