/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 04:38:03 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/24 21:27:34 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void
	ft_lifebar(t_square square, t_mlx_data *data)
{
	square = ft_set_square(112, 22, data->sort->resw
	- (data->sort->resh * 0.25) - 6, 14);
	ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 0), data);
	square = ft_set_square(108, 18, data->sort->resw
	- (data->sort->resh * 0.25) - 4, 16);
	ft_mlx_drawfilled_square(&square, rgb_int(180, 0, 0), data);
	square = ft_set_square(100, 10, data->sort->resw
	- data->sort->resh * 0.25, 20);
	ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 0), data);
	square = ft_set_square(data->health, 10, data->sort->resw
	- data->sort->resh * 0.25, 20);
	ft_mlx_drawfilled_square(&square, rgb_int(255, 0, 0), data);
}

static void
	ft_staminabar(t_square square, t_mlx_data *data)
{
	square = ft_set_square(112, 22, data->sort->resw
	- (data->sort->resh * 0.25) - 6, 14 + 24);
	ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 0), data);
	square = ft_set_square(108, 18, data->sort->resw
	- (data->sort->resh * 0.25) - 4, 16 + 24);
	ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 180), data);
	square = ft_set_square(100, 10, data->sort->resw
	- data->sort->resh * 0.25, 20 + 24);
	ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 0), data);
	square = ft_set_square(data->stamina, 10, data->sort->resw
	- data->sort->resh * 0.25, 20 + 24);
	ft_mlx_drawfilled_square(&square, rgb_int(0, 0, 255), data);
}

int
	draw(t_mlx_data *data)
{
	t_square	square;

	data->movespeed = 0.05;
	ft_keybr_event(data);
	ft_raycast(data);
	if (data->showbonus == 1)
		ft_mlx_show_minimap(data, data->sort);
	ft_teleport(data);
	data->ord = 0;
	while (data->ord < data->spritenumber)
	{
		ft_spookia(data);
	}
	ft_lifecheck(data);
	if (data->showbonus == 1)
	{
		ft_lifebar(square, data);
		ft_staminabar(square, data);
	}
	mlx_put_image_to_window(data->data->mlx_ptr, data->data->mlx_win,
	data->img.img_ptr, 0, 0);
	screenshot(data);
	ft_die(data);
	return (1);
}

static void
	ft_set_mlx_datatwo(t_mlx_data *mlx_data)
{
	mlx_data->left = 0;
	mlx_data->down = 0;
	mlx_data->right = 0;
	mlx_data->esc = 0;
	mlx_data->mkey = 0;
	mlx_data->r = 0;
	mlx_data->key_left = 0;
	mlx_data->key_right = 0;
	mlx_data->key_up = 0;
	mlx_data->key_down = 0;
	mlx_data->shift = 0;
	mlx_data->spritenumber = 0;
	mlx_data->posx = 1.5;
	mlx_data->posy = 1.5;
	mlx_data->dirx = -1;
	mlx_data->diry = 0;
	mlx_data->planex = 0;
	mlx_data->planey = 0.66;
	mlx_data->promton = 0;
	mlx_data->isdead = 0;
	mlx_data->health = 100;
	mlx_data->stamina = 100;
	mlx_data->hasstamina = 1;
	mlx_data->biggest = 0;
}

t_mlx_data
	ft_set_mlx_data(char **map, t_data *data, t_sort *sort, t_player *player)
{
	t_mlx_data	mlx_data;
	double		zbuffer[sort->resw];
	int			spriteorder[mlx_data.numesprite];
	double		spritedistance[mlx_data.numesprite];

	mlx_data.map = map;
	mlx_data.numesprite = 2;
	mlx_data.data = data;
	mlx_data.sort = sort;
	mlx_data.player = player;
	mlx_data.up = 0;
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
	ft_set_mlx_datatwo(&mlx_data);
	return (mlx_data);
}
