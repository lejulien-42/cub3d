/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 06:13:21 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/23 00:27:35 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

int
	key_press(int key, t_mlx_data *data)
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
	key_release(int key, t_mlx_data *data)
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
	get_click(int button, int x, int y, t_mlx_data *data)
{
	if (button == 1)
	{
		data->posx = x * 0.20 / data->sort->mapheight;
		data->posy = y * 0.20 / data->sort->mapheight;
	}
	return (1);
}

void
	ft_setimg(t_mlx_data *data)
{
	int count_h = -1;
	int count_w = -1;

	while (++count_h < data->sort->resh)
	{
		count_w = -1;
		while (++count_w < data->sort->resw)
		{
			if (count_h < (data->sort->resh / 2))
				data->img.data[count_h * data->sort->resw
				+ count_w] = data->sort->rgbc;
			else
				data->img.data[count_h * data->sort->resw
				+ count_w] = data->sort->rgbf;
		}
	}
}

void
	ft_swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
