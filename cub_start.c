/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 22:06:24 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/12 20:48:39 by lejulien         ###   ########.fr       */
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
	sort.mapwidth = 33;
	sort.mapheight = 33;
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

int     rgba_int(int red, int green, int blue, int alpha)
{
    int     rgb;

    rgb = red;
    rgb = (rgb << 8) + green;
    rgb = (rgb << 8) + blue;
	rgb = (rgb << 8) + alpha;
    return (rgb);
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

static void
	ft_debug_sort(sort_t *sort)
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
	ft_putvalues("rgbc = ",  sort->rgbc);
	ft_putvalues("mapwidth = ",  sort->mapwidth);
	ft_putvalues("mapheight = ",  sort->mapheight);
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
	*ft_compressmap(int fd, sort_t *sort)
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
			else
				previousline = currentline;
		}
		else
		{
			if (ret == 0)
			{
				ft_putstr_fd("Error no map\n", 1);
				exit(0);
			}
			if (currentline[0] == 'R')
			{
				int i = 1;
				if (currentline[i] != ' ')
				{
					ft_putstr_fd("res error\n", 1);
					exit(0);
				}
				sort->resw = ft_atoi(&currentline[i]);
				while (currentline[i] == ' ')
					i++;
				while (ft_isdigit(currentline[i]) == 1)
					i++;
				if (currentline[i] != ' ')
				{
					ft_putstr_fd("res error\n", 1);
					exit(0);
				}
				sort->resh = ft_atoi(&currentline[i]);
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
	ft_mlx_show_minimap(data_t *data, mlx_data_t *mlxdata, sort_t *sort)
{
	int		resph = sort->resh * 0.20 / sort->mapheight;
	//int	pers = (mlxdata->sort->resw < mlxdata->sort->resh)?mlxdata->sort->resh:mlxdata->sort->resw;
	int	i = 0;
	int	j = 0;
    square_t square;
	while (mlxdata->map[i][j])
	{
		while (mlxdata->map[i][j])
		{
			square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
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
			else if (mlxdata->map[i][j] == '0')
			{
                square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
                ft_mlx_drawfilled_square(&square, data, rgb_int(255, 255, 255), mlxdata);
			}
			else
            {
			    square = ft_set_square(resph, resph, 10 + j * resph, 10 + i * resph);
                ft_mlx_drawfilled_square(&square, data, rgb_int(255, 0, 0), mlxdata);
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
    mlx_data.numsprite = 2;
    double      zBuffer[sort->resw];
    int         spriteOrder[mlx_data.numsprite];
    double      spriteDistance[mlx_data.numsprite];

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
    mlx_data.posx = 1.5;
    mlx_data.posy = 1.5;
    mlx_data.dirx = -1;
    mlx_data.diry = 0;
    mlx_data.planeX = 0;
    mlx_data.planeY = 0.66;
    mlx_data.promton = 0;
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
    mlx_data.zBuffer = zBuffer;
    mlx_data.spriteOrder = spriteOrder;
    mlx_data.spriteDistance = spriteDistance;
    mlx_data.showbonus = 0;
    return (mlx_data);
}
void
    ft_setplayer(double x, double y, mlx_data_t *data)
{

    data->posx = x;
	data->posy = y;
}

int
    key_press(int key, mlx_data_t *data)
{
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
    if (key == 257)
        data->shift = 1;
    if (key == 15)
        data->r = 1;
    if (key == 126)
        data->key_up = 1;
    if (key == 125)
        data->key_down = 1;
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
    if (key == 257)
        data->shift = 0;
    if (key == 15)
        data->r = 0;
    if (key == 126)
        data->key_up = 0;
    if (key == 125)
        data->key_down = 0;

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
    sortSprite(int *spriteOrder, double *spriteDistance, int numSprite)
{
    (void)spriteOrder;
    (void)spriteDistance;
    (void)numSprite;
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

    if (data->showbonus == 1)
    {
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
    
    			int txf = (int)(data->s_escalier.width * (floorX - cellX)) & (data->s_escalier.width - 1);
    			int tyf = (int)(data->s_escalier.height * (floorY - cellY)) & (data->s_escalier.height - 1);
    			int txr = (int)(data->s_roofeleven.width * (floorX - cellX)) & (data->s_roofeleven.width - 1);
    			int tyr = (int)(data->s_roofeleven.height * (floorY - cellY)) & (data->s_roofeleven.height - 1);

    			floorX += floorStepX;
    			floorY += floorStepY;

    			int color =  data->s_escalier.data[tyf * data->s_escalier.width + txf];

//			if (data->map[cellX][cellY] == '2')
//			    color = data->s_lava.data[ty * data->texwidth + tx];

    			data->img.data[y * data->sort->resw + x] = color;
    			data->img.data[(data->sort->resh - y - 1) * data->sort->resw + x] = data->s_roofeleven.data[data->s_roofeleven.width * tyr + txr];
			//x++;)
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
            if (data->map[mapX][mapY] != '0')
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

////////////////////////////////////////////////////////////////////////////////////////////////////////
		//x of the texture
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    int numSprite = 4;
    int spriteOrder[numSprite];
    t_sprite  *sprite = malloc(numSprite * sizeof(t_sprite));

    int nbr = 0;
    while (nbr < 4)
    {
        sprite[nbr].x = 12.5 + (double)nbr;
        sprite[nbr].y = 12.5;
        if (nbr == 1)
            sprite[nbr].texture = 1;
        else
            sprite[nbr].texture = 0;
        nbr++;
    }
    double  spriteDistance[numSprite];
    while (i < numSprite)
    {
        spriteOrder[i] = i;
        spriteDistance[i] = ((data->posx - sprite[i].x) * (data->posx - sprite[i].x) + (data->posy - sprite[i].y) * (data->posy - sprite[i].y));
        i++;
    }
    sortSprite(spriteOrder, spriteDistance, numSprite);
    i = 0;
    while (i < numSprite)
    {
        double  spriteX = sprite[spriteOrder[i]].x - data->posx;
        double  spriteY = sprite[spriteOrder[i]].y - data->posy;

        double  invDet = 1.0 / (data->planeX * data->diry - data->dirx * data->planeY);

        double  transformX = invDet * (data->diry * spriteX - data->dirx * spriteY);
        double  transformY = invDet * (-data->planeY * spriteX + data->planeX * spriteY);

        int     spriteScreenX = (int)((data->sort->resw / 2) * (1 + transformX / transformY));

        int     spriteHeight = abs((int)(data->sort->resh / (transformY)));
        int     drawStartY = -spriteHeight / 2 + data->sort->resh / 2;
        if (drawStartY < 0)
            drawStartY = 0;
        int     drawEndY = spriteHeight / 2 + data->sort->resh / 2;
        if (drawEndY >= data->sort->resh)
            drawEndY = data->sort->resh - 1;
        
        int     spriteWidth = abs((int)(data->sort->resh / (transformY)));
        int     drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0)
            drawStartX = 0;
        int     drawEndX = spriteWidth / 2 + spriteScreenX;
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
                    int color;
                    if (sprite[spriteOrder[i]].texture == 0)
                        color = data->s_health.data[texWidth * texY + texX];
                    else
                        color = data->s_monster.data[texWidth * texY + texX];
                    if (color != -16777216)
                        data->img.data[y * data->sort->resw + stripe] = color;
                    y++;
                }
            }
            stripe++;
        }
        i++;
    }
    //sortSprites(spriteOrder, spriteDistance, numSprite, data);
}

void
	ft_setplayerdir(mlx_data_t *data, int dir)
{
	if (dir == 0)   //Nord
	{
		data->dirx = -1;
		data->diry = 0;
		data->planeX = 0;
		data->planeY = 0.66;
	}
	if (dir == 1) //Sud
	{
		data->dirx = 1;
		data->diry = 0;
		data->planeX = 0;
		data->planeY = -0.66;
	}
	if (dir == 2)  //Est
	{
		data->dirx = 0;
		data->diry = 1;
		data->planeX = 0.66;
		data->planeY = 0;
	}
	if (dir == 3) // Ouest
	{
		data->dirx = 0;
		data->diry = -1;
		data->planeX = -0.66;
		data->planeY = 0;
	}
}

void
    screenshot(mlx_data_t *data)
{
   if (data->sort->issave == 1)
   {
        ft_putstr_fd("\e[31mProcessing screenshot ...\n", 1);
        
        ft_putstr_fd("\e[32mScreenshot : done :)\n", 1);
   }
   data->sort->issave = 2;
}

int
    draw(mlx_data_t *data)
{
    square_t    square;
    double moveSpeed = 0.05;
    double rotSpeed = 0.05;
	int youdied = 0;


    if (data->esc == 1)
        closeit(NULL);
	if (data->shift == 1 && data->hasstamina == 1 && data->health > 0)
	{
		moveSpeed = 0.1;
		data->stamina--;
		if (data->stamina <= 0)
		{
			data->hasstamina = 0;
			data->stamina = 0;
		}
	}
	else
	{
		data->stamina++;
		if (data->stamina == 100)
			data->hasstamina = 1;
	}
	if (data->stamina > 100)
		data->stamina = 100;
    if (data->mkey == 1)
    {
        data->promton = 1;
    }
	//printf("%f|%f\n", data->dirx, data->diry);
	if (data->health > 0)
	{
		if (data->r == 1)
		{
			data->showbonus = 1;
		}
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
		if (data->up == 1 || data->key_up == 1)
		{
			if (data->map[(int)(data->posx + data->dirx * moveSpeed)][(int)(data->posy)] == '0' ||
				data->map[(int)(data->posx + data->dirx * moveSpeed)][(int)(data->posy)] == '2' ||
				data->map[(int)(data->posx + data->dirx * moveSpeed)][(int)(data->posy)] == '4' ||
				data->map[(int)(data->posx + data->dirx * moveSpeed)][(int)(data->posy)] == '7')
				data->posx += data->dirx * moveSpeed;
			if (data->map[(int)(data->posx)][(int)(data->posy + data->diry * moveSpeed)] == '0' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->diry * moveSpeed)] == '2' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->diry * moveSpeed)] == '4' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->diry * moveSpeed)] == '7')
				data->posy += data->diry * moveSpeed;
		}
		if (data->down == 1 || data->key_down == 1)
		{
			if (data->map[(int)(data->posx - data->dirx * moveSpeed)][(int)(data->posy)] == '0' ||
				data->map[(int)(data->posx - data->dirx * moveSpeed)][(int)(data->posy)] == '2' ||
				data->map[(int)(data->posx - data->dirx * moveSpeed)][(int)(data->posy)] == '4' ||
				data->map[(int)(data->posx - data->dirx * moveSpeed)][(int)(data->posy)] == '7')
				data->posx -= data->dirx * moveSpeed;
			if (data->map[(int)(data->posx)][(int)(data->posy - data->diry * moveSpeed)] == '0' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->diry * moveSpeed)] == '2' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->diry * moveSpeed)] == '4' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->diry * moveSpeed)] == '7')
				data->posy -= data->diry * moveSpeed;
		}
		if (data->right == 1)
		{
			if (data->map[(int)(data->posx + data->planeX * moveSpeed)][(int)(data->posy)] == '0' ||
				data->map[(int)(data->posx + data->planeX * moveSpeed)][(int)(data->posy)] == '2' ||
				data->map[(int)(data->posx + data->planeX * moveSpeed)][(int)(data->posy)] == '4' ||
				data->map[(int)(data->posx + data->planeX * moveSpeed)][(int)(data->posy)] == '7')
				data->posx += data->planeX * moveSpeed;
			if (data->map[(int)(data->posx)][(int)(data->posy + data->planeY * moveSpeed)] == '0' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->planeY * moveSpeed)] == '2' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->planeY * moveSpeed)] == '4' ||
				data->map[(int)(data->posx)][(int)(data->posy + data->planeY * moveSpeed)] == '7')
				data->posy += data->planeY * moveSpeed;
		}
		if (data->left == 1)
		{
			if (data->map[(int)(data->posx - data->planeX * moveSpeed)][(int)(data->posy)] == '0' ||
				data->map[(int)(data->posx - data->planeX * moveSpeed)][(int)(data->posy)] == '2' ||
				data->map[(int)(data->posx - data->planeX * moveSpeed)][(int)(data->posy)] == '4' ||
				data->map[(int)(data->posx - data->planeX * moveSpeed)][(int)(data->posy)] == '7')
				data->posx -= data->planeX * moveSpeed;
			if (data->map[(int)(data->posx)][(int)(data->posy - data->planeY * moveSpeed)] == '0' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->planeY * moveSpeed)] == '2' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->planeY * moveSpeed)] == '4' ||
				data->map[(int)(data->posx)][(int)(data->posy - data->planeY * moveSpeed)] == '7')
				data->posy -= data->planeY * moveSpeed;
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
        ft_mlx_show_minimap(data->data, data, data->sort);
    if (data->map[(int)data->posx][(int)data->posy] == '2')
		data->health = data->health - 5;
    if (data->map[(int)data->posx][(int)data->posy] == '7')
		data->health = data->health + 5;
    if (data->map[(int)data->posx][(int)data->posy] == '4')
		data->posy = 21.5;
	//printf("x = %d, y = %d\n", (int)data->posx, (int)data->posy);
	if ((int)data->posx == 18 && (int)data->posy == 8)
	{
		data->posx = data->posx = 20.0 + (data->posx - (int)data->posx);
		data->posy = data->posy = 20.0 + (data->posy - (int)data->posy);
	}
	if ((int)data->posx == 20 && (int)data->posy == 24)
	{
		data->posx = data->posx = 4.0 + (data->posx - (int)data->posx);
		data->posy = data->posy = 13.0 + (data->posy - (int)data->posy);
	}
	if ((int)data->posx == 18 && (int)data->posy == 16)
	{
		data->posx = data->posx = 20.0 + (data->posx - (int)data->posx);
		data->posy = data->posy = 20.0 + (data->posy - (int)data->posy);
	}
	//health
    if (data->health <= 0)
    {
		data->health = 0;
        youdied = 1;
    }
	if (data->health > 100)
		data->health = 100;
    if (data->showbonus == 1)
    {
	    //printf("planex = %f planey = %f\n", data->planeX, data->planeY);
        square = ft_set_square(112, 22, data->sort->resw - (data->sort->resh * 0.25) - 6, 14);
        ft_mlx_drawfilled_square(&square, data->data, rgb_int(0, 0, 0), data);
        square = ft_set_square(108, 18, data->sort->resw - (data->sort->resh * 0.25) - 4, 16);
        ft_mlx_drawfilled_square(&square, data->data, rgb_int(180, 0, 0), data);
        square = ft_set_square(100, 10, data->sort->resw - data->sort->resh * 0.25, 20);
        ft_mlx_drawfilled_square(&square, data->data, rgb_int(0, 0, 0), data);
        square = ft_set_square(data->health, 10, data->sort->resw - data->sort->resh * 0.25, 20);
        ft_mlx_drawfilled_square(&square, data->data, rgb_int(255, 0, 0), data);

    	//stamina bar
        square = ft_set_square(112, 22, data->sort->resw - (data->sort->resh * 0.25) - 6, 14 + 24);
        ft_mlx_drawfilled_square(&square, data->data, rgb_int(0, 0, 0), data);
        square = ft_set_square(108, 18, data->sort->resw - (data->sort->resh * 0.25) - 4, 16 + 24);
        ft_mlx_drawfilled_square(&square, data->data, rgb_int(0, 0, 180), data);
        square = ft_set_square(100, 10, data->sort->resw - data->sort->resh * 0.25, 20 + 24);
        ft_mlx_drawfilled_square(&square, data->data, rgb_int(0, 0, 0), data);
        square = ft_set_square(data->stamina, 10, data->sort->resw - data->sort->resh * 0.25, 20 + 24);
        ft_mlx_drawfilled_square(&square, data->data, rgb_int(0, 0, 255), data);
    }
//  Updating actual image
	mlx_put_image_to_window(data->data->mlx_ptr, data->data->mlx_win, data->img.img_ptr, 0, 0);
    screenshot(data);	
//  text HUD
    if (youdied)
		mlx_string_put(data->data->mlx_ptr, data->data->mlx_win,
		data->sort->resw * 0.5 - 40,  data->sort->resh * 0.5,
		rgb_int(0, 0 , 0), "YOU DIED");
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

	compressedmap = ft_compressmap(fd, sort);
	ft_debug_sort(sort);
	map = ft_split(compressedmap, '~');
	free(compressedmap);
    mlx_data = ft_set_mlx_data(map, &data, sort, &player);
	ft_setplayer(3.5, 22.5, &mlx_data);
	ft_setplayerdir(&mlx_data, 3);
    ft_debugmap(map);
	if (!(data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, sort->resw, sort->resh, "cub3d")))
		return (EXIT_FAILURE);
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
    mlx_data.s_health.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/New-Piskel.xpm", &mlx_data.s_health.width, &mlx_data.s_health.height);
    mlx_data.s_monster.img_ptr = mlx_xpm_file_to_image(mlx_data.data->mlx_ptr, "./textures/monster.xpm", &mlx_data.s_monster.width, &mlx_data.s_monster.height);
	
	
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
	//int game = 1;
	//while (game)
	//{
		mlx_hook(data.mlx_win, 17, 0L, closeit, NULL);
		mlx_hook(data.mlx_win, 2, 1L<<0, key_press, &mlx_data);
		mlx_key_hook(data.mlx_win, key_release, &mlx_data);
		mlx_loop_hook(data.mlx_ptr, draw, &mlx_data);
		mlx_loop(data.mlx_ptr);
	//}
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
		ft_sort_and_rend(fd, &sort);
	}
	return (0);
}
