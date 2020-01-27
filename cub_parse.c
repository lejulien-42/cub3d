/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 22:06:24 by lejulien          #+#    #+#             */
/*   Updated: 2020/01/22 03:50:06 by lejulien         ###   ########.fr       */
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
	sort.resw = 900;
	sort.resh = 800;
	sort.sprite = NULL;
	sort.rgbf = 0;
	sort.rgbc = 0;
	sort.mapwidth = 10;
	sort.mapheight = 10;
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
	ft_drawline(pos_t pointone, pos_t pointtwo, data_t *data)
{
    int dx = pointtwo.x - pointone.x;
    int dy = pointtwo.y - pointone.y;
    int x = 0;
    int y = 0;
    int x1 = pointone.x;
    int x2 = pointtwo.x;
    int y1 = pointone.y;

    if (x1 <= x2)
    {
        x = x1;
        while (x < x2)
        {
            y = y1 + dy * (x - x1) / dx;
            mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, y, rgb_int(0, 255, 0));
            x++;
        }
    }
    else
    {
        x = x1;
        while (x > x2)
        {
            y = y1 + dy * (x - x1) / dx;
            mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, y, rgb_int(0, 255, 0));
            x--;
        }
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
    square = ft_set_square(resph, resph, 10 + playery * resph, 10 + playerx * resph);
	ft_mlx_drawfilled_square(&square, data, rgb_int(255, 127, 80), mlxdata);
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
    mlx_data.posx = 2;
    mlx_data.posy = 2;
    mlx_data.dirx = -1;
    mlx_data.diry = 0;
    mlx_data.planeX = 0;
    mlx_data.planeY = 0.50;
    mlx_data.promton = 0;
    mlx_data.health = 100;
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
            //printf("%d ", data->img.data[count_h * data->sort->resw + count_w]);
        }
//        printf("\n");
    }
}

void
    ft_raycast(mlx_data_t *data)
{
    double cameraX;
    double rayDirX;
    double rayDirY;
    int    x = 0;

    while (x < data->sort->resw)
    {
        cameraX = 2 * x / (double)data->sort->resw - 1;
        rayDirX = data->dirx + data->planeX * cameraX;
        rayDirY = data->diry + data->planeY * cameraX;
        int mapX = (int)data->posx;
        int mapY = (int)data->posy;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWalldist;

        int    stepX;
        int    stepY;

        int    hit = 0;
        int    side;

        //printf("raycasting start");
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
                sideDistX++;
                mapX = mapX + stepX;
                side = 0;
            }
            else
            {
                sideDistY = sideDistY + deltaDistY;
                mapY = mapY + stepY;
                side = 1;
            }
            if (data->map[mapX][mapY] != '0')
                hit = 1;
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

        //wall color
        int color;
        int i = 0;
        int y = 0;

        while (data->map[i][y])
        {
            y = 0;
            while (data->map[i][y])
            {
                if (data->map[i][y] == '1')
                    color = rgb_int(255, 0, 0);
                else
                    color = rgb_int(88,88,88);
                y++;
            }
            i++;
        }
        if (side == 1)
            color = color / 2;
        printf("start = %d | end = %d\n", drawstart, drawend);
        pos_t posone = ft_setpoint(x, drawstart);
        ft_mlx_vertline(data, color, &posone, drawend - drawstart);
        x++;
    }
}

int
    draw(mlx_data_t *data)
{
    square_t    square;
    double moveSpeed = 0.05;
    double playerspeed = 0.05;
    double rotSpeed = 0.05;

    //printf("x=%f y=%f dirx=%f diry=%f\n", data->posx, data->posy, data->dirx, data->diry);
    //13468991
    printf("%d\n", rgb_int(0, 0, 0));
    if (data->esc == 1)
        closeit(NULL);
    if (data->mkey == 1)
    {
        data->promton = 1;
    }
    if (data->right == 1)
    {
        double oldDirX = data->dirx;
        data->dirx = data->dirx * cos(-rotSpeed) - data->diry * sin(-rotSpeed);
        data->diry = oldDirX * sin(-rotSpeed) + data->diry * cos(-rotSpeed);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(-rotSpeed) - data->planeY * sin(-rotSpeed);
        data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);
    }
    if (data->left == 1)
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
        if (data->map[(int)(data->posx + data->dirx * moveSpeed)][(int)(data->posy)] == '0')
            data->posx += data->dirx * moveSpeed;
        if(data->map[(int)(data->posx)][(int)(data->posy + data->diry * moveSpeed)] == '0')
            data->posy += data->diry * moveSpeed;
    }
    if (data->down == 1)
    {
        if (data->map[(int)(data->posx - data->dirx * moveSpeed)][(int)(data->posy)] == '0')
            data->posx -= data->dirx * moveSpeed;
        if (data->map[(int)(data->posx)][(int)(data->posy - data->diry * moveSpeed)] == '0')
            data->posy -= data->diry * moveSpeed;
    }
    ft_setimg(data);
    ft_raycast(data);
    ft_mlx_show_minimap(data->data, data, data->sort, square);
    data->health++;
    if (data->health > 100)
    {
        data->health = 0;
    }
    square = ft_set_square(108, 18, (data->sort->resh * 0.25) - 4, 16);
    ft_mlx_drawfilled_square(&square, data->data, rgb_int(255, 0, 0), data);
    square = ft_set_square(100, 10, data->sort->resh * 0.25, 20);
    ft_mlx_drawfilled_square(&square, data->data, rgb_int(255, 255, 255), data);
    square = ft_set_square(data->health, 10, data->sort->resh * 0.25, 20);
    ft_mlx_drawfilled_square(&square, data->data, rgb_int(255, 0, 0), data);
    mlx_string_put(data->data->mlx_ptr, data->data->mlx_win, 20,  data->sort->resh * 0.25, rgb_int(0, 0 , 0), "100 pv");
    mlx_put_image_to_window(data->data->mlx_ptr, data->data->mlx_win, data->img.img_ptr, 0, 0);
    return (1);
}

int
	ft_sort_and_rend(int fd, sort_t *sort)
{

	char		*compressedmap;
	data_t		data;
	mlx_data_t  mlx_data;
	player_t    player;
	char        **map;

	player = ft_setplayer(40, 40, 0);
	compressedmap = ft_compressmap(fd);
	map = ft_split(compressedmap, '~');
	free(compressedmap);
    mlx_data = ft_set_mlx_data(map, &data, sort, &player);
    ft_debugmap(map);
	if (!(data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, sort->resw, sort->resh, "cub3d")))
		return (EXIT_FAILURE);
	mlx_data.img.img_ptr = mlx_new_image(data.mlx_win, mlx_data.sort->resw, mlx_data.sort->resh);
	mlx_data.img.data = (int *)mlx_get_data_addr(mlx_data.img.img_ptr, &mlx_data.img.bpp, &mlx_data.img.size_l,
	        &mlx_data.img.endian);
	ft_setimg(&mlx_data);
    mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, mlx_data.img.img_ptr, 0, 0);
	int game = 1;
	while (game)
    {
        mlx_hook(data.mlx_win, 17, 0L, closeit, NULL);
        mlx_hook(data.mlx_win, 2, 1L, key_press, &mlx_data);
        mlx_mouse_hook(data.mlx_win, get_click, &mlx_data);
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
